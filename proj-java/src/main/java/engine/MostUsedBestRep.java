package engine;

import java.util.stream.Collectors;
import java.util.List;
import li3.Post;
import li3.User;
import li3.Tag;
import li3.Question;
import li3.Answer;
import li3.Tag;
import common.ComparatorUserReputation;
import common.ComparatorLongIntEntry;
import java.util.Map;
import java.util.Set;
import java.util.HashSet;
import java.util.TreeSet;
import java.util.TreeMap;
import java.util.HashMap;
import java.util.Comparator;
import java.time.LocalDate;
import exceptions.UserDoesNotExistException;
import exceptions.PostDoesNotExistException;


/**
 * MostUsedBestRep class, stands for Query 11
 *
 * @author Grupo 42
 * @version 2018-06-11
 */
public class MostUsedBestRep {

  /**
    * Given a set of posts, returns a list with all the users who posted them,
    * truncated to N
    * @param N max size of return list
    * @param com Community
    * @param posts Set of posts to analyze
    * @return List of users
  */
  private static List<User> usersThatParticipated(int N, Community com , Set<Post> posts) {
    TreeSet<User> usersThatParticipated = new TreeSet<>(new ComparatorUserReputation());
    for(Post p : posts) {
      long id = p.getCreatorId();
      try {
        User participated = com.getUserById(id);
        usersThatParticipated.add(participated);
      }
      catch (UserDoesNotExistException e) {
        continue;
      }
    }
    return usersThatParticipated.stream().limit(N).collect(Collectors.toList());
  }

  /**
    * Method that implements the query
    * @param N size of most active
    * @param begin Starting date
    * @param end Ending date
    * @param com Community
    * @return list with the ids
  */
  public static List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end, Community com) {
    Set<Post> posts = com.filterPostsByInterval(begin,end);
    // Has the posts in that period
    List<User> finalListOfUsers = usersThatParticipated(N,com,posts);
    // list has the users ordered by rep
    HashMap<Long,Integer> timesTagUsedById = new HashMap<>();
    //For each user, check his posts
    for (User u : finalListOfUsers) {
      Set<Post> postsOfUser = com.getPostsOfUser(u.getId());
      // For each post, verify if it's question and, if it is, verify if part of posts
      for(Post p : postsOfUser) {
        if (p instanceof Question) {
          if (posts.contains(p)) {
            Question q = (Question) p;
            List<String> usedTags = q.getTags();
            // everything matches, so add used strings to map
            for (String s : usedTags) {
              Long tagId = com.getTagId(s);
              int count;
              if (!timesTagUsedById.containsKey(tagId))
                timesTagUsedById.put(tagId,1);
              else {
                count = (timesTagUsedById.get(tagId)) + 1;
                timesTagUsedById.put(tagId,count);
              }
            }
          }
        }
      }
    }
    // all is collected, so now need to compare and limit to N
    return timesTagUsedById.entrySet().stream()
    .sorted(new ComparatorLongIntEntry())
    .limit(N)
    .mapToLong(entry -> entry.getKey())
    .boxed()
    .collect(Collectors.toList());
  }
}
