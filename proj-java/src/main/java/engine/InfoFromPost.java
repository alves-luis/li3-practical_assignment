package engine;

import common.Pair;
import li3.Post;
import li3.Question;
import li3.User;
import li3.Answer;
import exceptions.PostDoesNotExistException;
import exceptions.UserDoesNotExistException;

/**
 * InfoFromPost class, stands for Query 1
 *
 * @author Grupo 42
 * @version 2018-06-11
 */
public class InfoFromPost {
  /**
    * @param id ID
    * @param com Community
    * @return Pair with the post title and author's username
  */
  public static Pair<String,String> infoFromPost(long id, Community com) {
    try {
      Post p = com.getPost(id);
      String title = null;
      String name = null;
      // If answers, get the question
      if (p instanceof Answer) {
        Answer a = (Answer) p;
        Question father = (Question) com.getPost(a.getParentId());
        if (father != null) {
          title = father.getTitle();
          name = com.getUserById(father.getCreatorId()).getName();
        }
      }
      else {
        title = p.getTitle();
        name = com.getUserById(p.getCreatorId()).getName();
      }
      return new Pair(title,name);
    }
    catch (PostDoesNotExistException e) {
      return new Pair(null,null);
    }
    catch (UserDoesNotExistException e) {
      return new Pair(null,null);
    }
  }
}
