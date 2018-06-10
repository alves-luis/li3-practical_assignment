package engine;

import java.util.stream.Collectors;
import java.util.List;
import li3.User;

public class TopMostActive {
  /**
    * @param N size of most active
    * @param com Community
  */
  public static List<Long> topMostActive(int N, Community com) {
    return com.getUsersByNumberOfPosts().stream()
    .limit(N)
    .mapToLong(User::getId)
    .boxed()
    .collect(Collectors.toList());
  }
}
