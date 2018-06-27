package li3;

import java.time.LocalDateTime;
import java.time.LocalDate;
import li3.Identifiable;

/**
 * Post class
 *
 * @author Grupo 42
 * @version 2018-05-23
 */
public class Post implements Comparable<Post>, Identifiable {
    /** Title of the Post */
    String title;
    /** ID of the Post */
    long id;
    /** DateTime of the creation date */
    LocalDateTime creationDate;
    /** Id of the Creator */
    long creatorId;

    /**
      * Default constructor
    */
    public Post() {
      this.title = null;
      this.id = -99;
      this.creationDate = LocalDateTime.now();
      this.creatorId = -1;
    }

    /**
      * Parametrized constructor
      * @param title Title
      * @param postId Post ID
      * @param date Date
      * @param creator Creator ID
    */
    public Post(String title, long postId, LocalDateTime date, long creator) {
      this.title = title;
      this.id = postId;
      this.creationDate = date;
      this.creatorId = creator;
    }

    /**
      * Copy constructor
      * @param p Post
    */
    public Post(Post p) {
      title = p.getTitle();
      id = p.getId();
      creationDate = p.getCreationDate();
      creatorId = p.getCreatorId();
    }

    /**
      * Title getter
      * @return Title (can be null)
    */
    public String getTitle() {
      return title;
    }

    /**
      * Post ID getter
      * @return ID
    */
    public long getId() {
      return this.id;
    }

    /**
      * Creator ID getter
      * @return Creator ID
    */
    public long getCreatorId() {
      return this.creatorId;
    }

    /**
      * Creation date getter
      * @return Date
    */
    public LocalDateTime getCreationDate() {
      return this.creationDate;
    }

    /**
      * Local date getter
      * @return Local Date
    */
    public LocalDate getLocalDate() {
      return this.creationDate.toLocalDate();
    }

    /**
      * Title setter
      * @param tit Title
    */
    public void setTitle(String tit) {
      title = tit;
    }

    /**
      * Post ID setter
      * @param newID Post ID
    */
    public void setId(long newId) {
      id = newId;
    }

    /**
      * Creation date setter
      * @param year Year
      * @param month Month
      * @param day Day
      * @param hour Hour
      * @param minute Minute
      * @param second Second
      * @param nano Nano Second
    */
    public void setCreationDate(Integer year, Integer month, Integer day, Integer hour, Integer minute, Integer second, Integer nano) {
      creationDate = LocalDateTime.of(year,month,day,hour,minute,second,nano);
    }

    /**
      * Creator ID setter
      * @param cID Creator ID
    */
    public void setCreatorId(long cId) {
      creatorId = cId;
    }

    /**
      * ToString method
      * @return String containing all the info of the post
    */
    public String toString() {
      StringBuilder sb = new StringBuilder();
      sb.append("\nId: ").append(id);
      sb.append("\nTitle: ").append(title);
      sb.append("\nCreatorId: ").append(creatorId);
      sb.append("\nCreationDate: ").append(creationDate);

      return sb.toString();
    }

    /**
      * Equals method
      * @param o Object compared to post
      * @return True or false boolean
    */
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

    /**
      * Clone method
      * @return Object with type Post
    */
    public Post clone() {
      return new Post(this);
    }

    /**
      * Compare creation dates
      * @param o Post
      * @return 1 if True, 0 if False
    */
    public int compareTo(Post o) {
      return o.getCreationDate().compareTo(this.creationDate);
    }
}
