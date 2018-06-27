package common;

import li3.User;

/**
  * Comparator of Users by Reputation (biggest rep first)
  * biggest id first then
  *
  * @author Grupo 42
  * @version 2018-05-23
*/
import java.util.Comparator;

public class ComparatorUserReputation implements Comparator<User> {
  /**
    * Compares two Users by number of posts
    * @param u1 User 1
    * @param u2 User 2
    * @return int of comparison (if equal, then compares by Id)
  */
  public int compare(User u1, User u2) {

    int comparison = u2.getReputation() - u1.getReputation();
    if (comparison == 0) return Long.compare(u2.getId(),u1.getId());
    else return comparison;
  }
}
