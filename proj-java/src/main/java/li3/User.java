package li3;

import exceptions.UserDoesNotHaveBioException;
import li3.Identifiable;
import common.*;

/**
 * Write a description of class User here.
 *
 * @author (your name)
 * @version 2018-05-23
 */

import java.util.Set;
import java.util.TreeSet;
import java.util.stream.Collectors;

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

  public User() {
    bio = null;
    name = null;
    id = -1;
    reputation = 0;
    numberOfPosts = 0;
  }

  public User(long nid,int nrep,String nname,String nbio) {
    bio = nbio;
    name = nname;
    id = nid;
    reputation = nrep;
    numberOfPosts = 0;
  }

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

  public long getId() {
    return this.id;
  }

  public int getNumberOfPosts() {
    return this.numberOfPosts;
  }

  public String getBio() throws UserDoesNotHaveBioException {
    if (bio == null)
      throw new UserDoesNotHaveBioException(String.valueOf(id));
    else
      return this.bio;
  }

  public String getName() {
    return this.name;
  }

  public int getReputation() {
    return this.reputation;
  }

  public void setId(long id) {
    this.id = id;
  }

  public int compareTo(User u) {
    return Long.compare(this.id,u.getId());
  }

  public void addPost() {
    this.numberOfPosts++;
  }

  public User clone() {
    return new User(this);
  }

  public String toString() {
    StringBuilder sb = new StringBuilder();
    sb.append("Nome: ").append(name);
    sb.append("\nId: ").append(id);
    sb.append("\nRep: ").append(reputation);
    sb.append("\nBio: ").append(bio).append("\n");
    return sb.toString();
  }
}
