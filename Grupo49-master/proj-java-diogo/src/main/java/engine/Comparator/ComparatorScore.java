package engine.Comparator;

import common.Post;
import java.util.Comparator;

/**
 * The ComparatorScore comparator implements an Comparator<Post>
 * that simply Compares Posts according to their Score.
 *
 * @author  Diogo Gonçalves
 * @version 1.1
 * @since 2018-06-08
 */

public class ComparatorScore implements Comparator<Post> {
    public int compare(Post f1, Post f2){
        if(f1.getScore() > f2.getScore())
            return -1;
        else if(f1.getScore() < f2.getScore())
            return 1;
        else
            return 0;
    }
}
