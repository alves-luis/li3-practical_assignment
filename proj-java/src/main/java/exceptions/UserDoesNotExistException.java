package exceptions;

/**
 * Exception to an unexisting user
 *
 * @author Grupo 42
 * @version 2018-05-23
 */
 public class UserDoesNotExistException extends Exception {
   /**
     * Default constructor to the exception
   */
   public UserDoesNotExistException() {
     super();
   }

   /**
     * Parametrized constructor to the exception
     * @param msg Message
   */
   public UserDoesNotExistException(String msg) {
     super(msg);
   }
 }
