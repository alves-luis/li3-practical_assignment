package engine;

import java.util.stream.Collectors;
import java.util.List;
import java.time.LocalDate;
import li3.Answer;
import common.ComparatorAnswerScore;

/**
 * MostVotedAnswers class, stands for Query 6
 *
 * @author Grupo 42
 * @version 2018-06-11
 */
public class MostVotedAnswers {

  /**
    * Method that implements query MostVotedAnswers
    * @param N size of most active
    * @param begin Starting date
    * @param end Ending date
    * @param com Community
    * @return List with the ids of the most voted answers
  */
  public static List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end, Community com) {
    return com.filterAnswerByInterval(begin,end).stream()
    .sorted(new ComparatorAnswerScore())
    .limit(N)
    .mapToLong(a -> a.getId())
    .boxed()
    .collect(Collectors.toList());
  }
}
