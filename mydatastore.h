#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <iostream>
#include <string>
#include <map>
#include "datastore.h"

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void dump(std::ostream& ofile);
    void addCart(std::string username, int hit_num, std::vector<Product*> hits);
    void viewCart(std::string username);
    void buyCart(std::string username);
    bool checkUsername(std::string username);


private:
    std::vector<Product*> allProducts_; // vector of products
    std::map<std::string, User*> allUsers_; // map of users
    std::map<std::string, std::vector<Product*>> cart_; // cart for each user
    std::map<std::string, std::set<Product*>> keywordMap_; // map all products associated with keyword

};

#endif