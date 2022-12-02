//
// Created by RanVolt on 17.06.2022.
//

#include "Logic.h"
#include "Password.h"

#include <ctime>
#include <vector>
#include <iostream>

std::string Logic::toUpperCase(std::string text) {
    for(int i=0; i<text.size(); i++) {
        text[i] = std::toupper(text[i]);
    }
    return text;
}

bool Logic::checkSimilar(std::string s1, std::string s2) {
    s1 = toUpperCase(s1);
    s2 = toUpperCase(s2);
    return std::equal(
            s1.begin(), s1.end(),
            s2.begin(), s2.end()
            );
}

const char Logic::randomCharacter(characterType type) {
//    srand(time(NULL));
    switch (type) {
        case BIG:
            return (char)(rand()%26+65);

        case SMALL:
            return (char)(rand()%26+97);

        case NUMBER:
            return (char)(rand()%10+48);

        case SPECIAL:
            int temp = rand()%32;
            if(temp<15){
                return (char)(temp+33);

            }else if(temp>=15 && temp<22){
                return (char)(temp+58-15);

            }else if(temp>=22 && temp<27){
                return (char)(temp+91-22);

            }else{
                return (char)(temp+123-28);
            }
    }
    throw "Out of bound";
}

const std::string Logic::generatePassword(const int length, const bool type[4]) {
    srand(time(NULL));

    if(length<4) throw std::logic_error("Password will be too short");

    std::string password;

    int actualLength = 0;
    for (int i=0; i<4; i++){
        if(type[i]){
            password = password + randomCharacter( characterType(i) );
            actualLength++;
        }
    }

    for(int i=actualLength; i<length; i++){
        bool errorLoop = true;
        int randomType;
        while (errorLoop) {
            randomType = rand() % 4;
            if(type[randomType]) errorLoop = false;
        }
        password = password + randomCharacter( characterType(randomType) );
    }

    for(int i=0; i<length*2; i++){
        int p1 = rand()%length;
        int p2 = rand()%(length-1);
        p2 = p2<p1 ? p2 : p2+1;
        char temp = password[p1];
        password[p1] = password[p2];
        password[p2] = temp;
    }

    return password;
}

const int Logic::checkPasswordDifficulty(std::string text) {
    int difficulty = 0;
    if(text.length()>=12){
        difficulty+=3;
    }else if(text.length()>=10){
        difficulty+=2;
    }else if(text.length()>=8){
        difficulty++;
    }
    if( checkContains(text, BIG) ){
        difficulty++;
    }
    if( checkContains(text, SMALL) ){
        difficulty++;
    }
    if( checkContains(text, NUMBER) ){
        difficulty++;
    }
    if( checkContains(text, SPECIAL) ){
        difficulty++;
    }
    return difficulty;
}

const bool Logic::checkContains(std::string text, Logic::characterType type) {
    for(int i=0; i<text.length(); i++) {
        switch (type) {
            case BIG:
                if(text[i]>=65 && text[i]<=90)
                    return true;
                break;

            case SMALL:
                if(text[i]>=97 && text[i]<=122)
                    return true;
                break;

            case NUMBER:
                if(text[i]>=48 && text[i]<=57)
                    return true;
                break;

            case SPECIAL:
                if((text[i]>=33 && text[i]<=47)
                ||(text[i]>=58 && text[i]<=64)
                ||(text[i]>=91 && text[i]<=96)
                ||(text[i]>=123 && text[i]<=126))
                    return true;
                break;

        }
    }
    return false;
}

bool Logic::lookForSimilarities(std::string text, std::string key) {
    if(text.length() > key.length()) {
        text = Logic::toUpperCase(text);
        key = Logic::toUpperCase(key);
        for (int j = 0; j < text.length() - key.length()+1; j++){
            bool bad = false;
            for (int i = 0; i < key.length() && !bad; ++i) {
                if(key[i] != text[i+j]){
                    bad = true;
                }
            }
            if (!bad) return true;
        }
    }
    return false;
}
