//
// Created by RanVolt on 13.06.2022.
//

#ifndef PASSWORDMANAGER_MAINMENU_H
#define PASSWORDMANAGER_MAINMENU_H

#include <string>
#include "PasswordManager.h"

const std::string menuPositions[9] = {
        "Search password",
        "Sort password",
        "Add password",
        "Edit password",
        "Delete password",
        "Add category",
        "Delete category",
        "Show all password",
        "Exit"
};
const std::string sortPasswordPositions[6]{
    "By name",
    "By category",
    "By password",
    "By login",
    "By domain",
    "None"
};

class MainMenu {
    static bool workingStatus;
    static int chosenPos;

private:
    static void init();
    static void onExit();
    static void run();

    static void sort();
    static void search();
    static void addPassword();
    static void editPassword();
    static void deletePassword();
    static void addCategory();
    static void deleteCategory();

    /**
     * It calls the private methods init, run, and exit, in order.
     * @return created password according to the user
     */
    static std::string choosePassword();

public:
    /**
     * It calls the private methods init(), run(), and exit(), in order.
     */
    static void start();
};


#endif //PASSWORDMANAGER_MAINMENU_H
