# onlineRetailStore
Implementing online retail store using C++ STL classes and linear data structures.

This project models a simplified version of an online retail system such as Amazon.

## Project Features
- Read a database of products from certain categories as well as users and their associated information
- Allow a user to interactively search for products based on certain keywords returning the products that match the search
- From those matches, the program will allow a user to add select items to their "cart", view items in their cart, purchase the items in their cart, and save the updated database of product and user information

## Data Format
The online retail system will sell products of various categories. All products (no matter the type) will have a: 
- name
- price
- quantity in stock

The system supports 3 categories of products, and each category will supply additional fields of data as indicated below:
- book: ISBN, author
- clothing: size, brand
- movie: genre, rating

The program will also support a set of known users with a:
- username
- credit amount
- type (identifying "prime" users)

This information can be stored and accessed through '''database.txt'''
