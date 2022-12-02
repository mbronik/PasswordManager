//
// Created by RanVolt on 15.06.2022.
//

#include <fstream>
#include <iostream>
#include <ctime>
#include "PasswordManager.h"
#include "Logic.h"


std::vector<Password> PasswordManager::passwords;
std::string PasswordManager::currentMasterPassword;
std::string PasswordManager::pathToFile;

std::string PasswordManager::timestamp;
int mainTimestampKey[12][2] = {{11,1},{50,2},{31,4},{4,5},{97,7},{17,8},{46,10},{84,11},{99,13},{77,14},{28,15},{53,16}};
#define secondTimestampKey 51

void PasswordManager::init(const std::string path, const std::string password) {
    pathToFile = path;
    currentMasterPassword = password;

    std::fstream inFile;
    inFile.open(pathToFile,std::ios::in);
    std::string decryptedTimestamp = "HH:mm DD-MM-RRRR";
    if(inFile.is_open()){
        std::getline(inFile, timestamp);
    } else {
        throw "Problem with open file";
    }
    inFile.close();
    for(int i=0; i<12; i++) decryptedTimestamp[mainTimestampKey[i][1]-1] = timestamp[mainTimestampKey[i][0]]-secondTimestampKey;
    std::cout << "Timestamp : " << decryptedTimestamp << std::endl;

    PasswordManager::decrypt();
    PasswordManager::createTimestamp();
    PasswordManager::encrypt();
}

void PasswordManager::createTimestamp() {
    srand(time(NULL));

    time_t time1;
    time1 = time(0);

    tm *now = localtime(&time1);

    for(int i=0; i<100; i++){
        timestamp = timestamp + (char)( rand()%94 + 33 );
    }

    int shift = +'0' + secondTimestampKey;

    timestamp[11] = (char)(int)(now->tm_hour/10) + shift;
    timestamp[50] = (char)(now->tm_hour%10) + shift;
    timestamp[31] = (char)(int)(now->tm_min/10) + shift;
    timestamp[4] = (char)(now->tm_min%10) + shift;
    timestamp[97] = (char)(int)(now->tm_mday/10) + shift;
    timestamp[17] = (char)(now->tm_mday%10) + shift;
    timestamp[46] = (char)(int)(now->tm_mon/10) + shift;
    timestamp[84] = (char)(now->tm_mon%10) + shift;
    timestamp[99] = (char)(int)((now->tm_year+1900)/1000) + shift;
    timestamp[77] = (char)(int)((now->tm_year+1900)%1000/100) + shift;
    timestamp[28] = (char)(int)((now->tm_year+1900)%100/10) + shift;
    timestamp[53] = (char)((now->tm_year+1900)%10) + shift;
}

void PasswordManager::decrypt() {
    std::fstream inFile;
    inFile.open(pathToFile,std::ios::in);
    if(inFile.is_open()){
        int lastKey = 0;
        int lastCharOfPas = -1;

        std::string line;
        std::getline(inFile, line);

        while (std::getline(inFile,line)){
            std::string decryptedLine;
            for(int i=0; i<line.length(); i++){
                lastCharOfPas++;
                if(lastCharOfPas == currentMasterPassword.length()){
                    lastCharOfPas = 0;
                }
                int temp = ((int)line[i]-33-lastKey-currentMasterPassword[lastCharOfPas]);
                while (temp<33){
                    temp+=93;
                }
                lastKey = temp;
                decryptedLine = decryptedLine + (char)temp;
            }
            Password temp = Password::parse(decryptedLine);
            addPassword(temp);
        }
        inFile.close();
    }else{
        throw std::logic_error("Problem with open data file");
    }
}

void PasswordManager::encrypt() {
    std::fstream outFile;
    outFile.open(pathToFile,std::ios::out);
    if(outFile.is_open()){
        int lastKey = 0;
        int lastCharOfPas = -1;
        outFile << timestamp << "\n";

        for(int j=0; j<passwords.size(); j++){
            std::string password = passwords.at(j).toString();
            for(int i=0; i<password.length(); i++){
                lastCharOfPas++;
                if(lastCharOfPas == currentMasterPassword.length()){
                    lastCharOfPas = 0;
                }
                int temp = (int)password[i];
                password[i] = (char)((temp + currentMasterPassword[lastCharOfPas] + lastKey) % 93 + 33);
                lastKey = temp;
            }
            outFile << password;
            if(j+1 != passwords.size()) outFile << "\n";
        }

    }else{
        throw std::logic_error("Problem with open data file");
    }
    outFile.close();
}

