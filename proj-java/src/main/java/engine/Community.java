package engine;

import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.TreeSet;
import java.util.TreeMap;
import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.Comparator;
import java.util.Collection;

import common.ComparatorPostInverseChrono;
import common.ComparatorUserNumberOfPosts;
import common.Pair;
import li3.Answer;
import li3.Post;
import li3.Question;
import li3.Tag;
import li3.User;
import li3.MostActive;
import li3.BaseInfo;
import li3.Filters;
import exceptions.UserDoesNotExistException;
import exceptions.UserDoesNotHaveBioException;
import exceptions.PostDoesNotExistException;

/**
  * Class where all the data is stored
  * @author Grupo 42
  * @version 2018-12-06
*/
public class Community implements MostActive, BaseInfo, Filters {

  /** They all share pointers */

  /** Maps the Id of a User, to the Object User */
  private Map<Long,User> usersById;
  /** Maps the Id of a Post, to the Object Post */
  private Map<Long,Post> postsById;
  /** Maps the Id of a Question to the Set of Answers (ordered by Inverse Chrono) */
  private Map<Long,Set<Answer>> answersByQuestionId;
  /** Maps the Id of a User, to their Posts (ordered by Inverse Chrono) */
  private Map<Long,Set<Post>> postsByUserId;
  /** List of Users by number of Posts (is ordered after load) */
  private List<User> usersByNumberOfPosts;
  /** Maps the times, to the Posts with given LocalDateTime (value is set, cause maybe repeated dates) */
  private TreeMap<LocalDateTime,Set<Post>> postsByDate;
  /** Maps the name of a Tag, to the Object Tag */
  private Map<String,Tag> tagsByName;

  /**
    * Default constructor for Community
  */
  public Community() {
    usersById = new HashMap<>(1000);
    postsById = new HashMap<>(1000);
    answersByQuestionId = new HashMap<>(500);
    postsByUserId = new HashMap<>(1000);
    usersByNumberOfPosts = new ArrayList<>(1000);
    postsByDate = new TreeMap<>();
    tagsByName = new HashMap<>(200);
  }

  /**
    * Given a path name, loads all the instance variables
    * @param path the path of the xml files (ends with the /)
  */
  public void load(String path) {
    addUsers(Parser.parseUser(path.concat("Users.xml")));
    addTags(Parser.parseTag(path.concat("Tags.xml")));
    addPosts(Parser.parsePost(path.concat("Posts.xml")));
  }

  /**
    * Returns a pointer to all the Users ordered by number of posts
    * It's the actually pointer, not a copy.
    * @param N number of Users to retrieve
    * @return List with all the Users ordered by number of Posts
    * @see User
  */
  public List<User> getUsersByNumberOfPosts(int N) {
    return this.usersByNumberOfPosts.stream()
    .limit(N)
    .collect(Collectors.toList());
  }

  /**
    * Given an Id, returns the Post, if it exists
    * @param id id of the Post
    * @return The post with that id, or throws an exception
  */
  public Post getPost(Long id) throws PostDoesNotExistException {
    Post p = this.postsById.get(id);
    if (p == null) throw new PostDoesNotExistException();
    else return p;

  }

  /**
    * Given the name of a Tag, returns its id
    * @param tag Name of the tag
    * @return Id of the tag
    * @see li3.Tag
  */
  public Long getTagId(String tag) {
    Tag t = tagsByName.get(tag);
    if (t != null) return t.getId();
    else return Long.valueOf(0);
  }

  /**
    * Given an Id of a question, returns the answers to that question.
    * If no answers, returns an empty Set
    * @param id id of the question
    * @return Set of Answers (maybe empty)
    * @see li3.Answer
  */
  public Set<Answer> getAnswers(Long id) {
    Set<Answer> result = this.answersByQuestionId.get(id);
    if (result == null) return new TreeSet<>();
    else return result;
  }

  /**
    * Given an id of a User, returns the Object
    * @param id id of a user
    * @return User object, or, if it doesn't exist, an exception
  */
  public User getUserById(Long id) throws UserDoesNotExistException {
    if (this.usersById.get(id) == null)
      throw new UserDoesNotExistException(id.toString());
    else
      return this.usersById.get(id);
  }

