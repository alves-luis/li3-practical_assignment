package engine;

import li3.Post;
import li3.Question;
import li3.Answer;
import common.Pair;
import java.util.Set;
import java.time.LocalDate;

/**
 * TotalPosts class, stands for Query 3
 *
 * @author Grupo 42
 * @version 2018-06-11
 */
public class TotalPosts {
  /**
    * @param begin Start of the range
    * @param end End of the range
    * @param com Community
    * @return Pair containing the number of questions and answers
  */
  public static Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end, Community com) {
    return com.countPostsBetweenDates(begin,end);
  }

}
