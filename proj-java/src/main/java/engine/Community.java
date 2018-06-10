package engine;

import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.TreeSet;
import java.util.TreeMap;
import java.util.SortedMap;
import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.Comparator;
import java.util.Collection;

import common.*;
import li3.*;
import exceptions.UserDoesNotExistException;
import exceptions.UserDoesNotHaveBioException;
import exceptions.PostDoesNotExistException;

public class Community {

  /** They all share pointers */
  private Map<Long,User> usersById;
  private Map<Long,Post> postsById;
  private Map<Long,Set<Answer>> answersByQuestionId;
  private Map<Long,Set<Post>> postsByUserId;
  private List<User> usersByNumberOfPosts;
  private TreeMap<LocalDateTime,Set<Post>> postsByDate;
  private Map<String,Tag> tagsByName;

  public Community() {
    usersById = new HashMap<>(1000);
    postsById = new HashMap<>(1000);
    answersByQuestionId = new HashMap<>(500);
    postsByUserId = new HashMap<>(1000);
    usersByNumberOfPosts = new ArrayList<>(1000);
    postsByDate = new TreeMap<>();
    tagsByName = new HashMap<>(200);
  }

  public void load(String path) {
    addUsers(Parser.parseUser(path.concat("/Users.xml")));
    addTags(Parser.parseTag(path.concat("/Tags.xml")));
    addPosts(Parser.parsePost(path.concat("/Posts.xml")));
  }

  public List<User> getUsersByNumberOfPosts() {
    return this.usersByNumberOfPosts;
  }

  public Post getPost(long id) throws PostDoesNotExistException {
    Post p = this.postsById.get(id);
    if (p == null) throw new PostDoesNotExistException();
    else return p;

  }

  public Long getTagId(String tag) {
    Tag t = tagsByName.get(tag);
    if (t != null) return t.getId();
    else return Long.valueOf(0);
  }

  public Set<Answer> getAnswers(Long id) {
    return this.answersByQuestionId.get(id);
  }

  public Integer getAnswerCount(Long id) {
    Set<Answer> answers = answersByQuestionId.get(id);
    if (answers != null) return answers.size();
    else return 0;
  }

  public User getUserById(Long id) throws UserDoesNotExistException {
    if (this.usersById.get(id) == null)
      throw new UserDoesNotExistException(id.toString());
    else
      return this.usersById.get(id);
  }

  public Set<Post> getPostsOfUser(Long id) {
    return this.postsByUserId.get(id);
  }

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
    * Returns a List with all the Questions
  */
  public List<Question> filterQuestionByInterval() {
    return this.postsByDate.values().stream()
    .flatMap(set -> set.stream())
    .filter(p -> p instanceof Question)
    .map(q -> (Question) q)
    .collect(Collectors.toList());
  }

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

  public Set<Post> filterPostsByInterval(LocalDate begin, LocalDate end) {
    Collection<Set<Post>> col = this.postsByDate.subMap(LocalDateTime.of(begin,LocalTime.MIN),LocalDateTime.of(end,LocalTime.MAX)).values();
    if (col == null) return new TreeSet<>();
    else
      return col.stream()
      .flatMap(set -> set.stream())
      .collect(Collectors.toSet());
  }

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
  public String getBio(long id) {
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
  */
  public Set<Question> getQuestions(long id) {
    Set<Post> posts = postsByUserId.get(id);
    if (posts == null) return new TreeSet<>();
    else {
      TreeSet<Question> result = new TreeSet<>();
      for(Post p : posts) {
        if (p instanceof Question) {
          Question q = (Question) p;
          result.add(q);
        }
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
    * @return list of 10 posts
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
    if (!postsByUserId.containsKey(creatorId))
      postsByUserId.put(creatorId,new TreeSet<>(new ComparatorPostInverseChrono()));
    postsByUserId.get(creatorId).add(p);
    User creator = usersById.get(creatorId);
    if (creator != null)
      creator.addPost();
    long id = p.getId();
    if (!postsByDate.containsKey(p.getCreationDate()))
      postsByDate.put(p.getCreationDate(),new TreeSet(new ComparatorPostInverseChrono()));
    postsByDate.get(p.getCreationDate()).add(p);
    postsById.put(id,p);

    if (p instanceof Answer) {
      Answer a = (Answer) p;
      long parentID = a.getParentId();
      if(!answersByQuestionId.containsKey(parentID))
        answersByQuestionId.put(parentID,new TreeSet<>());
      answersByQuestionId.get(parentID).add(a);
    }
    else if (p instanceof Question) {
      Question q = (Question) p;
      if (!answersByQuestionId.containsKey(q.getId()))
        answersByQuestionId.put(q.getId(),new TreeSet<>());
    }
  }


}
