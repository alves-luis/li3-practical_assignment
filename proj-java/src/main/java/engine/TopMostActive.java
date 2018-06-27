package engine;

import java.util.stream.Collectors;
import java.util.List;
import li3.User;

/**
 * TopMostActive class, stands for Query 2
 *
 * @author Grupo 42
 * @version 2018-06-11
 */
public class TopMostActive {
  /**
    * @param N size of most active
    * @param com Community
    * @return List containing the N most active users
  */
  public static List<Long> topMostActive(int N, Community com) {
    return com.getUsersByNumberOfPosts(N).stream()
    .mapToLong(User::getId)
    .boxed()
    .collect(Collectors.toList());
  }
}
