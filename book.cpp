#include "book.h"
#include "util.h"
using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author) :
    Product(category, name, price, qty)
{
    isbn_ = isbn;
    author_ = author;
}

Book::~Book()
{

}

std::set<std::string> Book::keywords() const
{
    set<string> return_key = parseStringToWords(name_);
    set<string> authors = parseStringToWords(author_); // Add authors as keywords
    for (set<string>::iterator it=authors.begin(); it!=authors.end(); ++it) {
        return_key.insert(*it);
    }
    return_key.insert(isbn_); // Add isbn as keyword

    // iterate over set and print (TEST)
    // for (set<string>::iterator it=return_key.begin(); it!=return_key.end(); ++it) {
    //     cout << *it << endl;
    // }
    return return_key;
}

std::string Book::displayString() const
{
    string display;
    display = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
    return display;
}

void Book::dump(std::ostream& os) const
{
    os << "book" << endl;
    os << name_ << endl;
    os << price_ << endl;
    os << qty_ << endl;
    os << isbn_ << endl;
    os << author_ << endl;
}