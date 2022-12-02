//
// Created by RanVolt on 15.06.2022.
//

#ifndef PASSWORDMANAGER_PASSWORD_H
#define PASSWORDMANAGER_PASSWORD_H


#include <string>
#include "Category.h"

class Password {
private:
    int category;
    std::string tag, password, page, login;

public:
    Password(const std::string &tag, const std::string &password, const int &category);

    void setTag(const std::string &tag);

    void setPassword(const std::string &password);

    void setCategory(const int &id);

    void setPage(const std::string &page);

    void setLogin(const std::string &login);

    const std::string &getTag() const;

    const std::string &getPassword() const;

    const Category &getCategory() const;

    const std::string &getPage() const;

    const std::string &getLogin() const;

    const int getDifficult();

    std::string toString();

    static Password parse(std::string text);

    Password();
};


#endif //PASSWORDMANAGER_PASSWORD_H
