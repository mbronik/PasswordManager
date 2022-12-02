//
// Created by RanVolt on 16.06.2022.
//

#ifndef PASSWORDMANAGER_CATEGORY_H
#define PASSWORDMANAGER_CATEGORY_H


#include <string>
#include <vector>

class Category {
private:
    int id;
    std::string name;

    Category();

    Category(std::string name);

    static std::vector<Category> categoryList;

    static int findUnusedId(int first);

public:
    int getId() const;

    const std::string &getName() const;

    static const Category &getCategory(int id);

    static int create(std::string name);

    static void remove(int no);

    static int searchSimilar(std::string name);

    static void printList();

    static int parse(std::string text);

    static int countOfCategory();
};


#endif //PASSWORDMANAGER_CATEGORY_H
