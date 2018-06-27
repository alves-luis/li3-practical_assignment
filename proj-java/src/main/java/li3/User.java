package li3;

import exceptions.UserDoesNotHaveBioException;
import li3.Identifiable;
import common.*;
import java.util.Set;
import java.util.TreeSet;
import java.util.stream.Collectors;

/**
 * User class
 *
 * @author Grupo 42
 * @version 2018-05-23
 */
public class User implements Comparable<User>, Identifiable{
  /** Bio of user */
  private String bio;
  /** Username */
  private String name;
  /** Id */
  private long id;
  /** Reputation */
  private int reputation;
  /** Number of posts */
  private int numberOfPosts;

  /**
    * Default constructor
  */
  public User() {
    bio = null;
    name = null;
    id = -1;
    reputation = 0;
    numberOfPosts = 0;
  }

  /**
    * Parametrized constructor
    * @param nid User ID
    * @param nrep Reputation
    * @param nname Username
    * @param nbio User biography
  */
  public User(long nid,int nrep,String nname,String nbio) {
    bio = nbio;
    name = nname;
    id = nid;
    reputation = nrep;
    numberOfPosts = 0;
  }

  /**
    * Copy constructor
    * @param u User
  */
  public User(User u) {
    try {
      bio = u.getBio();
    }
    catch (UserDoesNotHaveBioException e) {
      bio = null;
    }
    name = u.getName();
    id = u.getId();
    reputation = u.getReputation();
    numberOfPosts = u.getNumberOfPosts();
  }

  /**
    * User ID getter
    * @return ID
  */
  public long getId() {
    return this.id;
  }

  /**
    * Number of posts getter
    * @return Number of posts
  */
  public int getNumberOfPosts() {
    return this.numberOfPosts;
  }

  /**
    * User biography getter
    * @return User bio
  */
  public String getBio() throws UserDoesNotHaveBioException {
    if (bio == null)
      throw new UserDoesNotHaveBioException(String.valueOf(id));
    else
      return this.bio;
  }

  /**
    * Username getter
    * @return Username
  */
  public String getName() {
    return this.name;
  }

  /**
    * User reputation getter
    * @return Reputation
  */
  public int getReputation() {
    return this.reputation;
  }

  /**
    * User ID setter
    * @param id ID
  */
  public void setId(long id) {
    this.id = id;
  }

  /**
    * Compare ID's
    * @param u User
    * @return 1 if True, 0 if False
  */
  public int compareTo(User u) {
    return Long.compare(this.id,u.getId());
  }

  /**
    * Adds a post to a user
  */
  public void addPost() {
    this.numberOfPosts++;
  }

  /**
    * Clone method
    * @return Object with type User
  */
  public User clone() {
    return new User(this);
  }

  /**
    * ToString method
    * @return String containing all the info of the user
  */
  public String toString() {
    StringBuilder sb = new StringBuilder();
    sb.append("Nome: ").append(name);
    sb.append("\nId: ").append(id);
    sb.append("\nRep: ").append(reputation);
    sb.append("\nBio: ").append(bio).append("\n");
    return sb.toString();
  }
}
