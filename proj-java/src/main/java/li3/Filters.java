package li3;

import java.util.List;
import java.util.Set;
import java.time.LocalDate;

import common.Pair;

/**
  * Interface that TCD must implement, with filters associated with timeframes
  * @author Grupo 42
  * @version 2018-11-06
*/

public interface Filters {
  
  public List<Question> filterQuestionByInterval(LocalDate begin, LocalDate end);
  public List<Question> filterQuestionByInterval();
  public List<Answer> filterAnswerByInterval(LocalDate begin, LocalDate end);
  public Set<Post> filterPostsByInterval(LocalDate begin, LocalDate end);
  public Pair<Long,Long> countPostsBetweenDates(LocalDate begin, LocalDate end);
}
