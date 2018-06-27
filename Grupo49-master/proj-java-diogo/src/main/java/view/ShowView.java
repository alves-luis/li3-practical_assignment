package view;

import li3.TADView;

/**
 * The ShowView class implements an Comparator<User>
 *
 * @authors Diogo Gonçalves
 * @version 1.2
 * @since 2018-06-08
 */

public class ShowView implements TADView {

    /**
     * Display Main Menu
     */
    public void mainMenu(){
        System.out.println("----------------");
        System.out.println("----- Menu -----");
        System.out.println("----------------");
        System.out.println("1 -> Query 1");
        System.out.println("2 -> Query 2");
        System.out.println("3 -> Query 3");
        System.out.println("4 -> Query 4");
        System.out.println("5 -> Query 5");
        System.out.println("6 -> Query 6");
        System.out.println("7 -> Query 7");
        System.out.println("8 -> Query 8");
        System.out.println("9 -> Query 9");
        System.out.println("10 -> Query 10");
        System.out.println("11 -> Query 11");
        System.out.println("0 -> Leave");
    }

    /**
     * Display QUERY 1
     */
    public void infoFromPostMenu(){
        System.out.println("---------------");
        System.out.println("--- QUERY 1 ---");
        System.out.println("---------------");
    }

    /**
     * Display QUERY 2
     */
    public void topMostActiveMenu(){
        System.out.println("---------------");
        System.out.println("--- QUERY 2 ---");
        System.out.println("---------------");
    }

    /**
     * Display QUERY 3
     */
    public void totalPostsMenu(){
        System.out.println("---------------");
        System.out.println("--- QUERY 3 ---");
        System.out.println("---------------");
    }

    /**
     * Display QUERY 4
     */
    public void questionsWithTagMenu(){
        System.out.println("---------------");
        System.out.println("--- QUERY 4 ---");
        System.out.println("---------------");
    }

    /**
     * Display QUERY 5
     */
    public void getUserInfoMenu(){
        System.out.println("---------------");
        System.out.println("--- QUERY 5 ---");
        System.out.println("---------------");
    }

    /**
     * Display QUERY 6
     */
    public void mostVotedAnswersMenu(){
        System.out.println("---------------");
        System.out.println("--- QUERY 6 ---");
        System.out.println("---------------");
    }

    /**
     * Display QUERY 7
     */
    public void mostAnsweredQuestionsMenu(){
        System.out.println("---------------");
        System.out.println("--- QUERY 7 ---");
        System.out.println("---------------");
    }

    /**
     * Display QUERY 8
     */
    public void containsWordMenu(){
        System.out.println("---------------");
        System.out.println("--- QUERY 8 ---");
        System.out.println("---------------");
    }

    /**
     * Display QUERY 9
     */
    public void bothParticipatedMenu(){
        System.out.println("---------------");
        System.out.println("--- QUERY 9 ---");
        System.out.println("---------------");
    }

    /**
     * Display QUERY 10
     */
    public void betterAnswerMenu(){
        System.out.println("----------------");
        System.out.println("--- QUERY 10 ---");
        System.out.println("----------------");
    }

    /**
     * Display QUERY 11
     */
    public void mostUsedBestRepMenu(){
        System.out.println("----------------");
        System.out.println("--- QUERY 11 ---");
        System.out.println("----------------");
    }
    /**
     * Display Scanner of a Date
     */
    public void showScanDate(){
        System.out.print("Insert date:");
    }
    /**
     * Display Scanner of an Integer
     */
    public void showScanInt(){
        System.out.print("Insert an Integer:");
    }
    /**
     * Display Scanner of a Long
     */
    public void showScanLong(String what){
        System.out.print("Insert a Long" + what + ":");
    }
    /**
     * Display Scanner of a String
     */
    public void showScanString(String what){
        System.out.print("Insert a String" + what + ":");
    }
    /**
     * Display Exit Menu
     */
    public void showExit(){
        System.out.println("Leaving");
    }
}



