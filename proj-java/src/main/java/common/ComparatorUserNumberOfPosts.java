package common;

import li3.User;

/**
  * Comparator of Users by Number of Posts (Mosts posts first)
  * Then compares by id
  *
  * @author Grupo 42
  * @version 2018-05-23
*/
import java.util.Comparator;
import java.time.LocalDateTime;

public class ComparatorUserNumberOfPosts implements Comparator<User> {
  /**
    * Compares two Users by number of posts
    * @param u1 User 1
    * @param u2 User 2
    * @return int of comparison (if equal, then compares by Id)
  */
  public int compare(User u1, User u2) {

    int comparison = u2.getNumberOfPosts() - u1.getNumberOfPosts();
    if (comparison == 0) return Long.compare(u2.getId(),u1.getId());
    else return comparison;
  }
}
