#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <set>
#include "product.h"

class Book : public Product{
public:
    Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author); // Constructor
    ~Book();
    std::set<std::string> keywords() const; // returns the appropriate keywords to index the product
    std::string displayString() const;
    void dump(std::ostream& os) const;
private:
    std::string isbn_;
    std::string author_;
};
#endif