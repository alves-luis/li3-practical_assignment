package engine;

import li3.Answer;
import li3.Post;
import li3.Question;
import li3.Tag;
import li3.User;

/**
 * Class with the methods to parse xml into our TCD
 *
 * @author Grupo 42
 * @version 2018-05-23
 */

import java.io.FileReader;
import java.io.FileInputStream;
import javax.xml.stream.XMLInputFactory;
import javax.xml.stream.XMLStreamException;
import javax.xml.stream.XMLStreamConstants;
import javax.xml.stream.XMLStreamReader;
import java.io.FileNotFoundException;
import java.time.LocalDateTime;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;

public class Parser {

  /**
    * Method that given a file name, parses the file into a List of Posts
    * @param file filename
    * @return list with the posts
    * @see li3.Post
  */
  public static List<Post> parsePost(String file) {
    ArrayList<Post> result = new ArrayList<>();
    try {
      XMLInputFactory factory = XMLInputFactory.newInstance();
      XMLStreamReader reader = factory.createXMLStreamReader(new FileInputStream(file));
      while (reader.hasNext()) {
        int eventType = reader.next();
        if (eventType == XMLStreamConstants.START_ELEMENT) {
          String content = reader.getLocalName();
          if (isRow(content)) {
            String title = reader.getAttributeValue(null,"Title");
            int postType = Integer.parseInt(reader.getAttributeValue(null,"PostTypeId"));
            long id = Long.parseLong(reader.getAttributeValue(null,"Id"));
            LocalDateTime date = LocalDateTime.parse(reader.getAttributeValue(null,"CreationDate"));
            long creatorId = Long.parseLong(reader.getAttributeValue(null,"OwnerUserId"));
            if (postType == 1) {
              Question p = new Question(title,id,date,creatorId);
              String notParsedTags = reader.getAttributeValue(null,"Tags");
              List<String> listOfTags = Parser.trimTags(notParsedTags);
              int answerCount = Integer.parseInt(reader.getAttributeValue(null,"AnswerCount"));
              p.addTags(listOfTags);
              p.setAnswerCount(answerCount);
              result.add(p);
            }
            else if (postType == 2) {
              long parentId = Long.parseLong(reader.getAttributeValue(null,"ParentId"));
              short score = Short.parseShort(reader.getAttributeValue(null,"Score"));
              short comments = Short.parseShort(reader.getAttributeValue(null,"CommentCount"));
              Answer p = new Answer(title,id,date,creatorId,parentId,score,comments);
              result.add(p);
            }
          }
        }
      }
    }
    catch (FileNotFoundException e) {
      System.out.println("File not found!");
    }
    catch (XMLStreamException e) {
      System.out.println("Xml exception " + e.getMessage());
    }
    return result;

  }

  /**
    * Parses the tags with <tag><tag2> format to a List of Tag
    * @param tags with default format
    * @return all trimmed, in a list, pretty nice
  */
  private static List<String> trimTags(String tags) {
    String withoutEnds = tags.substring(1,tags.length()-1);
    String[] tokens = withoutEnds.split("><");
    return Arrays.asList(tokens);
  }

  /**
    * Method that given a filename, returns a list with the tags parsed
    * @param file file to be parsed
    * @return Returns a list with the tags all nice
  */
  public static List<Tag> parseTag(String file) {
    ArrayList<Tag> result = new ArrayList<>();
    try {
      XMLInputFactory factory = XMLInputFactory.newInstance();
      XMLStreamReader reader = factory.createXMLStreamReader(new FileInputStream(file));
      while(reader.hasNext()) {
        int eventType = reader.next();
        if (eventType == XMLStreamConstants.START_ELEMENT) {
          String content = reader.getLocalName();
          if (isRow(content)) {
            long id = Long.parseLong(reader.getAttributeValue(null,"Id"));
            String name = reader.getAttributeValue(null,"TagName");
            Tag tag = new Tag(name,id);
            result.add(tag);
          }
        }
      }
    }
    catch (FileNotFoundException e) {
      System.out.println("File not found!");
    }
    catch (XMLStreamException e) {
      System.out.println("Xml exception " + e.getMessage());
    }
    return result;
  }

  /**
    * Method that given a filename, parses it to a list of users
    * @param file filename
    * @return List with the users all parsed out
  */
  public static List<User> parseUser(String file) {
    ArrayList<User> result = new ArrayList<>();
    try {
      XMLInputFactory factory = XMLInputFactory.newInstance();
      XMLStreamReader reader = factory.createXMLStreamReader(new FileInputStream(file));
      while(reader.hasNext()) {
        int eventType = reader.next();
        if (eventType == XMLStreamConstants.START_ELEMENT) {
          String content = reader.getLocalName();
          if (isRow(content)) {
            long id = Long.parseLong(reader.getAttributeValue(null,"Id"));
            int rep = Integer.parseInt(reader.getAttributeValue(null,"Reputation"));
            String name = reader.getAttributeValue(null,"DisplayName");
            String bio = reader.getAttributeValue(null,"AboutMe");
            User u = new User(id,rep,name,bio);
            result.add(u);
          }
        }
      }
    }
    catch (FileNotFoundException e) {
      System.out.println("File not found!");
    }
    catch (XMLStreamException e) {
      System.out.println("Xml exception " + e.getMessage());
    }
    return result;
  }

  /**
    * verify beggining of each element in xml file
    * @param name content
    * @return if equals "row"
  */
  private static boolean isRow(String name) {
    return name.equals("row");
  }
}