void PasswordManager::addPassword(Password password) {
    passwords.push_back(password);
}

void PasswordManager::removePassword(int id) {
    std::cout << "Are you sure to remove the password?(" << passwords.at(id).toString() <<
                 ")\n1. Yes"
                 "\nAnother. No" << std::endl;
    int com;
    std::cin >> com;
    if(com == 1){
        passwords.erase(passwords.begin()+id, passwords.begin()+id+1);
        encrypt();
    } else {
        std::cout << "Deletion canceled" << std::endl;
    }
}

void PasswordManager::removeWithCategory(int id) {
    for(int i=0; i<passwords.size(); i++){
        if(passwords.at(i).getCategory().getId() == id){
            removePassword(i);
        }
    }
    encrypt();
}

void PasswordManager::printAllPassword(bool withId) {
    if (withId) std::cout << "Id" << "\t";
    std::cout << "Tag" << " | " << "Category" << " | " << "Password" << " | " << "Login" << " | " << "Page" << std::endl;
    for(int i=0; i<passwords.size(); i++) {
        Password temp = passwords.at(i);
        if (withId) std::cout << i << " | ";
        std::cout << temp.getTag() << " | " << temp.getCategory().getName() << " | " << temp.getPassword() << " | " << temp.getLogin() << " | " << temp.getPage() << "\n";
    }
}

int PasswordManager::countOfPassword() {
    return passwords.size();
}

Password &PasswordManager::getPassword(int id) {
    return passwords.at(id);
}

void PasswordManager::searchAndPrint(std::string key) {
    std::vector<Password> searched;

    for(int i=0; i<passwords.size(); i++){
        if (
                Logic::lookForSimilarities( passwords.at(i).getTag(), key ) ||
                Logic::lookForSimilarities( passwords.at(i).getPassword(), key ) ||
                Logic::lookForSimilarities( passwords.at(i).getCategory().getName(), key ) ||
                Logic::lookForSimilarities( passwords.at(i).getPage(), key ) ||
                Logic::lookForSimilarities( passwords.at(i).getLogin(), key )
        ){
            searched.push_back(passwords.at(i));
        }
    }
    std::cout << "Tag" << " | " << "Category" << " | " << "Password" << " | " << "Login" << " | " << "Page" << std::endl;
    for(int i=0; i<searched.size(); i++){
        std::cout << searched.at(i).toString() << std::endl;
    }
}


std::string PasswordManager::get(int id, sortType type) {
    Password password = passwords.at(id);
    switch (type) {
        case NON:
            return "";

        case TAG:
            return password.getTag();

        case CATEGORY:
            return password.getCategory().getName();

        case PASSWORD:
            return  password.getPassword();

        case LOGIN:
            return password.getLogin();

        case DOMAIN:
            return password.getPage();
        default:
            throw "Out of bound";
    }
}

int PasswordManager::compareTo(std::string s1, std::string s2) {
    s1 = Logic::toUpperCase(s1);
    s2 = Logic::toUpperCase(s2);

    for(int i=0; i<std::min(s1.length(), s2.length()); i++){
        if(s1[i] > s2[i]){
            return 1;
        }else if(s1[i] < s2[i]){
            return -1;
        }
    }
    return 0;
}

void PasswordManager::sort(sortType first, sortType second) {
    int correctness;
    do{
        correctness = 0;
        for(int i=0; i<passwords.size()-1; i++){
            int compareResult = compareTo( get(i, first), get(i+1, first) );

            if( compareResult > 0 && first != NON){
                Password temp = passwords.at(i);
                passwords[i] = passwords.at(i+1);
                passwords[i+1] = temp;
            } else if( compareResult == 0 && second != NON){

                compareResult = compareTo( get(i, second), get(i+1, second) );
                if( compareResult > 0){
                    Password temp = passwords.at(i);
                    passwords[i] = passwords.at(i+1);
                    passwords[i+1] = temp;
                } else {
                    correctness++;
                }
            } else {
                correctness++;
            }
        }
    }while (correctness != passwords.size()-1);
    encrypt();
}

const bool PasswordManager::searchSamePassword(std::string password, Password& same) {
    for(int i=0; i<passwords.size(); i++){
        if ( std::equal( passwords.at(i).getPassword().begin(), passwords.at(i).getPassword().end(),
                         password.begin(), password.end() ) ){
            same = passwords.at(i);
            return true;
        }
    }
    return false;
}
