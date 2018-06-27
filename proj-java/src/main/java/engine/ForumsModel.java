package engine;

import common.Pair;
import li3.TADCommunity;

/**
 * Class that implements TADCommunity
 *
 * @author Grupo 42
 * @version 2018-05-23
 */
import java.util.List;
import java.time.LocalDate;
import java.time.Month;

public class ForumsModel implements TADCommunity {

  /** Where all the stuff is stored */
  private Community community;

  public ForumsModel() {
    community = new Community();
  }

  /**
    * Loads from the path_file
    * @param path
  */
  public void load(String path) {
    community.load(path);
  }

  /**
    * Title and author's username of a post (given its ID)
    * @param id Post ID
    * @return Pair of strings containing the post title and author's username
  */
  public Pair<String,String> infoFromPost(long id) {
    return InfoFromPost.infoFromPost(id,community);
  }

  /**
    * Top N users with more posts made ever
    * @param N Number of users
    * @return List containing the N user ID's calculated
  */
  public List<Long> topMostActive(int N) {
    return TopMostActive.topMostActive(N,community);
  }

  /**
    * Total number of posts between a given interval
    * @param begin Start of the range
    * @param end End of the range
    * @return Pair containing the number of questions and answers respectively
  */
  public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end) {
    return TotalPosts.totalPosts(begin,end,community);
  }

/**
  * All questions containing a given tag between an either given interval
  * @param tag Tag
  * @param begin Start of the range
  * @param end End of the range
  * @return List of questions from fresher to older
*/
  public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {
    return QuestionsWithTag.questionsWithTag(tag,begin,end,community);
  }

  /**
    * Given a User ID, returns the profile bio of said user, as well as the ID's of his 10 last posts
    * @param id User ID
  */
  public Pair<String, List<Long>> getUserInfo(long id) {
    return GetUserInfo.getUserInfo(id,community);
  }

/**
  * The N most voted answers in an interval of time (sorted decreasingly)
  * @param N Number of answers
  * @param begin Start of the range
  * @param end End of the range
  * @return List of answers sorted by votes
*/
  public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {
    return MostVotedAnswers.mostVotedAnswers(N,begin,end,community);
  }

/**
  * The N most answered questions in an interval of time (sorted decreasingly)
  * @param N Number of questions
  * @param begin Start of the range
  * @param end End of the range
  * @return List of questions sorted by the number of answers
*/
  public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {
    return MostAnsweredQuestions.mostAnsweredQuestions(N,begin,end,community);
  }

  /**
    * List of Questions that contain a certain word
    * @param N Number of questions
    * @param word Word to look for
  */
  public List<Long> containsWord(int N, String word) {
    return ContainsWord.containsWord(N,word,community);
  }

  /**
    * Last N questions where 2 given users both participated
    * @param N Number of questions
    * @param id1 Id of first user
    * @param id2 Id of second user
  */
  public List<Long> bothParticipated(int N, long id1, long id2) {
    return BothParticipated.bothParticipated(N,id1,id2,community);
  }

  /**
    * Given a question id returns the better answer
    * @param id Question id
  */
  public long betterAnswer(long id) {
    return BetterAnswer.betterAnswer(id,community);
  }

/**
  * The N tags most used by the N most reputed users in an interval of time (sorted decreasingly)
  * @param N Number of answers
  * @param begin Start of the range
  * @param end End of the range
  * @return List of tags sorted by the number of times used
*/
  public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {
    return MostUsedBestRep.mostUsedBestRep(N,begin,end,community);
  }

  /**
    * Clears memory, sets the instance variable to null, so gc can clean it up
  */
  public void clear() {
    community = null;
  }
}
