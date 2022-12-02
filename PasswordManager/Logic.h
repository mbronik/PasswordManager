//
// Created by RanVolt on 17.06.2022.
//

#ifndef PASSWORDMANAGER_LOGIC_H
#define PASSWORDMANAGER_LOGIC_H


#include <string>


class Logic {
public:
    enum characterType{BIG=0, SMALL=1, NUMBER=2, SPECIAL=3};

    /**
     * Changes all lowercase letters to uppercase
     * @param text input string
     * @return returns text in uppercase
     */
    static std::string toUpperCase(std::string text);

    /**
     * Checks if string s1 is the same as string s2
     * @param s1
     * @param s2
     * @return true if the strings are the same else false
     */
    static bool checkSimilar(std::string s1, std::string s2);

    /**
     * Checks whether the key is contained in text.
     * @param text
     * @param key
     * @return true if the key is contained in text
     */
    static bool lookForSimilarities(std::string text, std::string key);

    /**
     * Returns a random character of the specified type
     * @param type character type specified enum characterType
     * @return  random char
     */
    const static char randomCharacter(characterType type);

    /**
     * Generates a random password according to given criteria.
     * @param length password length to generate (minimum 4, if less will throw an error)
     * @param type array of length 4, defines what types of characters are to be used in the password in the order of enum characterType
     * @return generated password
     */
    const static std::string generatePassword(int length, const bool type[4]);

    /**
     * Defines the difficulty of a password in relation to the length used and the number of different types of characters.
     * @param text represents the password
     * @return password difficulty level from 0 to 7
     */
    const static int checkPasswordDifficulty(std::string text);

    /**
     * Checks that the text contains the appropriate character type represented by enum characterType.
     * @param text checked text
     * @param type type of shearing character
     * @return
     */
    const static bool checkContains(std::string text, characterType type);
};


#endif //PASSWORDMANAGER_LOGIC_H
