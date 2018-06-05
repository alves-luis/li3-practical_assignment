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
import java.util.ArrayList;
import java.util.TreeMap;
import java.util.HashMap;
import java.util.Comparator;

public class MostUsedBestRep {

  private static List<User> usersThatParticipated(int N, Map<Long,User> users, Set<Post> posts) {
    ArrayList<User> usersThatParticipated = new ArrayList<>();
    for(Post p : posts) {
      long id = p.getCreatorId();
      User participated = users.get(id);
      usersThatParticipated.add(participated);
    }
    usersThatParticipated.sort(new ComparatorUserReputation());
    return usersThatParticipated.subList(0,N);
  }

  /**
    * @param N size of most active
    * @param users List of users by number of posts
  */
  public static List<Long> mostUsedBestRep(int N, Map<String,Tag> tags,Map<Long,User> users, Set<Post> posts, Map<Long,Set<Post>> postsByUser, Map<Long,Post> postsById) {
    List<User> finalListOfUsers = usersThatParticipated(N,users,posts);
    HashMap<Long,Integer> timesTagUsedById = new HashMap<>();
    for (User u : finalListOfUsers) {
      Set<Post> postsOfUser = postsByUser.get(u.getId());
      for(Post p : postsOfUser) {
        if (posts.contains(p)) {
          if (p instanceof Question) {
            Question q = (Question) p;
            List<String> usedTags = q.getTags();
            for (String s : usedTags) {
              Long tagId = tags.get(s).getId();
              int count = 0;
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
    return timesTagUsedById.entrySet().stream()
    .sorted(new ComparatorLongIntEntry())
    .limit(N)
    .mapToLong(entry -> entry.getKey())
    .boxed()
    .collect(Collectors.toList());
  }
}
