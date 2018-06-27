package common;

import java.time.LocalDate;

/**
 * Class that contains all the information about a Post
 *
 * @author  Pedro Gomes , Pedro Lima, Diogo Gonçalves
 * @version 1.4
 * @since 2018-06-08
 */

public class Post{

    private String title;
    private String  tags;
    private int postType;
    private long  id;
    private long  parent_id;
    private long  user_id;
    private double best_answer;
    private int   score;
    private int reply_number;
    private LocalDate date;


    /**
     * Constructor for objects of class Post
     */
    public Post(){
        this.title = "n/a";
        this.tags = "n/a";
        this.postType = 0;
        this.id = 0;
        this.parent_id = 0;
        this.user_id = 0;
        this.best_answer = 0;
        this.score = 0;
        this.reply_number = 0;
        this.date = LocalDate.now();

    }

    /**
     * Constructor for objects of class Post with specified parameters.
     */
    public Post(String title,String tags, int postType, int id, int parent_id, int user_id, int score, int reply_number) {
        this.title = title;
        this.tags = tags;
        this.postType = postType;
        this.id = id;
        this.parent_id = parent_id;
        this.user_id = user_id;
        this.best_answer = -2;
        this.score = score;
        this.reply_number = reply_number;
        this.date = LocalDate.now();
    }

    /**
     * Constructor for objects of class Post receiving another Post as parameter.
     */
    public Post(Post p) {
        this.title = p.getTitle();
        this.tags = p.getTags();
        this.postType = p.getPostType();
        this.id = p.getId();
        this.parent_id = p.getParentId();
        this.user_id = p.getUserId();
        this.best_answer = p.getScore();
        this.score = p.getScore();
        this.reply_number = p.getReply_number();
        this.date = p.getDate();
    }

    /**
     * Set the Post title to a given param.
     * @param title data to be replaced by.
     */
    public void setTitle(String title){
        this.title = title;
    }

    /**
     * Set the Post tags to a given param.
     * @param tags data to be replaced by.
     */
    public void setTags(String tags){
        this.tags = tags;
    }

    /**
     * Set the Post id to a given param.
     * @param id data to be replaced by.
     */
    public void setId(long id){
        this.id = id;
    }

    /**
     * Set the Post parent_id to a given param.
     * @param id data to be replaced by.
     */
    public void setParentId(long id){
        this.parent_id = id;
    }

    /**
     * Set the Post userId to a given param.
     * @param id data to be replaced by.
     */
    public void setUserId(long id){
        this.user_id = id;
    }

    /**
     * Set the Post postType to a given param.
     * @param type data to be replaced by.
     */
    public void setPostType(int type){
        this.postType = type;
    }

    /**
     * Set the Post score to a given param.
     * @param score data to be replaced by.
     */
    public void setScore(int score){
        this.score = score;
    }

    /**
     * Set the Post best_answer to a given param.
     * @param x data to be replaced by.
     */
    public void setBestScore(double x){
        this.best_answer = x;
    }

    /**
     * Set the Post reply_number to a given param.
     * @param reply_number data to be replaced by.
     */
    public void setReply_number(int reply_number){
        this.reply_number = reply_number;
    }

    /**
     * Set the Post date to a given param.
     * @param data data to be replaced by.
     */
    public void setDate(String data){
        String result = data.substring(0, 10);
        this.date = LocalDate.parse(result);
    }

    /**
     * Get the Post title.
     * @return String return the title of the Post.
     */
    public String getTitle(){
        return this.title;
    }

    /**
     * Get the Post tags.
     * @return String return the tags of the Post.
     */
    public String getTags(){
        return this.tags;
    }

    /**
     * Get the Post type.
     * @return Int return the type of the Post.
     */
    public int getPostType(){
        return this.postType;
    }

    /**
     * Get the Post id.
     * @return Int return the id of the Post.
     */
    public long getId(){
        return this.id;
    }

    /**
     * Get the Post best_answer.
     * @return double return the best_answer of the Post.
     */
    public double getBestScore(){
        return this.best_answer;
    }

    /**
     * Get the Post parent_id.
     * @return long return the parent_id of the Post.
     */
    public long getParentId(){
        return this.parent_id;
    }

    /**
     * Get the Post user_id.
     * @return long return the user_id of the Post.
     */
    public long getUserId(){
        return this.user_id;
    }

    /**
     * Get the Post reply_number.
     * @return int return the reply_number of the Post.
     */
    public int getReply_number(){
        return this.reply_number;
    }

    /**
     * Get the Post date.
     * @return LocalDate return the date of the Post.
     */
    public LocalDate getDate(){
        return this.date;
    }

    /**
     * Get the Post score.
     * @return int return the score of the Post.
     */
    public int getScore(){
        return this.score;
    }

    /**
     * Clone the Post.
     * @return Post return the clone of the Post.
     */
    public Post clone() {
        return new Post(this);
    }
}
