package engine.Comparator;

import common.*;
import java.util.Comparator;

/**
 * The ComparatorBestAnswer comparator implements an Comparator<Post>
 * that simply Compares Posts according to their best Score.
 *
 * @author Pedro Lima
 * @version 1.1
 * @since 2018-06-08
 */

public class ComparatorBestAnswer implements Comparator<Post>
{
    // instance variables - replace the example below with your ow
    public int compare(Post f1, Post f2){
            if(f1.getBestScore() > f2.getBestScore())
                return -1;
            else if(f1.getBestScore() < f2.getBestScore())
                return 1;
            else
                return 0;
        }

}