package engine;

import java.util.stream.Collectors;
import java.util.List;
import li3.User;

public class TopMostActive {
  /**
    * @param N size of most active
    * @param users List of users by number of posts
  */
  public static List<Long> topMostActive(int N, List<User> users) {
    return users.stream()
    .limit(N)
    .mapToLong(User::getId)
    .boxed()
    .collect(Collectors.toList());
  }
}
