package engine.Comparator;

import common.Tag;
import java.util.Comparator;

/**
 * The ComparatorCount comparator implements an Comparator<Tag>
 * that simply Compares Tags according to number of times their appear.
 *
 * @author  Diogo Gonçalves
 * @version 1.2
 * @since 2018-06-09
 */

public class ComparatorCount implements Comparator<Tag> {
    public int compare(Tag f1, Tag f2){
        if(f1.getTagCount() > f2.getTagCount())
            return -1;
        else if(f1.getTagCount() < f2.getTagCount())
            return 1;
        else {
            if (f1.getId() > f2.getId())
                return 1;
            if (f1.getId() < f2.getId())
                return -1;
            return 0;
        }
    }
}
