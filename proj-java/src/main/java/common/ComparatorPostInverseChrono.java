package common;

import li3.Post;

/**
  * Comparator of Posts by Date (Inverse Chronological Order)
  *
  * @author Grupo 42
  * @version 2018-05-23
*/
import java.util.Comparator;
import java.time.LocalDateTime;

public class ComparatorPostInverseChrono implements Comparator<Post> {
  /**
    * Compares two Posts by date
    * @param p1 Post 1
    * @param p2 Post 2
    * @return int of comparison (if equal, then compares by Id)
  */
  public int compare(Post p1, Post p2) {
    LocalDateTime d1 = p1.getCreationDate();
    LocalDateTime d2 = p2.getCreationDate();
    int comparison = d2.compareTo(d1);
    if (comparison == 0) return Long.compare(p2.getId(),p1.getId());
    else return comparison;
  }
}
