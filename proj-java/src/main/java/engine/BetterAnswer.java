package engine;

import java.util.stream.Collectors;
import java.util.Set;
import java.util.TreeMap;
import java.util.TreeSet;
import java.util.Comparator;

import li3.Answer;
import li3.User;
import exceptions.UserDoesNotExistException;

public class BetterAnswer {
  /**
    * @param com Community
    * @return id of the best answer
  */
  public static long betterAnswer(long id, Community com) {
    Set<Answer> answers = com.getAnswers(id);
    if (answers == null) return -1;
    else {
      TreeMap<Double,Set<Long>> result = new TreeMap<>(Comparator.reverseOrder());
      for(Answer a : answers) {
        double score = a.getScore()*0.65;
        double rep;
        try {
          User creator = com.getUserById(a.getCreatorId());
          rep = creator.getReputation()*0.25;
        }
        catch (UserDoesNotExistException e) {
          rep = 0;
        }
        double coms = a.getComments()*0.1;
        Double finalScore = Double.valueOf(score + rep + coms);
        if (!result.containsKey(finalScore))
          result.put(finalScore, new TreeSet<Long>());
        result.get(finalScore).add(a.getId());
      }
    TreeSet<Long> finalSet = (TreeSet) result.firstEntry().getValue();
    if (finalSet == null) return -1;
    else {
      Long finalId = finalSet.first();
      return finalId.longValue();
    }
    }
  }
}
