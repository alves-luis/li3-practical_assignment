package engine;

import java.util.stream.Collectors;
import java.util.List;
import li3.Question;
import common.ComparatorLongIntEntryReverseInt;
import java.util.Comparator;
import java.util.Map;
import java.util.Set;
import java.time.LocalDate;
import java.util.HashMap;

public class MostAnsweredQuestions {
  /**
    * @param N size
    * @param begin LocalDate that begins
    * @param end LocalDate of ending
  */
  public static List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end, Community com) {
    List<Question> questions = com.filterQuestionByInterval(begin,end);
    HashMap<Long,Integer> result = new HashMap<>();
    for(Question question : questions) {
      long questionID = question.getId();
      int count = question.getAnswerCount();
      result.put(questionID,count);
    }
    return result.entrySet().stream()
    .sorted(new ComparatorLongIntEntryReverseInt())
    .limit(N)
    .mapToLong(en -> en.getKey())
    .boxed()
    .collect(Collectors.toList());
  }
}
