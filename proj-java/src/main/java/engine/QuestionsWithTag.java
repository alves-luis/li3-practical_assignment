package engine;

import li3.Question;
import common.ComparatorPostInverseChrono;
import java.util.stream.Collectors;
import java.util.List;
import java.time.LocalDate;

/**
 * QuestionsWithTag class, stands for Query 4
 *
 * @author Grupo 42
 * @version 2018-06-11
 */
public class QuestionsWithTag {
  /**
    * @param tag Tag
    * @param begin Start of the range
    * @param end End of the range
    * @param com Community
    * @return List containing the question ID's
  */
  public static List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end, Community com) {
    List<Question> questions = com.filterQuestionByInterval(begin,end);
    return questions.stream()
    .filter(q -> q.getTags().contains(tag))
    .sorted(new ComparatorPostInverseChrono())
    .mapToLong(q -> q.getId())
    .boxed()
    .collect(Collectors.toList());
  }
}
