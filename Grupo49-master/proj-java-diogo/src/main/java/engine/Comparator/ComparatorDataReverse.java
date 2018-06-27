package engine.Comparator;

import common.Post;
import java.util.Comparator;

/**
 * The ComparatorDataReverse comparator implements an Comparator<Post>
 * that simply Compares Posts according to their Date of creation.
 *
 * @author Pedro Lima
 * @version 1.1
 * @since 2018-06-08
 */


public class ComparatorDataReverse implements Comparator<Post> {
    public int compare(Post f1, Post f2){
        if(f1.getDate().isBefore(f2.getDate()))
            return 1;
        else if (f1.getDate().isAfter(f2.getDate()))
            return -1;

        return 0;
    }
}
