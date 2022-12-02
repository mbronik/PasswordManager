#include <iostream>
#include "MainMenu.h"
#include "PasswordManager.h"
#include "Category.h"
#include "Logic.h"

void createSamplePassword();

int main() {
    MainMenu::start();

//    createSamplePassword();
    return 0;
}

void creatSamplePassword(){
    int c1 = Category::create("Mail");
    int c2 = Category::create("Game");
    int c3 = Category::create("Shopping");

    PasswordManager::addPassword(Password("To_the_email_from_Google","daSD43(#ds@",c1));
    PasswordManager::addPassword(Password("Steam","password1234",c2));
    PasswordManager::addPassword(Password("Epic_Games","password1234",c2));
    PasswordManager::addPassword(Password("Aliexpress","veryHard",c3));

    PasswordManager::encrypt();
}
