package engine.Comparator;

import common.Post;
import java.util.Comparator;


/**
 * The ComparatorAnswerCount comparator implements an Comparator<Post>
 * that simply Compares Posts according to the number of replies a post had
 *
 * @author  Pedro Gomes
 * @version 1.1
 * @since 2018-06-08
 */

public class ComparatorAnswerCount implements Comparator<Post> {
    public int compare(Post f1, Post f2){
        if(f1.getReply_number() > f2.getReply_number())
            return -1;
        else if(f1.getReply_number() < f2.getReply_number())
            return 1;
        else
            return 0;
    }
}
