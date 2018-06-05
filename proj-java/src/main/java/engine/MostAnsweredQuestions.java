package engine;

import java.util.stream.Collectors;
import java.util.List;
import li3.Answer;
import common.ComparatorLongIntEntryReverseInt;
import java.util.Comparator;
import java.util.Map;
import java.util.Set;
import java.time.LocalDate;
import java.util.HashMap;

public class MostAnsweredQuestions {
  /**
    * @param N size
    * @param questions Id of questions
    * @param answers map of question id, to answer
  */
  public static List<Long> mostAnsweredQuestions(int N,List<Long> questions, Map<Long,Set<Answer>> answers) {
    HashMap<Long,Integer> result = new HashMap<>();
    for(Long questionID : questions) {
      result.put(questionID,answers.get(questionID).size());
    }
    return result.entrySet().stream()
    .sorted(new ComparatorLongIntEntryReverseInt())
    .limit(N)
    .mapToLong(en -> en.getKey())
    .boxed()
    .collect(Collectors.toList());
  }
}
