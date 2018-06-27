package engine.Comparator;

import common.*;
import java.util.Comparator;

/**
 * The ComparatorUserCount comparator implements an Comparator<User>
 * that simply Compares Users according to their number of Posts
 * in case they have the same amount of Posts the second Comparator
 * is the ID of the Users.
 *
 * @authors Diogo Gonçalves
 * @version 1.2
 * @since 2018-06-09
 */

public class ComparatorUserCount implements Comparator<User> {

    public int compare(User f1, User f2){
        if(f1.getPostC() > f2.getPostC())
            return -1;
        else if(f1.getPostC() < f2.getPostC())
            return 1;
        else {
            if (f1.getId() > f2.getId())
                return -1;
            else if(f1.getId() < f2.getId())
                return 1;
            return 0;
        }

    }

}