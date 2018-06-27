package engine.Parser;

import common.*;

import java.io.IOException;
import java.util.Map;
import java.util.HashMap;

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
 * @author  Diogo Gonçalves
 * @version 1.2
 * @since 2018-06-09
 */


public class ParserTags extends DefaultHandler {
    private final Map<String,Tag> bookL;
    private String bookXmlFileName;
    private Tag bookTmp;

    /**
     * This method is the constructor to start the parser
     * @param bookXmlFileName this param is the path to the file to be parsed
     */
    public ParserTags(String bookXmlFileName) {
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
            bookTmp = new Tag();
            bookTmp.setId(Long.parseLong(attributes.getValue("Id")));
            bookTmp.setTagName(attributes.getValue("TagName"));
            bookTmp.setCount(0);
        }
    }
    @Override
    public void endElement(String s, String s1, String element) {
        bookL.put(bookTmp.getTagName(),bookTmp);
    }

    /**
     * This method is used to get the Map with all the Tags after the parse.
     * @return Map<Long,Tag> All the Tags from the file.
     */
    public Map<String, Tag> getTags(){
        return this.bookL;
    }
}