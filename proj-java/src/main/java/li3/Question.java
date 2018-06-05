package li3;

/**
 * Question is a type of Post
 *
 * @author (your name)
 * @version 2015-05-23
 */
import java.util.Set;
import java.util.List;
import java.util.TreeSet;
import java.util.ArrayList;
import java.util.stream.Collectors;
import java.time.LocalDateTime;

public class Question extends Post {

  /** List with Tags */
  private List<String> tags;

  public Question() {
    tags = new ArrayList<String>();
  }

  public Question(String title,long id,LocalDateTime date,long creatorId) {
    super(title,id,date,creatorId);
    tags = new ArrayList<String>();
  }

  public Question(Question q) {
    super(q);
    tags = q.getTags();
  }

  public List<String> getTags() {
    return this.tags.stream()
    .collect(Collectors.toList());
  }

  public void addTag(String t) {
    this.tags.add(t);
  }

  public void addTags(List<String> t) {
    this.tags = t;
  }

  public Question clone() {
    return new Question(this);
  }

  public boolean equals(Object o) {
    if (this == o)
      return true;
    if (o == null || o.getClass() != this.getClass())
      return false;
    Question a = (Question) o;
    return super.equals(a);
  }

}
