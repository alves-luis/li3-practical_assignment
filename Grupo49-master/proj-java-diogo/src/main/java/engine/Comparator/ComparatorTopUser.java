package engine.Comparator;

import common.*;
import java.util.Comparator;

/**
 * The ComparatorTopUser comparator implements an Comparator<User>
 * that simply Compares Users according to their Reputation.
 *
 * @author Pedro Lima
 * @version 1.1
 * @since 2018-06-08
 */

public class ComparatorTopUser implements Comparator<User> {
    public int compare(User f1, User f2){
        if(f1.getRep() > f2.getRep())
            return -1;
        else if(f1.getRep() < f2.getRep())
            return 1;
        else
            return 0;
    }
}
