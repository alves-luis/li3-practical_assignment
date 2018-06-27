package exceptions;

/**
 * Exception to an unexisting post
 *
 * @author Grupo 42
 * @version 2018-05-23
 */
 public class PostDoesNotExistException extends Exception {
   /**
     * Default constructor to the exception
   */
   public PostDoesNotExistException() {
     super();
   }

   /**
     * Parametrized constructor to the exception
     * @param msg Message
   */
   public PostDoesNotExistException(String msg) {
     super(msg);
   }
}
