package common;

/**
 * Class that contains all the information about a Tag
 *
 * @author  Pedro Gomes , Pedro Lima, Diogo Gonçalves
 * @version 1.4
 * @since 2018-06-08
 */

public class Tag{


    private String name;
    private long  id;
    private int  count;

    /**
     * Constructor for objects of class Tag with Empty param
     */
    public Tag(){
        this.name = "n/a";
        this.count = 0;
        this.id = 0;
    }

    /**
     * Constructor for objects of class Tag with the param specified
     */
    public Tag(String title, int id, int score) {
        this.name = title;
        this.id = id;
        this.count = score;
    }

    /**
     * Constructor for objects of class Tag receiving a Tag
     */
    public Tag(Tag t) {
        this.name = t.getTagName();
        this.id = t.getId();
        this.count = t.getTagCount();
    }
    /**
     * Set the Tag name to a given param
     * @param title data to be replaced by
     */
    public void setTagName(String title){
        this.name = title;
    }
    /**
     * Set the Tag id to a given param
     * @param id data to be replaced by
     */
    public void setId(long id){
        this.id = id;
    }
    /**
     * Set the Tag count to a given param
     * @param id data to be replaced by
     */
    public void setCount(int id){
        this.count = id;
    }
    /**
     * Get the Tag name.
     * @return String return the name of the Tag.
     */
    public String getTagName(){
        return this.name;
    }
    /**
     * Get the id of a tag.
     * @return String return the Id of the Tag.
     */
    public long getId(){
        return this.id;
    }
    /**
     * Get the Tag count.
     * @return String return the count of the Tag.
     */
    public int getTagCount(){
        return this.count;
    }
    /**
     * Clone a certain Tag
     */
    public Tag clone() {
        return new Tag(this);
    }
    /**
     * Increment the count of the Tag
     */
    public void incCount(){
        this.count += 1;
    }
}