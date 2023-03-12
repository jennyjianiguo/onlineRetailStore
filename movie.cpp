#include "movie.h"
#include "util.h"
using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) :
    Product(category, name, price, qty)
{
    genre_ = genre;
    rating_ = rating;
}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const
{
    set<string> return_key = parseStringToWords(name_); // Add name as keyword
    set<string> genres = parseStringToWords(genre_); // Add genres as keywords
    for (set<string>::iterator it=genres.begin(); it!=genres.end(); ++it) {
        return_key.insert(*it);
    }
    
    // iterate over set and print (TEST)
    // for (set<string>::iterator it=return_key.begin(); it!=return_key.end(); ++it) {
    //     cout << *it << endl;
    // }
    return return_key;
}

std::string Movie::displayString() const
{
    string display;
    display = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
    return display;
}

void Movie::dump(std::ostream& os) const
{
    os << "movie" << endl;
    os << name_ << endl;
    os << price_ << endl;
    os << qty_ << endl;
    os << genre_ << endl;
    os << rating_ << endl;
}