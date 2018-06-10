package engine;

import java.util.List;
import java.util.Set;
import java.util.stream.Collectors;

import li3.User;
import li3.Question;

public class BothParticipated {
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
