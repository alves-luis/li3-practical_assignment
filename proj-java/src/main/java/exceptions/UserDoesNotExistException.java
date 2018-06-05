package exceptions;

/**
 * Escreva a descrição da classe UserDoesNotExistException aqui.
 *
 * @author (seu nome)
 * @version 2018-05-23
 */
 public class UserDoesNotExistException extends Exception {

   public UserDoesNotExistException() {
     super();
   }

   public UserDoesNotExistException(String msg) {
     super(msg);
   }
 }