  /**
    * Given an id of a User, returns a Set with their posts
    * @param id id of user
    * @return A set with their posts (empty set, if no posts)
    * @see li3.Post
  */
  public Set<Post> getPostsOfUser(Long id) {
    Set<Post> result = this.postsByUserId.get(id);
    if (result == null) return new TreeSet<>();
    else return result;
  }

  /**
    * Given two dates, returns a list with the questions that were made during
    * that timeframe. If no questions, returns an empty List
    * @param begin inclusive beginning
    * @param end exclusive ending
    * @see li3.Question
  */
  public List<Question> filterQuestionByInterval(LocalDate begin, LocalDate end) {
    Collection<Set<Post>> col = this.postsByDate.subMap(LocalDateTime.of(begin,LocalTime.MIN),LocalDateTime.of(end,LocalTime.MAX)).values();
    if (col == null) return new ArrayList<Question>();
    else
      return col.stream()
      .flatMap(set -> set.stream())
      .filter(p -> p instanceof Question)
      .map(q -> (Question) q)
      .collect(Collectors.toList());
  }

  /**
    * Returns a List with all the Questions in the database
    * @return List with the questions (empty if no questions stored)
    * @see li3.Question
  */
  public List<Question> filterQuestionByInterval() {
    if (this.postsByDate.size() == 0) return new ArrayList<>();
    else return this.postsByDate.values().stream()
    .flatMap(set -> set.stream())
    .filter(p -> p instanceof Question)
    .map(q -> (Question) q)
    .collect(Collectors.toList());
  }

  /**
    * Given two dates, returns a List with all the answers posted between those dates
    * @param begin inclusive beggining
    * @param end exclusive ending
    * @return List of answers (empty List, if no answers in that period)
    * @see li3.Answer
  */
  public List<Answer> filterAnswerByInterval(LocalDate begin, LocalDate end) {
    Collection<Set<Post>> col = this.postsByDate.subMap(LocalDateTime.of(begin,LocalTime.MIN),LocalDateTime.of(end,LocalTime.MAX)).values();
    if (col == null) return new ArrayList<>();
    else
      return col.stream()
      .flatMap(set -> set.stream())
      .filter(p -> p instanceof Answer)
      .map(p -> (Answer) p)
      .collect(Collectors.toList());
  }

  /**
    * Given two dates, returns a Set with all the Posts posted between those dates
    * @param begin inclusive beggining
    * @param end exclusive ending
    * @return Set of Posts (empty Set, if no posts in that period)
    * @see li3.Post
  */
  public Set<Post> filterPostsByInterval(LocalDate begin, LocalDate end) {
    Collection<Set<Post>> col = this.postsByDate.subMap(LocalDateTime.of(begin,LocalTime.MIN),LocalDateTime.of(end,LocalTime.MAX)).values();
    if (col == null) return new TreeSet<>();
    else
      return col.stream()
      .flatMap(set -> set.stream())
      .collect(Collectors.toSet());
  }

  /**
    * Given two dates, returns a Pair with the number of questions and answers in that period
    * @param begin inclusive beggining
    * @param end exclusive ending
    * @return Pair, with first element as the number of questions, the second the number of answers
    * @see common.Pair
  */
  public Pair<Long,Long> countPostsBetweenDates(LocalDate begin, LocalDate end) {
    Collection<Set<Post>> col = this.postsByDate.subMap(LocalDateTime.of(begin,LocalTime.MIN),LocalDateTime.of(end,LocalTime.MAX)).values();
    long questions = 0;
    long answers = 0;
    for(Set<Post> set : col)
      for(Post p : set) {
        if (p instanceof Answer)
          answers++;
        else
          questions++;
      }
    return new Pair(questions,answers);

  }

