package common;


/**
 * Class that contains all the information about a User
 *
 * @author  Pedro Gomes , Pedro Lima, Diogo Gonçalves
 * @version 1.4
 * @since 2018-06-08
 */

public class User {

    private String biography;
    private String nickname;
    private long id;
    private int rep;
    private int post_number;

    /**
     * Constructor for objects of class User
     */
    public User(){
        this.biography = "n/a";
        this.nickname = "n/a";
        this.id = -2;
        this.rep = -2;
        this.post_number = 0;

    }

    /**
     * Constructor for objects of class User with specified parameters.
     */
    public User(String bio,String nick, int id, int rep) {
        this.biography = bio;
        this.nickname = nick;
        this.id = id;
        this.rep = rep;
        this.post_number = 0;
    }

    /**
     * Constructor for objects of class User receiving another User as parameter.
     */
    public User(User u) {
        this.biography = u.getShortBio();
        this.nickname = u.getNickname();
        this.id = u.getId();
        this.rep = u.getRep();
        this.post_number = u.getPostC();
    }

    /**
     * Set the User biography to a given param.
     * @param biography data to be replaced by.
     */
    public void setShortBio(String biography){
        this.biography = biography;
    }

    /**
     * Set the User nickname to a given param.
     * @param nick data to be replaced by.
     */
    public void setNickname(String nick){
        this.nickname = nick;
    }

    /**
     * Set the User id to a given param.
     * @param id data to be replaced by.
     */
    public void setId(long id){
        this.id = id;
    }

    /**
     * Set the User reputation to a given param.
     * @param rep data to be replaced by.
     */
    public void setRep(int rep){
        this.rep = rep;
    }

    /**
     * Get the User shortbio.
     * @return String return the shortbio of the User.
     */
    public String getShortBio(){
        return this.biography;
    }

    /**
     * Get the User nickname.
     * @return String return the nickname of the User.
     */
    public String getNickname(){
        return this.nickname;
    }

    /**
     * Get the User id.
     * @return long return the id of the User.
     */
    public long getId(){
        return this.id;
    }

    /**
     * Get the User reputation.
     * @return int return the rep of the User.
     */
    public int getRep(){
        return this.rep;
    }

    /**
     * Get the User post_number.
     * @return int return the post_number of the User.
     */
    public int getPostC(){
        return this.post_number;
    }

    /**
     * Increment the User post_number.
     */
    public void incPostC(){
        this.post_number += 1;
    }

    /**
     * Clone the User.
     * @return User return the clone of the User.
     */
    public User clone() {
        return new User(this);
    }

}
