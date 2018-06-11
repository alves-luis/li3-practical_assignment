package li3;

import li3.Identifiable;

/**
 * Escreva a descrição da classe Tag aqui.
 *
 * @author (seu nome)
 * @version 2018-05-23
 */
public class Tag implements Comparable<Tag>, Identifiable {
  /** Name of Tag */
  private String name;
  /** Id of Tag */
  private long id;
  

  public Tag() {
    this.name = null;
    this.id = -1;
  }

  public Tag(String name, long id) {
    this.name = name;
    this.id = id;
  }

  public Tag(Tag t) {
    this.name = t.getName();
    this.id = t.getId();
  }

  public String getName() {
    return this.name;
  }

  public long getId() {
    return this.id;
  }

  public void setId(long newId) {
    this.id = newId;
  }

  public int compareTo(Tag t) {
    return Long.compare(this.id,t.getId());
  }

  public Tag clone() {
    return new Tag(this);
  }

  public String toString() {
    StringBuilder sb = new StringBuilder();
    sb.append("\nName: ").append(this.name);
    sb.append("\nId: ").append(this.id);
    return sb.toString();
  }
}
