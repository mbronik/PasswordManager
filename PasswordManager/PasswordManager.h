//
// Created by RanVolt on 15.06.2022.
//

#ifndef PASSWORDMANAGER_PASSWORDMANAGER_H
#define PASSWORDMANAGER_PASSWORDMANAGER_H


#include <vector>
#include "Password.h"

enum sortType{TAG, CATEGORY, PASSWORD, LOGIN, DOMAIN, NON};

class PasswordManager {
    static std::vector<Password> passwords;
    static std::string currentMasterPassword;
    static std::string pathToFile;

    static std::string timestamp;

private:
    /**
     * Compare first string with the specified second string for order.
     * Returns a negative integer, zero, or a positive integer as this object is less than,
     * equal to, or greater than the specified object.
     * @param s1 the object being compared
     * @param s2 the object it is being compared to
     * @return -1/0/1 - less / equal / greater
     */
    static int compareTo (std::string s1, std::string s2);
    /**
     * A method used only to retrieve data for sorting
     * @param id
     * @param type
     * @return
     */
    static std::string get (int id, sortType type);
    /**
     * Creates the last decryption timestamp.
     */
    static void createTimestamp();

public:
    /**
     * Initialize file with encrypted passwords.
     * @param path path to file with encrypted password
     * @param password password to encrypt file
     */
    static void init(const std::string path, const std::string password);

    /**
     * Decrypts or encrypts the file according to the password provided earlier in initialization.
     */
    static void decrypt();
    static void encrypt();

    /**
     * Adds the given password to the vector
     * @param password object of type Password
     */
    static void addPassword(Password password);

    /**
     * Removes the password with the given number in the vector
     * @param id entry of the password in the vector
     */
    static void removePassword(int id);

    /**
     * Returns the password with the given number in vector
     * @param id entry of the password in the vector
     * @return Password object from the vector
     */
    static Password &getPassword(int id);

    /**
     * Removes all passwords with a category with the given id.
     * @param id category id
     */
    static void removeWithCategory(int id);

    /**
     * Prints a password list to the console.
     * @param withId defines whether id identifiers should be displayed before
     */
    static void printAllPassword(bool withId);

    /**
     * Checks the number of passwords.
     * @return returns integer with count of password
     */
    static int countOfPassword();

    /**
     * Search all passwords and all parts of the given key, then print a list of matches found.
     * The key does not have to fully match the searched strings, it can be at the beginning, middle or end.
     * If the string to be searched is less than the key, the comparison does not take place.
     * @param key search key
     */
    static void searchAndPrint(std::string key);

    /**
     * Sorts the password list according to the given categories.
     * The types are expressed in enum sortType.
     * @param first main sort type
     * @param second additional sort type
     */
    static void sort(sortType first, sortType second);

    /**
     * Looks for an identical password.
     * @param password string representing the password that is being searched for
     * @param same if a similar password is found it will be assigned
     * @return returns true if it finds an identical password, and false if not
     */
    const static bool searchSamePassword(std::string password, Password& same);
};


#endif //PASSWORDMANAGER_PASSWORDMANAGER_H
