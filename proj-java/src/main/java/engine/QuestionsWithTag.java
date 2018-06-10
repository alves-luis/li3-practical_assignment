package engine;

import li3.Question;
import common.ComparatorPostInverseChrono;

import java.util.stream.Collectors;
import java.util.List;
import java.time.LocalDate;


public class QuestionsWithTag {
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
