//
// Created by RanVolt on 15.06.2022.
//

#include <iostream>
#include "Password.h"
#include "Logic.h"

Password::Password(const std::string &tag, const std::string &password, const int &category)
: tag(tag), password(password), category(category){
    Password::login = "";
    Password::page = "";
}

Password::Password() {

}



void Password::setTag(const std::string &tag) {
    Password::tag = tag;
}

void Password::setPassword(const std::string &password) {
    Password::password = password;
}

void Password::setCategory(const int &id) {
    Password::category = id;
}

void Password::setLogin(const std::string &login) {
    Password::login = login;
}

void Password::setPage(const std::string &page) {
    Password::page = page;
}

const std::string &Password::getTag() const {
    return tag;
}

const std::string &Password::getPassword() const {
    return password;
}

const Category &Password::getCategory() const {
    return Category::getCategory(category);
}

const std::string &Password::getPage() const {
    return page;
}

const std::string &Password::getLogin() const {
    return login;
}

const int Password::getDifficult() {
    return Logic::checkPasswordDifficulty(password);
}

std::string Password::toString() {
    return tag + "|" + password + "|" + getCategory().getName() + "|" + page + "|" + login;
}

Password Password::parse(std::string text) {
    Password tempPassword;

    int j = 0;
    for(int i=0; i<5; i++){
        std::string temp = "";
        char character;
        do{
            character = text[j];
            if(character != '|' && character != 0){
                temp = temp + character;
            }
            j++;
        }while(character != '|' && character != 0);
        switch (i) {
            case 0:
                tempPassword.setTag(temp);
                break;
            case 1:
                tempPassword.setPassword(temp);
                break;
            case 2:
                tempPassword.setCategory(Category::parse(temp));
                break;
            case 3:
                tempPassword.setPage(temp);
                break;
            case 4:
                tempPassword.setLogin(temp);
                break;
        }
    }
    return tempPassword;
}

