package engine;

import li3.Question;
import common.ComparatorPostInverseChrono;

import java.util.List;
import java.util.stream.Collectors;

public class ContainsWord {
  public static List<Long> containsWord(int N, String word, Community com) {
    List<Question> questions = com.filterQuestionByInterval();
    return questions.stream()
    .filter(q -> q.getTitle() != null && q.getTitle().contains(word))
    .sorted(new ComparatorPostInverseChrono())
    .limit(N)
    .mapToLong(q -> q.getId())
    .boxed()
    .collect(Collectors.toList());
  }
}
