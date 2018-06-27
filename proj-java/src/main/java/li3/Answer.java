package li3;

import java.time.LocalDateTime;

/**
 * Answer is a type of Post
 *
 * @author Grupo 42
 * @version 2018-05-23
 */
public class Answer extends Post {
  /** Id of Parent */
  private long parentId;
  /** Score */
  private short score;
  /** Number of comments */
  private short comments;

  /**
    * Default constructor
  */
  public Answer() {
    parentId = -1;
    score = 0;
    comments = 0;
  }

  /**
    * Parametrized constructor
    * @param title Title
    * @param id ID
    * @param date Date
    * @param creatorId Creator ID
    * @param parent Parent ID
    * @param sc Score
    * @param com Number of comments
  */
  public Answer(String title, long id, LocalDateTime date, long creatorId, long parent, short sc, short com) {
    super(title,id,date,creatorId);
    parentId = parent;
    score = sc;
    comments = com;
  }

  /**
    * Copy constructor
    * @param a Answer
  */
  public Answer(Answer a) {
    super(a);
    parentId = a.getParentId();
    score = a.getScore();
    comments = a.getComments();
  }

  /**
    * Parent ID setter
    * @param parent Parent ID
  */
  public void setParentId(long parent) {
    parentId = parent;
  }

  /**
    * Parent ID getter
    * @return Parent ID
  */
  public long getParentId() {
    return this.parentId;
  }

  /**
    * Score getter
    * @return Score
  */
  public short getScore() {
    return this.score;
  }

  /**
    * Comments getter
    * @return Number of comments
  */
  public short getComments() {
    return this.comments;
  }

  /**
    * Clone method
    * @return Object with type Answer
  */
  public Answer clone() {
    return new Answer(this);
  }

  /**
    * Equals method
    * @param o Object compared to answer 
    * @return True or false boolean
  */
  public boolean equals(Object o) {
    if (this == o)
      return true;
    if (o == null || o.getClass() != this.getClass())
      return false;
    Answer a = (Answer) o;
    return super.equals(o) && parentId == a.getParentId()
           && score == a.getScore() &&
           comments == a.getComments();
  }
}
