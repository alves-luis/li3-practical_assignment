package exceptions;

/**
 * Exception to an user without bio
 *
 * @author Grupo 42
 * @version 2018-05-23
 */
 public class UserDoesNotHaveBioException extends Exception {
   /**
     * Default constructor to the exception
   */
   public UserDoesNotHaveBioException() {
     super();
   }
   
   /**
     * Parametrized constructor to the exception
     * @param msg Message
   */
   public UserDoesNotHaveBioException(String msg) {
     super(msg);
   }
 }
