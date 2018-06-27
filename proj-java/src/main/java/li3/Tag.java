package li3;

import li3.Identifiable;

/**
 * Tag class
 *
 * @author Grupo 42
 * @version 2018-05-23
 */
public class Tag implements Comparable<Tag>, Identifiable {
  /** Name of Tag */
  private String name;
  /** Id of Tag */
  private long id;

  /**
    * Default constructor
  */
  public Tag() {
    this.name = null;
    this.id = -1;
  }

  /**
    * Parametrized constructor
    * @param name Name
    * @param id ID
  */
  public Tag(String name, long id) {
    this.name = name;
    this.id = id;
  }

  /**
    * Copy constructor
    * @param t Tag
  */
  public Tag(Tag t) {
    this.name = t.getName();
    this.id = t.getId();
  }

  /**
    * Name getter
    * @return Name
  */
  public String getName() {
    return this.name;
  }

  /**
    * ID getter
    * @return ID
  */
  public long getId() {
    return this.id;
  }

  /**
    * ID setter
    * @param newId ID
  */
  public void setId(long newId) {
    this.id = newId;
  }

  /**
    * Compare ID's
    * @param t Tag
    * @return 1 if True, 0 if False
  */
  public int compareTo(Tag t) {
    return Long.compare(this.id,t.getId());
  }

  /**
    * Clone method
    * @return Object with type Tag
  */
  public Tag clone() {
    return new Tag(this);
  }

  /**
    * ToString method
    * @return String containing all the info of the tag
  */
  public String toString() {
    StringBuilder sb = new StringBuilder();
    sb.append("\nName: ").append(this.name);
    sb.append("\nId: ").append(this.id);
    return sb.toString();
  }
}
