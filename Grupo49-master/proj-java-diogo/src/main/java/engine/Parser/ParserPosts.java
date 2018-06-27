package engine.Parser;

import engine.Comparator.*;
import common.Post;

import java.io.IOException;
import java.util.*;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import org.xml.sax.SAXException;
import org.xml.sax.Attributes;
import org.xml.sax.helpers.DefaultHandler;


/**
 * The ComparatorCount comparator implements an Comparator<Tag>
 * that simply Compares Tags according to number of times their appear.
 *
 * @author  Pedro Gomes
 * @version 1.2
 * @since 2018-06-09
 */


public class ParserPosts extends DefaultHandler {

    private final Map<Long,Post> bookL;
    private Set<Post> setL;
    private String bookXmlFileName;
    private Post bookTmp;

    /**
     * This method is the constructor to start the parser
     * @param bookXmlFileName this param is the path to the file to be parsed
     */
    public ParserPosts(String bookXmlFileName) {
        this.bookXmlFileName = bookXmlFileName;
        bookL = new HashMap<>();
        this.setL = new TreeSet<>(new ComparatorData());
        parseDocument();
    }

    /**
     * This method is used to start the parsing
     */
    private void parseDocument() {
        SAXParserFactory factory = SAXParserFactory.newInstance();
        try {
            SAXParser parser = factory.newSAXParser();
            parser.parse(bookXmlFileName, this);
        } catch (ParserConfigurationException e) {
            System.out.println("ParserConfig error");
        } catch (SAXException e) {
            System.out.println("SAXException : xml not well formed");
        } catch (IOException e) {
            System.out.println("IO error");
        }
    }

    public void startElement(String s, String s1, String elementName, Attributes attributes) {
        if (elementName.equalsIgnoreCase("row")) {
            bookTmp = new Post();
            bookTmp.setId(Long.parseLong(attributes.getValue("Id")));
            bookTmp.setPostType(Integer.parseInt(attributes.getValue("PostTypeId")));
            bookTmp.setTitle(attributes.getValue("Title"));
            bookTmp.setScore(Integer.parseInt(attributes.getValue("Score")));
            bookTmp.setDate(attributes.getValue("CreationDate"));
            bookTmp.setTags(attributes.getValue("Tags"));

            if(bookTmp.getPostType() == 2) {
                bookTmp.setParentId(Long.parseLong(attributes.getValue("ParentId")));
                bookTmp.setReply_number(Integer.parseInt(attributes.getValue("CommentCount")));
            }

            if (attributes.getValue("OwnerUserId") != null)
                bookTmp.setUserId(Long.parseLong(attributes.getValue("OwnerUserId")));

            if (attributes.getValue("AnswerCount") != null)
                bookTmp.setReply_number(Integer.parseInt(attributes.getValue("AnswerCount")));
        }
    }
    public void endElement(String s, String s1, String element) {
        if (bookTmp.getPostType() == 1 || bookTmp.getPostType() == 2) {
            bookL.put(bookTmp.getId(), bookTmp);
            this.setL.add(bookTmp);
        }
    }
    /**
     * This method is used to get the Set with all the Posts after the parse.
     * @return Set<Post> All the Posts from the file.
     */
    public Set<Post> getSetPosts(){
        return this.setL;
    }

    /**
     * This method is used to get the Map with all the Posts after the parse.
     * @return Map<Long,User> All the Posts from the file.
     */
    public Map<Long,Post> getPosts(){
        return this.bookL;
    }
}
