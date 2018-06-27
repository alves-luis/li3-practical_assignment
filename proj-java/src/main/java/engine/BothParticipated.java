package engine;

import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

import li3.User;
import li3.Question;

/**
  * Class that implements query BothParticipated
  * @author Grupo 42
  * @version 2018-12-06
*/
public class BothParticipated {

  /**
    * Returns a list with the ids of the questions where both users participated
    * @param N size of list
    * @param id1 id of user 1
    * @param id2 id of user 2
    * @param com TCD
    * @return List with the ids
  */
  public static List<Long> bothParticipated(int N, long id1, long id2, Community com) {
    Set<Question> questionsFirstUser = com.getQuestions(id1);
    Set<Question> questionsSecondUser = com.getQuestions(id2);
    return questionsFirstUser.stream()
    .filter(q -> questionsSecondUser.contains(q))
    .sorted()
    .limit(N)
    .mapToLong(Question::getId)
    .boxed()
    .collect(Collectors.toList());
  }
}
