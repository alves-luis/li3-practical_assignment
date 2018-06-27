package controller;

import common.MyLog;
import common.Pair;
import li3.TADCommunity;
import view.ShowView;

import java.time.LocalDate;
import java.util.List;
import java.util.Scanner;

/**
 * Controller of the whole program
 *
 * @author  Pedro Gomes , Pedro Lima, Diogo Gonçalves
 * @version 1.4
 * @since 2018-06-08
 */

public class Controller {

    private final ShowView view;
    private TADCommunity qe;
    private MyLog log;
    private MyLog logtime;

    /**
     * This is the constructor for the Controller
     */
    public Controller(ShowView view, TADCommunity qe, MyLog log, MyLog logtime) {
        this.qe = qe;
        this.view = view;
        this.log = log;
        this.logtime = logtime;

    }
    /**
     * This method is used run the Controller and run the program.
     */
    public void startController() {

        int option = -1;
        Scanner input = new Scanner(System.in);

        do {
            view.mainMenu();
            try {
                option = input.nextInt();
            } catch (Exception e) {
                System.out.println("Error!:" + e);
            }
            switch (option) {
                case 1:
                    query1();
                    break;
                case 2:
                    query2();
                    break;
                case 3:
                    query3();
                    break;
                case 4:
                    query4();
                    break;
                case 5:
                    query5();
                    break;
                case 6:
                    query6();
                    break;
                case 7:
                    query7();
                    break;
                case 8:
                    query8();
                    break;
                case 9:
                    query9();
                    break;
                case 10:
                    query10();
                    break;
                case 11:
                    query11();
                    break;
                case 0:
                    view.showExit();
                    break;
                default:
                    System.out.println("Invalid option");
                    break;
            }
        } while (option != 0);
    }

    /**
     * This method is used run the Query1.
     */
    private void query1() {
        view.infoFromPostMenu();
        long before, after;
        long id = 0;

        view.showScanLong("Id");
        Scanner input = new Scanner(System.in);
        try {
            id = input.nextLong();
        } catch (Exception e) {
            System.out.println("Error!:" + e);
        }

        before = System.currentTimeMillis();
        Pair<String, String> q1 = this.qe.infoFromPost(id);
        after = System.currentTimeMillis();
        this.logtime.writeLog("Query 1: -> " + (after - before) + " ms");
        this.log.writeLog("Query1 -> " + q1);
    }

    /**
     * This method is used run the Query2.
     */
    private void query2() {
        view.topMostActiveMenu();
        long before, after;
        int n = 0;

        view.showScanInt();
        Scanner input = new Scanner(System.in);
        try {
            n = input.nextInt();
        } catch (Exception e) {
            System.out.println("Error!:" + e);
        }

        before = System.currentTimeMillis();
        List<Long> q2 = this.qe.topMostActive(n);
        after = System.currentTimeMillis();
        logtime.writeLog("Query 2 -> " + (after - before) + " ms");
        log.writeLog("Query 2 -> " + q2);
    }

    /**
     * This method is used run the Query3.
     */
    private void query3() {
        view.totalPostsMenu();
        long before, after;

        LocalDate begin;
        LocalDate end;

        view.showScanDate();
        begin = scanDate();

        view.showScanDate();
        end = scanDate();

        before = System.currentTimeMillis();
        Pair<Long, Long> q3 = this.qe.totalPosts(begin, end);
        after = System.currentTimeMillis();
        logtime.writeLog("Query 3 -> " + (after - before) + " ms");
        log.writeLog("Query 3 -> " + q3);
    }

    /**
     * This method is used run the Query4.
     */
    private void query4() {
        view.questionsWithTagMenu();
        long before, after;

        LocalDate begin;
        LocalDate end;

        view.showScanDate();
        begin = scanDate();

        view.showScanDate();
        end = scanDate();

        String tag;

        view.showScanString("Tag");
        Scanner input = new Scanner(System.in);
        tag = input.nextLine();
        String toUse = String.format("<%s>" , tag);
        before = System.currentTimeMillis();
        List<Long> query4 = this.qe.questionsWithTag(toUse, begin, end);
        after = System.currentTimeMillis();
        logtime.writeLog("Query 4 -> " + (after - before) + " ms");
        log.writeLog("Query 4 -> " + query4);
    }

    /**
     * This method is used run the Query5.
     */
    private void query5() {
        view.getUserInfoMenu();
        long before, after;
        long id = 0;

        view.showScanLong("Id");
        Scanner input = new Scanner(System.in);
        try {
            id = input.nextLong();
        } catch (Exception e) {
            System.out.println("Error!:" + e);
        }

        before = System.currentTimeMillis();
        Pair<String, List<Long>> q5 = this.qe.getUserInfo(id);
        after = System.currentTimeMillis();
        logtime.writeLog("Query 5 -> " + (after - before) + " ms");
        log.writeLog("Query 5 -> " + q5);
    }

