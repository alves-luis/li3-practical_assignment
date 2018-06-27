package li3;

public interface TADView {

    // Main Menu
    void mainMenu();

    // Menu for Query 1
    void infoFromPostMenu();

    //  Menu for Query 2
    void topMostActiveMenu();

    //  Menu for Query 3
    void totalPostsMenu();

    //  Menu for Query 4
    void questionsWithTagMenu();

    //  Menu for Query 5
    void getUserInfoMenu();

    //  Menu for Query 6
    void mostVotedAnswersMenu();

    //  Menu for Query 7
    void mostAnsweredQuestionsMenu();

    //  Menu for Query 8
    void containsWordMenu();

    //  Menu for Query 9
    void bothParticipatedMenu();

    //  Menu for Query 10
    void betterAnswerMenu();

    //  Menu for Query 11
    void mostUsedBestRepMenu();

    //  Menu to get a Date
    void showScanDate();

    //  Menu to get an Integer
    void showScanInt();

    //  Menu to get a Long
    void showScanLong(String what);

    //  Menu to get a String
    void showScanString(String what);

    //  Menu to show Exit
    void showExit();
}



