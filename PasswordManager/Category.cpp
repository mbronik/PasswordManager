//
// Created by RanVolt on 16.06.2022.
//

#include <iostream>
#include "Category.h"
#include "Logic.h"
#include "PasswordManager.h"


std::vector<Category> Category::categoryList;

Category::Category() {
    id = -1;
}

Category::Category(std::string name) {
    id = findUnusedId(0);
    this->name = name;
}

int Category::findUnusedId(int first) {
    for(int i=0; i<categoryList.size(); i++){
        if(first == categoryList.at(i).id){
            return findUnusedId(first+1);
        }
    }
    return first;
}

int Category::parse(std::string text) {
    int idSimilar = searchSimilar(text);
    if(idSimilar >= 0){
        return idSimilar;
    }else{
        return create(text);
    }
}

const Category &Category::getCategory(int id) {
    for(int i=0; i<categoryList.size(); i++) {
        if(categoryList.at(i).id == id)
            return categoryList.at(i);
    }
    throw "Category id out of bound";
}

int Category::create(std::string name) {
    Category temp = Category(name);
    categoryList.push_back( temp );
    return temp.id;
}

void Category::remove(int i) {
    PasswordManager::removeWithCategory(categoryList.at(i).id);
    categoryList.erase(categoryList.begin()+i, categoryList.begin()+i+1);
}

int Category::searchSimilar(std::string name) {
    for(int i=0; i<categoryList.size(); i++){
        if( Logic::checkSimilar(categoryList.at(i).name, name) ){
            return categoryList.at(i).id;
        }
    }
    return -1;
}

void Category::printList() {
    for(int i=0; i<categoryList.size(); i++){
        std::cout << i << ". " << categoryList.at(i).name << std::endl;
    }
}

const std::string &Category::getName() const {
    return name;
}

int Category::getId() const {
    return id;
}

int Category::countOfCategory() {
    return categoryList.size();
}
