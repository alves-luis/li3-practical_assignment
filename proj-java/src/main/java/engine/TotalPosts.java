package engine;

import li3.Post;
import li3.Question;
import li3.Answer;
import common.Pair;

import java.util.Set;
import java.time.LocalDate;

public class TotalPosts {

  public static Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end, Community com) {
    return com.countPostsBetweenDates(begin,end);
  }

}