    /**
     * This method is used run the Query6.
     */
    private void query6() {
        view.mostVotedAnswersMenu();
        long before, after;
        int n = 0;

        view.showScanInt();
        Scanner input = new Scanner(System.in);
        try {
            n = input.nextInt();
        } catch (Exception e) {
            System.out.println("Error!:" + e);
        }

        LocalDate begin;
        LocalDate end;

        view.showScanDate();
        begin = scanDate();

        view.showScanDate();
        end = scanDate();

        before = System.currentTimeMillis();
        List<Long> q6 = this.qe.mostVotedAnswers(n, begin, end);
        after = System.currentTimeMillis();
        logtime.writeLog("Query6 -> " + (after - before) + " ms");
        log.writeLog("Query6 -> " + q6);
    }

    /**
     * This method is used run the Query7.
     */
    private void query7() {
        view.mostAnsweredQuestionsMenu();
        long before, after;
        int n = 0;

        view.showScanInt();
        Scanner input = new Scanner(System.in);
        try {
            n = input.nextInt();
        } catch (Exception e) {
            System.out.println("Error!:" + e);
        }

        LocalDate begin;
        LocalDate end;

        view.showScanDate();
        begin = scanDate();

        view.showScanDate();
        end = scanDate();

        before = System.currentTimeMillis();
        List<Long> q7 = this.qe.mostAnsweredQuestions(n, begin, end);
        after = System.currentTimeMillis();
        logtime.writeLog("Query 7 -> " + (after - before) + " ms");
        log.writeLog("Query 7 -> " + q7);
    }


    /**
     * This method is used run the Query8.
     */
    private void query8() {
        view.containsWordMenu();
        long before, after;
        int N = 0;
        String tag;

        view.showScanString("Word");
        Scanner input = new Scanner(System.in);
        tag = input.nextLine();


        view.showScanInt();
        try {
            N = input.nextInt();
        } catch (Exception e) {
            System.out.println("Error!:" + e);
        }

        before = System.currentTimeMillis();
        List<Long> q8 = this.qe.containsWord(N, tag);
        after = System.currentTimeMillis();
        logtime.writeLog("Query 8 -> " + (after - before) + " ms");
        log.writeLog("Query 8 -> " + q8);
    }

    /**
     * This method is used run the Query9.
     */
    private void query9() {
        view.bothParticipatedMenu();
        long before, after;
        long id1 = 0, id2 = 0;
        int N = 0;

        view.showScanInt();
        Scanner input = new Scanner(System.in);
        try {
            N = input.nextInt();
        } catch (Exception e) {
            System.out.println("Error!:" + e);
        }
        view.showScanLong("Id 1");
        try {
            id1 = input.nextLong();
        } catch (Exception e) {
            System.out.println("Error!:" + e);
        }
        view.showScanLong("Id 2");
        try {
            id2 = input.nextLong();
        } catch (Exception e) {
            System.out.println("Error!:" + e);
        }


        before = System.currentTimeMillis();
        List<Long> q9 = this.qe.bothParticipated(N, id1, id2);
        after = System.currentTimeMillis();
        logtime.writeLog("Query9 -> " + (after - before) + " ms");
        log.writeLog("Query 9 -> " + q9);
    }

    /**
     * This method is used run the Query10.
     */
    private void query10() {
        view.betterAnswerMenu();
        long before, after;
        long id = 0;

        view.showScanLong("Id");
        Scanner input = new Scanner(System.in);
        try {
            id = input.nextLong();
        } catch (Exception e) {
            System.out.println("Error!:" + e);
        }

        before = System.currentTimeMillis();
        long q10 = this.qe.betterAnswer(id);
        after = System.currentTimeMillis();
        logtime.writeLog("Query 10 -> " + (after - before) + " ms");
        log.writeLog("Query 10 -> " + q10);
    }

    /**
     * This method is used run the Query11.
     */
    private void query11() {
        view.mostUsedBestRepMenu();
        long before, after;
        int n = 0;

        view.showScanInt();
        Scanner input = new Scanner(System.in);
        try {
            n = input.nextInt();
        } catch (Exception e) {
            System.out.println("Error!:" + e);
        }

        LocalDate begin;
        LocalDate end;

        view.showScanDate();
        begin = scanDate();

        view.showScanDate();
        end = scanDate();

        before = System.currentTimeMillis();
        List<Long> q11 = this.qe.mostUsedBestRep(n, begin, end);
        after = System.currentTimeMillis();
        logtime.writeLog("Query 11 -> " + (after - before) + " ms");
        log.writeLog("Query 11 -> " + q11);
    }
    /**
     * This method is used to scan LocalDate.
     * @return LocalDate Scanned.
     */
    private static LocalDate scanDate() {
        LocalDate data = LocalDate.of(1, 1, 1);
        Scanner sc = new Scanner(System.in);
        try {
            String data_string = sc.nextLine();
            data = LocalDate.parse(data_string);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
        return data;
    }
}