package li3;

import java.util.List;

/**
  * Interface that TCD must implement for query TopMostActive
  * @author Grupo 42
  * @version 2018-11-06
  * @see engine.TopMostActive
*/
public interface MostActive {

  /**
    * Given a max N, returns a List of Users ordered by number of posts
    * @param N size of List
    * @return List of Users
    * @see User
  */
  public List<User> getUsersByNumberOfPosts(int N);
}
