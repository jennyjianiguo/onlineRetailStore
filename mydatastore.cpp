#include "mydatastore.h"
#include "util.h"
using namespace std;

MyDataStore::MyDataStore()
{
}

// Iterate through users and products & deallocate
MyDataStore::~MyDataStore()
{
    // Deallocate all products
    for (size_t i=0; i<allProducts_.size(); i++) {
        delete allProducts_[i];
    }
    // Deallocate all users
    map<string, User*>::iterator it;
    for (it = allUsers_.begin(); it != allUsers_.end(); ++it) {
        delete it->second;
    }
}

// Adds a product to the data store
void MyDataStore::addProduct(Product* p)
{
    allProducts_.push_back(p);
    // Get keywords
    set<string> all_keys = p->keywords();
    // For each keyword
    for (set<string>::iterator it = all_keys.begin(); it != all_keys.end(); ++it) {
        map<string, set<Product*>>::iterator it2 = keywordMap_.find(*it); // Seach for keyword in keyword map
        // If keyword already in map
        if (it2 != keywordMap_.end()) {
            // Update the set to insert new product
            it2->second.insert(p);
        }
        // If keyword not in map
        else {
            // Add a new pair to the map where key is the keyword and the set is just the product
            set<Product*> set_product;
            set_product.insert(p);
            keywordMap_[*it] = set_product;
        }
    }
}

// Adds a user to the data store
void MyDataStore::addUser(User* u)
{
    allUsers_[u->getName()] = u;
    // Add user to cart
    vector<Product*> vec_products;
    cart_[u->getName()] = vec_products;
}

/*
 * Performs a search of products whose keywords match the given "terms"
 *  type 0 = AND search (intersection of results for each term) while
 *  type 1 = OR search (union of results for each term)
 */
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
    std::vector<Product*> return_vector;

    // Search AND
    set<Product*> intersect_set = keywordMap_[terms[0]];
    if (type == 0) {
        for (size_t i=1; i<terms.size(); i++) {
            set<Product*> set2 = keywordMap_[terms[i]];
            intersect_set = setIntersection(intersect_set, set2);
        }
        for (set<Product*>::iterator it=intersect_set.begin(); it != intersect_set.end(); ++it) {
            return_vector.push_back(*it);
        }
    }

    // Search OR
    set<Product*> union_set = keywordMap_[terms[0]];
    if (type == 1) {
        for (size_t i=1; i<terms.size(); i++) {
            set<Product*> set2 = keywordMap_[terms[i]];
            union_set = setUnion(union_set, set2);
        }
        for (set<Product*>::iterator it=union_set.begin(); it != union_set.end(); ++it) {
            return_vector.push_back(*it);
        }
    }

    // return vector of products
    return return_vector;
}

// Reproduce the database file from the current Products and User values
void MyDataStore::dump(std::ostream& ofile)
{
    ofile << "<products>" << endl;
    for (size_t i=0; i<allProducts_.size(); i++) {
        allProducts_[i]->dump(ofile);
    }
    ofile << "</products>" << endl;
    ofile << "<users>" << endl;
    for (map<string, User*>::iterator it = allUsers_.begin(); it != allUsers_.end(); ++it) {
        it->second->dump(ofile);
    }
    ofile << "</users>" << endl;

}

// ADD username search_hit_number
void MyDataStore::addCart(std::string username, int hit_num, vector<Product*> hits)
{
    // Check if username and hit_num are valid
    if (checkUsername(username) == false || hit_num < 1 || hit_num > static_cast<int>(hits.size())) {
        cout << "Invalid request" << endl;
        return;
    }
    // If username and hit_num are valid
    Product* productToAdd = hits[hit_num-1];
    map<string, vector<Product*>>::iterator it = cart_.find(username);
    it->second.push_back(productToAdd);
}

// VIEWCART username
void MyDataStore::viewCart(std::string username)
{
    // Check if username is valid
    if (checkUsername(username) == false) {
        cout << "Invalid username" << endl;
        return;
    }
    // Username is valid -> View cart
    map<string, vector<Product*>>::iterator it = cart_.find(username);
    vector<Product*> products = it->second;
    // Print products
    for (size_t i=0; i<products.size(); i++) {
        cout << endl;
        cout << "Item " << i+1 << endl;
        cout << products[i]->displayString() << endl;
    }
}

// BUYCART username
void MyDataStore::buyCart(std::string username)
{
    // Check if username is valid
    if (checkUsername(username) == false) {
        cout << "Invalid username" << endl;
        return;
    }
    // Find username's cart
    map<string, vector<Product*>>::iterator it = cart_.find(username);
    vector<Product*>* products = &(it->second); // all products in username's cart
    map<string, User*>::iterator it2 = allUsers_.find(username);
    User* user = it2->second; // pointer to user
    // For each item in cart
    while (products->size() > 0) {
        if ((*products)[0]->getQty() > 0 && user->getBalance() >= (*products)[0]->getPrice()) {
            // Reduce stock quantity by 1
            (*products)[0]->subtractQty(1);
            // Subtract price from user's account
            user->deductAmount((*products)[0]->getPrice());
            // Remove item from cart
            products->erase(products->begin());
        }
        else {
          return;
        }
    }
}

// Check if username is valid
bool MyDataStore::checkUsername(std::string username)
{
    map<string, User*>::iterator it = allUsers_.find(username);
    if (it != allUsers_.end()) { // username found
        return true;
    }
    return false; // username not found
}