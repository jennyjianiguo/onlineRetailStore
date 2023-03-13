# onlineRetailStore
This project models a simplified version of an online retail system such as Amazon using C++ STL classes and linear data structures.

## Project Summary
- Read a database of products from certain categories as well as users and their associated information
- Allow a user to interactively search for products based on certain keywords returning the products that match the search
- From those matches, the program will allow a user to add select items to their "cart", view items in their cart, purchase the items in their cart, and save the updated database of product and user information

## Data Format
The online retail system will sell products of various categories. All products (no matter the type) will have a: 
- Name
- Price
- Quantity in stock

The system supports 3 categories of products, and each category will supply additional fields of data as indicated below:
- Book: ISBN, author
- Clothing: size, brand
- Movie: genre, rating

The program will also support a set of known users with a:
- Username
- Credit amount
- Type (identifying "prime" users)

This information can be stored and accessed through **database.txt**

## Keywords
The system has an index mapping keywords to the set of products that match that keyword. A product should match a keyword if it appears in the product name or one of the following attributes below (dependent on specific type of product):
- Book: the words in the author’s name, the book’s ISBN number
- Clothing: the words in the brand
- Movie: the movie’s genre

For the product name, book author, and clothing brand, a keyword is defined to be any string of 2 or more characters. If such a word has punctuation it is split at each punctuation character and the resulting substrings (of 2 or more characters) are used as keywords.

## Online Store Features
**Adding to Cart**: Allows each user to add products to their personal shopping cart
- The ```ADD username hit_result_index``` command causes the product with index ```hit_result_index from``` the previous search result to be added to username's cart (case insensitive)
- If a product is added to a cart twice, they are treated  as separate items and stored in the user cart twice. This implies that each command of ```ADD``` adds 1 product to the CART
- The results from the last search are retained until a new search is performed. Thus, the hits from one search can be referenced by many ```ADD``` commands
- The cart is maintained in FIFO (first-in, first-out) order
- If the username or ```hit_result_index``` is either not provided, or invalid, the command will not be processed

**Viewing Cart**: Allows each user to view products in their shopping cart
- The ```VIEWCART username``` command prints the products in username's cart (case insensitive) at the current time
- The items are printed with ascending index number for users to easily count how many items are in the cart
- If the username provided is invalid, the command will not be processed

**Buying Cart**: Allows each user to check out all products in their cart
- The ```BUYCART username``` command causes the program to iterate through the items in username's cart (case insensitive)
- If the item is in stock AND the user has enough money, it is removed from the cart, the in stock quantity is reduced by 1, and the product price isdebited from the user’s available credit
- If an item is not in stock or the user does not have enough credit, the product is left in the cart and the program iterates to the next product
- The cart implementation iterates through the products in the order they were added
- If the username provided is invalid, the command will not be processed

**Quiting the Program**: Allows user to exit online retail store
- The ```QUIT filename``` command creates a new version of the database using the format described above to be saved to a file with name "filename"
- The new file represents the updated state of the database (i.e. changing product quantities and user credit) to reflect purchases
- Note: Within the various sections, users and products may be written in any order (not necessarily matching the order of the input database file)
