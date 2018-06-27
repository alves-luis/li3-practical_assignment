package li3;

import common.MyLog;
import engine.TCDExample;
import controller.Controller;
import view.ShowView;

/**
 * Main program
 *
 * @author  Pedro Gomes , Pedro Lima, Diogo Gonçalves
 * @version 1.4
 * @since 2018-06-08
 */

class Main {


    public static void main(String[] args){

        /*
            LOG CONFIGURATION
        */
        MyLog log = new MyLog("results");
        MyLog logtime = new MyLog("times");
        /* -------------------------------------------------------------------------------------------*/

        long before, after;
        TADCommunity qe = new TCDExample();
        // Load
        try {
            before = System.currentTimeMillis();
            qe.load(args[0]);
            after = System.currentTimeMillis();
            logtime.writeLog("LOAD -> "+(after-before)+" ms");
        } catch(IndexOutOfBoundsException e){
            System.out.println("Give the Dump Path as an argument");
        }

        // View

        ShowView view = new ShowView();

        // Controller
        Controller control= new Controller(view , qe , log, logtime);

        // Controller Start
        control.startController();

        // Clean
        before = System.currentTimeMillis();
        qe.clear();
        after = System.currentTimeMillis();
        logtime.writeLog("CLEAN -> "+(after-before)+" ms");
    }
}


