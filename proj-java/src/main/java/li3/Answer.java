package li3;

import java.time.LocalDateTime;

/**
 * Answer is a type of Post
 *
 * @author (your name)
 * @version 2018-05-23
 */
public class Answer extends Post {
  /** Id of Parent */
  private long parentId;
  /** Score */
  private short score;
  /** Number of comments */
  private short comments;

  public Answer() {
    parentId = -1;
    score = 0;
    comments = 0;
  }

  public Answer(String title, long id, LocalDateTime date, long creatorId, long parent, short sc, short com) {
    super(title,id,date,creatorId);
    parentId = parent;
    score = sc;
    comments = com;
  }

  public Answer(Answer a) {
    super(a);
    parentId = a.getParentId();
    score = a.getScore();
    comments = a.getComments();
  }

  public void setParentId(long parent) {
    parentId = parent;
  }

  public long getParentId() {
    return this.parentId;
  }

  public short getScore() {
    return this.score;
  }

  public short getComments() {
    return this.comments;
  }

  public Answer clone() {
    return new Answer(this);
  }

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
