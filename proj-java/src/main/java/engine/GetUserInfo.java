package engine;

import li3.User;
import li3.Post;
import common.Pair;
import java.util.List;
import java.util.stream.Collectors;

/**
  * Class that implements query GetUserInfo
  * @author Grupo 42
  * @version 2018-12-06
*/
public class GetUserInfo {

  /**
    * Method that retrieves a pair with the bio and ids of 10 latest posts
    * @param id id of user
    * @param com Community
    * @return Pair, with bio and list of ids
  */
  public static Pair<String, List<Long>> getUserInfo(long id, Community com) {
    String bio = com.getBio(id);
    List<Long> tenPosts = com.get10LatestPosts(id).stream().mapToLong(p -> p.getId()).boxed().collect(Collectors.toList());
    Pair<String, List<Long>> result = new Pair(bio,tenPosts);
    return result;
  }
}
