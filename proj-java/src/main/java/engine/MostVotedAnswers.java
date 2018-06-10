package engine;

import java.util.stream.Collectors;
import java.util.List;
import java.time.LocalDate;
import li3.Answer;
import common.ComparatorAnswerScore;

public class MostVotedAnswers {

  public static List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end, Community com) {
    return com.filterAnswerByInterval(begin,end).stream()
    .sorted(new ComparatorAnswerScore())
    .limit(N)
    .mapToLong(a -> a.getId())
    .boxed()
    .collect(Collectors.toList());
  }
}
