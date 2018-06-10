package li3;

import li3.Identifiable;
/**
 * Post
 *
 * @author (your name)
 * @version (a version number or a date)
 */

import java.time.LocalDateTime;
import java.time.LocalDate;

public class Post implements Comparable<Post>, Identifiable {
    /** Title of the Post */
    String title;
    /** ID of the Post */
    long id;
    /** DateTime of the creation date */
    LocalDateTime creationDate;
    /** Id of the Creator */
    long creatorId;

    public Post() {
      this.title = null;
      this.id = -99;
      this.creationDate = LocalDateTime.now();
      this.creatorId = -1;
    }

    public Post(String title, long postId, LocalDateTime date, long creator) {
      this.title = title;
      this.id = postId;
      this.creationDate = date;
      this.creatorId = creator;
    }

    public Post(Post p) {
      title = p.getTitle();
      id = p.getId();
      creationDate = p.getCreationDate();
      creatorId = p.getCreatorId();
    }

    /**
      * @return Title (can be null)
    */
    public String getTitle() {
      return title;
    }

    public long getId() {
      return this.id;
    }

    public long getCreatorId() {
      return this.creatorId;
    }

    public LocalDateTime getCreationDate() {
      return this.creationDate;
    }

    public LocalDate getLocalDate() {
      return this.creationDate.toLocalDate();
    }

    public void setTitle(String tit) {
      title = tit;
    }

    public void setId(long newId) {
      id = newId;
    }

    public void setCreationDate(Integer year, Integer month, Integer day, Integer hour, Integer minute, Integer second, Integer nano) {
      creationDate = LocalDateTime.of(year,month,day,hour,minute,second,nano);
    }

    public void setCreatorId(long cId) {
      creatorId = cId;
    }

    public String toString() {
      StringBuilder sb = new StringBuilder();
      sb.append("\nId: ").append(id);
      sb.append("\nTitle: ").append(title);
      sb.append("\nCreatorId: ").append(creatorId);
      sb.append("\nCreationDate: ").append(creationDate);

      return sb.toString();
    }

    public boolean equals(Object o) {
      if (o == this)
        return true;
      if (o == null || o.getClass() != this.getClass())
        return false;
      Post p = (Post) o;
      boolean titleBool = true;
      String pTitle = p.getTitle();
      if (this.title == null) titleBool = false;
      else titleBool = title.equals(pTitle);

      return this.id == p.getId() && titleBool &&
             this.creationDate.equals(p.getCreationDate()) &&
             this.creatorId == p.getCreatorId();
    }

    public Post clone() {
      return new Post(this);
    }

    public int compareTo(Post o) {
      return o.getCreationDate().compareTo(this.creationDate);
    }
}
