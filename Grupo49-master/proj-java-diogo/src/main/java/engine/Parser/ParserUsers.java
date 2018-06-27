package engine.Parser;

import common.User;

import java.util.Map;
import java.util.HashMap;
import java.io.IOException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import org.xml.sax.SAXException;
import org.xml.sax.Attributes;
import org.xml.sax.helpers.DefaultHandler;

/**
 * The ParserUsers class extends DefaultHandler
 * this class get creates a Map from a Users.xml file
 * where the key is the id of the Users
 * and the value is all the information regarding the User
 *
 * @author  Pedro Gomes
 * @version 1.2
 * @since 2018-06-09
 */

public class ParserUsers extends DefaultHandler {
    private final Map<Long,User> bookL;
    private String bookXmlFileName;
    private User bookTmp;


    /**
     * This method is the constructor to start the parser
     * @param bookXmlFileName this param is the path to the file to be parsed
     */
    public ParserUsers(String bookXmlFileName) {
        this.bookXmlFileName = bookXmlFileName;
        bookL = new HashMap<>();
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

    @Override
    public void startElement(String s, String s1, String elementName, Attributes attributes) {
        if (elementName.equalsIgnoreCase("row")) {
            bookTmp = new User();
            bookTmp.setId(Long.parseLong(attributes.getValue("Id")));
            bookTmp.setRep(Integer.parseInt(attributes.getValue("Reputation")));
            bookTmp.setNickname(attributes.getValue("DisplayName"));
            bookTmp.setShortBio(attributes.getValue("AboutMe"));
        }
    }
    public void endElement(String s, String s1, String element) {
        bookL.put(bookTmp.getId(),bookTmp);
    }
    /**
     * This method is used to add get the Map with all the users after the parse.
     * @return Map<Long,User> All the Users from the file.
     */
    public Map<Long,User> getUsers(){
        return this.bookL;
    }
}