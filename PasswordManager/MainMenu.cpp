//
// Created by RanVolt on 13.06.2022.
//

#include "MainMenu.h"
#include "Logic.h"

#include <iostream>

#define TesterMode false         //Automatic opening of the default file with the default password

void printMenuPos(const std::string positions[], size_t size) {
    for(int i=0; i<size; i++){
        std::cout << i+1 << ". " << positions[i] << std::endl;
    }
}

bool MainMenu::workingStatus;
int MainMenu::chosenPos;

void MainMenu::init() {
    workingStatus = true;
    chosenPos = 0;
    if(TesterMode){
        PasswordManager::init("data.txt", "admin");
    }else {
        std::cout << "Enter the path to the password file" << std::endl;
        std::string path;
        std::cin >> path;
        std::cout << "Enter the master password" << std::endl;
        std::string masterPassword;
        std::cin >> masterPassword;
        PasswordManager::init(path, masterPassword);
    }
}

void MainMenu::onExit(){
    PasswordManager::encrypt();
}

void MainMenu::run() {
    while(workingStatus){
        switch (chosenPos) {

            case 0:
                std::cout << std::endl;
                printMenuPos(menuPositions, std::size(menuPositions));
                std::cin >> chosenPos;
                break;

            case 1:
                MainMenu::search();
                break;

            case 2:
                MainMenu::sort();
                break;

            case 3:
                MainMenu::addPassword();
                break;

            case 4:
                MainMenu::editPassword();
                break;

            case 5:
                MainMenu::deletePassword();
                break;

            case 6:
                MainMenu::addCategory();
                break;

            case 7:
                MainMenu::deleteCategory();
                break;

            case 8:
                PasswordManager::printAllPassword(false);
                chosenPos = 0;
                break;

            case 9:
                workingStatus = false;
                break;

            default:
                throw "Out of bounds";
        }
    }
    MainMenu::onExit();
}

void MainMenu::sort(){
    printMenuPos(sortPasswordPositions, std::size(sortPasswordPositions));
    int firstSortType;
    int secondSortType;
    std::cout << "Choose main sort type" << std::endl;
    std::cin >> firstSortType;
    std::cout << "Choose second sort type" << std::endl;
    std::cin >> secondSortType;
    PasswordManager::sort( sortType(firstSortType-1), sortType(secondSortType-1) );
    chosenPos = 0;
}

void MainMenu::search(){
    std::string key;
    std::cout << "Enter search key" << std::endl;
    std::cin >> key;

    PasswordManager::searchAndPrint(key);

    chosenPos = 0;
}

void MainMenu::addPassword() {
    int category;
    std::string tag, password, domain, login;
    Category::printList();
    std::cout << "Choose category from list" << std::endl;
    std::cin >> category;
    std::cout << "Enter a password name" << std::endl;
    std::cin >> tag;

    password = choosePassword();
    Password pas = Password(tag, password, category);

    std::cout << std::endl << "Do you want to add optional parts?" << std::endl
    << "1. Domain" << std::endl
    << "2. Login" << std::endl
    << "3. Domain and login" << std::endl
    << "Another. No" << std::endl;
    int pos;
    std::cin >> pos;
    switch (pos) {
        case 3:
        case 1:
            std::cout << std::endl << "Enter the domain" << std::endl;
            std::cin >> domain;
            pas.setPage(domain);
            if(pos == 1)break;
        case 2:
            std::cout << std::endl << "Enter the login" << std::endl;
            std::cin >> login;
            pas.setLogin(login);
            break;
    }
    PasswordManager::addPassword(pas);
    PasswordManager::encrypt();
    chosenPos = 0;
}

