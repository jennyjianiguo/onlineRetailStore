#include "clothing.h"
#include "util.h"
using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) :
    Product(category, name, price, qty)
{
    size_ = size;
    brand_ = brand;
}

Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const
{
    set<string> return_key = parseStringToWords(name_);
    set<string> brands = parseStringToWords(brand_);
    // Add brands as keywords
    for (set<string>::iterator it=brands.begin(); it!=brands.end(); ++it) {
        return_key.insert(*it);
    }

    // iterate over set and print (TEST)
    // for (set<string>::iterator it=return_key.begin(); it!=return_key.end(); ++it) {
    //     cout << *it << endl;
    // }
    return return_key;
}

std::string Clothing::displayString() const
{
    string display;
    display = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + to_string(price_) + " " + to_string(qty_) + " left.";
    return display;
}

void Clothing::dump(std::ostream& os) const
{
    os << "clothing" << endl;
    os << name_ << endl;
    os << price_ << endl;
    os << qty_ << endl;
    os << size_ << endl;
    os << brand_ << endl;
}