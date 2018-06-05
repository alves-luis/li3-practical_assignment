package engine;

import common.*;
import li3.*;
import exceptions.*;

import java.time.LocalDate;
import java.time.Month;

/**
 * Model in MVC
 *
 * @author (seu nome)
 * @version 2018-05-23
 */
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.TreeSet;
import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

public class ForumsModel implements TADCommunity {

  /** They all share pointers */
  private Map<Long,User> usersById;
  private Map<Long,Post> postsById;
  private Map<Long,Set<Answer>> answersByQuestionId;
  private Map<Long,Set<Post>> postsByUserId;
  private List<User> usersByNumberOfPosts;
  private Set<Post> postsByDate;
  private Map<String,Tag> tagsByName;

  public ForumsModel() {
    usersById = new HashMap<>(1000);
    postsById = new HashMap<>(1000);
    answersByQuestionId = new HashMap<>(500);
    postsByUserId = new HashMap<>(1000);
    usersByNumberOfPosts = new ArrayList<>(1000);
    postsByDate = new TreeSet<>(new ComparatorPostInverseChrono());
    tagsByName = new HashMap<>(200);
  }

  /**
    * Loads from the path_file
    * !!Change from temp to variable path!!
    * @param path
  */
  public void load(String path) {
    addUsers(Parser.parseUser("./Files/Users.xml"));
    addTags(Parser.parseTag("./Files/Tags.xml"));
    addPosts(Parser.parsePost("./Files/Posts.xml"));
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
  private void insertPost(Post orig) {
    Post p = orig;
    long creatorId = p.getCreatorId();
    if (!postsByUserId.containsKey(creatorId))
      postsByUserId.put(creatorId,new TreeSet<>(new ComparatorPostInverseChrono()));
    postsByUserId.get(creatorId).add(orig);
    User creator = usersById.get(creatorId);
    if (creator != null)
      creator.addPost();
    long id = p.getId();
    postsByDate.add(p);
    postsById.put(id,p);
    // Falta cenas específicas de questão/resposta
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

  /**
    * Inserts a List of Users into the system
    * @param l List of users
  */
  private void addUsers(List<User> l) {
    l.stream().forEach(u -> this.insertUser(u));
  }

  /**
    * Inserts a List of Tags into the system
    * @param l List of Tags
  */
  private void addTags(List<Tag> l) {
    l.stream().forEach(t -> this.insertTag(t));
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
    * Verifies if a User exists
    * @param id id of User
    * @return boolean
  */
  private boolean userExists(long id) {
    return this.usersById.containsKey(id);
  }

  /**
    * Gets a User from the system, given its Id
    * @param id
    * @return User
  */
  private User getUser(long id) throws UserDoesNotExistException {
    User result = this.usersById.get(id);
    if (result != null)
      return result.clone();
    else
      throw new UserDoesNotExistException(String.valueOf(id));
  }

  /**
    * Gets a Post from the system, given its Id
    * @param id
    * @return Post
  */
  private Post getPost(long id) throws PostDoesNotExistException {
    Post result = this.postsById.get(id);
    if (result != null)
      return result.clone();
    else
      throw new PostDoesNotExistException(String.valueOf(id));
  }

  /**
    * Gets the id of a Tag by its String
    * @param tagName String
    * @return id of tag
  */
  private Long getTagId(String tagName) {
    return this.tagsByName.get(tagName).getId();
  }

  // Query 1
  public Pair<String,String> infoFromPost(long id) {
    return null;
  }

  /**
    * Returns a List of Ids with the most active Users
    * @param N top active
    * @return List
  */
  public List<Long> topMostActive(int N) {
    return TopMostActive.topMostActive(N,usersByNumberOfPosts);
  }

  // Query 3
  public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end) {
    return null;
  }

  // Query 4
  public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {
    return null;
  }

  // Query 5
  public Pair<String, List<Long>> getUserInfo(long id) {
    return null;
  }

  // Query 6
  public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {
    return null;
  }

  private List<Long> filterQuestionByInterval(LocalDate begin, LocalDate end) {
    return this.postsByDate.stream()
    .filter(p -> (p instanceof Question) && ((p.getCreationDate().toLocalDate().isAfter(begin) && p.getCreationDate().toLocalDate().isBefore(end)) || p.getCreationDate().toLocalDate().equals(begin) || p.getCreationDate().toLocalDate().equals(end)))
    .map(Post::clone)
    .mapToLong(Post::getId)
    .boxed()
    .collect(Collectors.toList());
  }

  // Query 7
  public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {
    List<Long> questions = this.filterQuestionByInterval(begin,end);
    return MostAnsweredQuestions.mostAnsweredQuestions(N,questions,answersByQuestionId);
  }

  // Query 8
  public List<Long> containsWord(int N, String word) {
    return null;
  }

  // Query 9
  public List<Long> bothParticipated(int N, long id1, long id2) {
    return null;
  }

  // Query 10
  public long betterAnswer(long id) {
    return 0;
  }

  private Set<Post> filterPostsByInterval(LocalDate begin, LocalDate end) {
    return this.postsByDate.stream()
    .filter(p -> (p.getCreationDate().toLocalDate().isAfter(begin) && p.getCreationDate().toLocalDate().isBefore(end)) || p.getCreationDate().toLocalDate().equals(begin) || p.getCreationDate().toLocalDate().equals(end))
    .collect(Collectors.toSet());
  }

  // Query 11
  public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {
    Set<Post> posts = this.filterPostsByInterval(begin,end);
    return MostUsedBestRep.mostUsedBestRep(N,tagsByName,usersById,posts,postsByUserId,postsById);
  }

  public void clear() {

  }
}
