package engine.Exception;

/**
 * Exception for Invalid id
 *
 * @author  Pedro Gomes
 * @version 1.4
 * @since 2018-06-08
 */

public class InvalidIdException extends Exception {
    public InvalidIdException(String message){
        super(message);
    }
    public void message(){
        System.out.println(this.getMessage());
    }
}