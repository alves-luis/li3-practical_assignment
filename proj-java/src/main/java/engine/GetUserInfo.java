package engine;

import li3.User;
import li3.Post;
import common.Pair;
import java.util.List;
import java.util.stream.Collectors;

public class GetUserInfo {
  public static Pair<String, List<Long>> getUserInfo(long id, Community com) {
    String bio = com.getBio(id);
    List<Long> tenPosts = com.get10LatestPosts(id).stream().mapToLong(p -> p.getId()).boxed().collect(Collectors.toList());
    Pair<String, List<Long>> result = new Pair(bio,tenPosts);
    return result;
  }
}
