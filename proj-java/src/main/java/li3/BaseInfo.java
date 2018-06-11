package li3;

import exceptions.PostDoesNotExistException;
import exceptions.UserDoesNotExistException;
import exceptions.UserDoesNotHaveBioException;

/**
  * Interface that TCD must implement for basic info from TCD.
  * @author Grupo 42
  * @version 2018-11-06
*/

public interface BaseInfo {

  public Post getPost(Long id) throws PostDoesNotExistException;
  public Long getTagId(String tag);
  public User getUserById(Long id) throws UserDoesNotExistException;
  public String getBio(Long id) throws UserDoesNotHaveBioException;

}
