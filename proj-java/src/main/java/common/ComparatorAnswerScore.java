package common;

import li3.Answer;

/**
  * Comparator of Answers by Score
  *
  * @author Grupo 42
  * @version 2018-05-23
*/
import java.util.Comparator;

public class ComparatorAnswerScore implements Comparator<Answer> {
  /**
    * Compares two Answers by score
    * @param a1 Answer 1
    * @param a2 Answer 2
    * @return int of comparison (if equal, then compares by Id)
  */
  public int compare(Answer a1, Answer a2) {
    short s1 = a1.getScore();
    short s2 = a2.getScore();
    int comparison = s2 - s1;
    if (comparison == 0) return Long.compare(a2.getId(),a1.getId());
    else return comparison;
  }
}