  /**
    * Returns the bio of a user
    * @param id id of user
    * @return String (null if no bio)
  */
  public String getBio(Long id) {
    User u = this.usersById.get(id);
    if (u != null) {
      try {
        String bio = u.getBio();
        return bio;
      }
      catch (UserDoesNotHaveBioException e) {
        return null;
      }
    }
    else return null;
  }

  /**
    * Given an id, returns the questions where it participated
    * @param id id of user
    * @return A set with the questions where a user participated, either via answer or question
    * @see li3.Question
  */
  public Set<Question> getQuestions(long id) {
    Set<Post> posts = postsByUserId.get(id);
    if (posts == null) return new TreeSet<>();
    else {
      TreeSet<Question> result = new TreeSet<>();
      for(Post p : posts) {
        // if posted a question, add to result
        if (p instanceof Question) {
          Question q = (Question) p;
          result.add(q);
        }
        // else, get the question he answered
        else {
          Answer a = (Answer) p;
          Question father = (Question) postsById.get(a.getParentId());
          if (father != null) result.add(father);
        }
      }
      return result;
    }
  }

  /**
    * Returns a list with the 10 latest posts of a user
    * @param id id of user
    * @return list of 10 latest posts of a user (empty list if no posts)
    * @see li3.Post
  */
  public List<Post> get10LatestPosts(long id) {
    Set<Post> posts = postsByUserId.get(id);
    if (posts != null) {
      return posts.stream().limit(10).collect(Collectors.toList());
    }
    else
      return new ArrayList<>();
  }

  /**
    * Inserts a List of Users into the system
    * @param l List of users
  */
  private void addUsers(List<User> l) {
    l.stream().forEach(u -> this.insertUser(u));
  }

  /**
    * Inserts a List of Posts into the system
    * @param p list of Posts
  */
  private void addPosts(List<Post> p) {
    p.stream().forEach(post -> this.insertPost(post));
    // now that users have their post count, can sort by number of posts
    this.usersByNumberOfPosts.sort(new ComparatorUserNumberOfPosts());
  }

  /**
    * Inserts a List of Tags into the system
    * @param l List of Tags
  */
  private void addTags(List<Tag> l) {
    l.stream().forEach(t -> this.insertTag(t));
  }

  /**
    * Inserts a new User into the system.
    * @param u User to insert
  */
  private void insertUser(User u) {
    User clonedUser = u.clone();
    this.usersById.put(u.getId(),clonedUser);
    this.usersByNumberOfPosts.add(clonedUser);
  }

  /**
    * Inserts a new Tag into the system.
    * @param t Tag to insert
  */
  private void insertTag(Tag t) {
    Tag clonedTag = t.clone();
    this.tagsByName.put(clonedTag.getName(),clonedTag);
  }

  /**
    * Inserts a new Post into the system
    * @param p Post to insert
  */
  private void insertPost(Post p) {
    long creatorId = p.getCreatorId();
    // adds to posts by creator ID
    if (!postsByUserId.containsKey(creatorId))
      postsByUserId.put(creatorId,new TreeSet<>(new ComparatorPostInverseChrono()));
    postsByUserId.get(creatorId).add(p);

    // adds to the creator count of posts
    User creator = usersById.get(creatorId);
    if (creator != null)
      creator.addPost();
    long id = p.getId();

    // adds to posts by postId and by Date
    if (!postsByDate.containsKey(p.getCreationDate()))
      postsByDate.put(p.getCreationDate(),new TreeSet(new ComparatorPostInverseChrono()));
    postsByDate.get(p.getCreationDate()).add(p);
    postsById.put(id,p);

    // if it's answer, adds to set of answers of the father question
    if (p instanceof Answer) {
      Answer a = (Answer) p;
      long parentID = a.getParentId();
      if(!answersByQuestionId.containsKey(parentID))
        answersByQuestionId.put(parentID,new TreeSet<>());
      answersByQuestionId.get(parentID).add(a);
    }
    // if it's question, starts the new set of answers as empty
    else if (p instanceof Question) {
      Question q = (Question) p;
      if (!answersByQuestionId.containsKey(q.getId()))
        answersByQuestionId.put(q.getId(),new TreeSet<>());
    }
  }


}
