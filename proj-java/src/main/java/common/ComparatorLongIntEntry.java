package common;

import java.util.Map;

/**
  * Comparator of Map.Entries of <Long,Integer> (second order is lowest ID first)
  *
  * @author Luís Alves
  * @version 2018-05-23
*/
import java.util.Comparator;

public class ComparatorLongIntEntry implements Comparator<Map.Entry<Long,Integer>> {
  /**
    * Compares two Map.Entries <Long,Integer>
    * @param e1 Entry 1
    * @param e2 Entry 2
    * @return int of comparison (if equal, then compares by Id)
  */
  public int compare(Map.Entry<Long,Integer> e1, Map.Entry<Long,Integer> e2) {
    int comparison = e2.getValue().compareTo(e1.getValue());
    if (comparison == 0) return Long.compare(e1.getKey(),e2.getKey());
    else return comparison;
  }
}
