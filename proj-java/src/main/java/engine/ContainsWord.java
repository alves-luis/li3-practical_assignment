package engine;

import li3.Question;
import common.ComparatorPostInverseChrono;

import java.util.List;
import java.util.stream.Collectors;

/**
  * Class that implements ContainsWord query
  * @author Grupo 42
  * @version 2018-12-06
*/
public class ContainsWord {

  /**
    * Method that implements query ContainsWord
    * @param N size of list
    * @param word word to search on the title
    * @param com Database
    * @return List with the ids of the questions that contain given word
  */
  public static List<Long> containsWord(int N, String word, Community com) {
    List<Question> questions = com.filterQuestionByInterval();
    if (questions == null) return null;
    return questions.stream()
    .filter(q -> q.getTitle() != null && q.getTitle().contains(word))
    .sorted(new ComparatorPostInverseChrono())
    .limit(N)
    .mapToLong(q -> q.getId())
    .boxed()
    .collect(Collectors.toList());
  }
}
