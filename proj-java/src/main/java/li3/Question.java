package li3;

import java.util.Set;
import java.util.List;
import java.util.TreeSet;
import java.util.ArrayList;
import java.util.stream.Collectors;
import java.time.LocalDateTime;

/**
 * Question is a type of Post
 *
 * @author Grupo 42
 * @version 2015-05-23
 */
public class Question extends Post {

  /** List with Tags */
  private List<String> tags;
  /** AnswerCount */
  private int answerCount;

  /**
    * Default constructor
  */
  public Question() {
    tags = new ArrayList<String>();
    answerCount = 0;
  }

  /**
    * Parametrized constructor
    * @param title Title
    * @param id ID
    * @param date Date
    * @param creatorId Creator ID
  */
  public Question(String title,long id,LocalDateTime date,long creatorId) {
    super(title,id,date,creatorId);
    tags = new ArrayList<String>();
    answerCount = 0;
  }

  /**
    * Copy constructor
    * @param q Question
  */
  public Question(Question q) {
    super(q);
    tags = q.getTags();
    answerCount = q.getAnswerCount();
  }

  /**
    * Tags getter
    * @return List of tags
  */
  public List<String> getTags() {
    return this.tags.stream()
    .collect(Collectors.toList());
  }

  /**
    * AnswerCount getter
    * @return Int answer count
  */
  public int getAnswerCount() {
    return this.answerCount;
  }

  /**
    * AnswerCount setter
    * @param a new answer count
  */
  public void setAnswerCount(int a) {
    answerCount = a;
  }

  /**
    * Adds a tag to the question
    * @param t new tag to add
  */
  public void addTag(String t) {
    this.tags.add(t);
  }

  /**
    * Adds a list of tags to another one
    * @param t List of tags
  */
  public void addTags(List<String> t) {
    this.tags = t;
  }

  /**
    * Clone method
    * @return Object with type Question
  */
  public Question clone() {
    return new Question(this);
  }

  /**
    * Equals method
    * @param o Object compared to question
    * @return True or false boolean
  */
  public boolean equals(Object o) {
    if (this == o)
      return true;
    if (o == null || o.getClass() != this.getClass())
      return false;
    Question a = (Question) o;
    return super.equals(a);
  }
}