std::string MainMenu::choosePassword() {
    _Again:
    std::string password;
    std::cout << "1. Own password\n2. Generate password" << std::endl;
    int com1;
    std::cin >> com1;

    bool choosing = true;
    bool type[4] = {true, true, true, true};
    const std::string typeList[4] = {"Uppercase","Lowercase","Number","Special characters"};
    switch (com1) {
        case 1:
            std::cout << "Enter your password" << std::endl;
            std::cin >> password;
            break;
        case 2:
            std::cout << "What characters do you want to use in the password?" << std::endl;
            while(choosing) {
                for (int i=0; i<4; i++) {
                    std::string status = type[i]?"ON":"OFF";
                    std::cout << i+1 << ". " << typeList[i] << " - " << status << std::endl;
                }
                std::cout << "Another. Go next" << std::endl;
                int com;
                std::cin >> com;
                com--;
                if (com>=0 && com<=3) {
                    type[com]=!type[com];
                }else{
                    if(type[0] || type[1] || type[2] || type[3]) {
                        choosing = false;
                    }else{
                        std::cout << "No type was selected" << std::endl;
                    }
                }
            }
            std::cout << "Enter the length of the password to generate (minimum 4)" << std::endl;
            int length;
            std::cin >> length;
            if(length<4) {
                std::cout << "Password too short, automatic change to minimum length" << std::endl;
                length = 4;
            }

            _PasswordGenerate:
            password = Logic::generatePassword(length, type);
            std::cout << "Your password is " << password << std::endl
            << "1.Generate a different password\nAnother. The password is okay" << std::endl;
            int com2;
            std::cin >> com2;
            if(com2 == 1) goto _PasswordGenerate;
            break;
        default:
            std::cout << "Out of bound" << std::endl;
            goto _Again;
    }

    std::string difficulty[6] = {"No password", "Very simple", "Simple", "Average difficulty", "Strong", "Very String"};
    int passwordDifficulty = (int)( Logic::checkPasswordDifficulty(password)*5/7 );
    std::cout << "Your password is " << difficulty[passwordDifficulty] << std::endl;

    Password same;
    if( PasswordManager::searchSamePassword(password, same) ){
        std::cout << "Same password found:\n" << same.toString() << std::endl;
    }

    std::cout << "Do you want to edit it?\n"
                 "1. Yes\n"
                 "Another. No" << std::endl;
    int com;
    std::cin >> com;
    if(com == 1) goto _Again;

    return password;
}

void MainMenu::editPassword() {
    PasswordManager::printAllPassword(true);
    std::cout << "Choose password to edit" << std::endl;
    int passwordId;
    std::cin >> passwordId;

    _Editor:
    std::cout << "What do you want to edit?\n"
                 "1. Name\n"
                 "2. Password\n"
                 "3. Category\n"
                 "4. Login\n"
                 "5. Domain" << std::endl;
    int com;
    std::cin >> com;

    std::string tempString;
    switch (com) {
        case 1:
            std::cout << "Enter a new password name" << std::endl;
            std::cin >> tempString;
            PasswordManager::getPassword(passwordId).setTag(tempString);
            break;
        case 2:
            PasswordManager::getPassword(passwordId).setPassword( choosePassword() );
            break;
        case 3:
            Category::printList();
            std::cout << "Choose category" << std::endl;
            int tempInt;
            std::cin >> tempInt;
            PasswordManager::getPassword(passwordId).setCategory(tempInt);
            break;
        case 4:
            std::cout << "Enter a new login" << std::endl;
            std::cin >> tempString;
            PasswordManager::getPassword(passwordId).setLogin(tempString);
            break;
        case 5:
            std::cout << "Enter a new domain" << std::endl;
            std::cin >> tempString;
            PasswordManager::getPassword(passwordId).setPage(tempString);
            break;
    }
    std::cout << "Do you want to change anything else?\n"
                 "1. Yes\n"
                 "Another. No" << std::endl;
    std::cin >> com;
    if(com == 1) goto _Editor;
    chosenPos = 0;
}

void MainMenu::deletePassword() {
    PasswordManager::printAllPassword(true);
    std::cout << "Another. Cancel\nChoose password to delete" << std::endl;
    int id;
    std::cin >> id;
    if(id>=0 && id<PasswordManager::countOfPassword())
        PasswordManager::removePassword(id);
    chosenPos = 0;
}

void MainMenu::addCategory() {
    std::string name;
    std::cout << "Enter a name for the new category" << std::endl;
    std::cin >> name;
    Category::create(name);
    chosenPos = 0;
}

void MainMenu::deleteCategory() {
    Category::printList();
    std::cout << "Another. Cancel\nEnter the number of the category to be deleted" << std::endl;
    int no;
    std::cin >> no;
    if(no>=0 && no<Category::countOfCategory())
        Category::remove(no);
    chosenPos = 0;
}

void MainMenu::start() {
    init();
    run();
}
