package engine;

import common.*;
import li3.*;
import exceptions.*;

import java.time.LocalDate;
import java.time.Month;

/**
 * Model in MVC
 *
 * @author (seu nome)
 * @version 2018-05-23
 */
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.TreeSet;
import java.util.List;
import java.util.ArrayList;
import java.util.stream.Collectors;

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

  // Query 1
  public Pair<String,String> infoFromPost(long id) {
    return InfoFromPost.infoFromPost(id,community);
  }

  // Query 2
  public List<Long> topMostActive(int N) {
    return TopMostActive.topMostActive(N,community);
  }

  // Query 3
  public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end) {
    return TotalPosts.totalPosts(begin,end,community);
  }

  // Query 4
  public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end) {
    return QuestionsWithTag.questionsWithTag(tag,begin,end,community);
  }

  // Query 5
  public Pair<String, List<Long>> getUserInfo(long id) {
    return GetUserInfo.getUserInfo(id,community);
  }

  // Query 6
  public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end) {
    return MostVotedAnswers.mostVotedAnswers(N,begin,end,community);
  }

  // Query 7
  public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end) {
    return MostAnsweredQuestions.mostAnsweredQuestions(N,begin,end,community);
  }

  // Query 8
  public List<Long> containsWord(int N, String word) {
    return ContainsWord.containsWord(N,word,community);
  }

  // Query 9
  public List<Long> bothParticipated(int N, long id1, long id2) {
    return BothParticipated.bothParticipated(N,id1,id2,community);
  }

  // Query 10
  public long betterAnswer(long id) {
    return BetterAnswer.betterAnswer(id,community);
  }

  // Query 11
  public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end) {
    return MostUsedBestRep.mostUsedBestRep(N,begin,end,community);
  }

  public void clear() {

  }
}
