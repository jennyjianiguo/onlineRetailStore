#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <vector>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    set<string> return_set;
    stringstream ss(rawWords);
    string word;
    while (ss >> word) {
        vector<int> index; // indices with punctuation
        word = convToLower(word);
        int split = 0;
        for (size_t i=0; i<word.size(); i++) {
            if (ispunct(word[i])) {
                split = 1;
                index.push_back(i); // keep track of indices with punctuation
            }
        } 
        // There are no punctuations in word
        if (split == 0) {
            return_set.insert(word);
        }
        // There are punctuations in word
        else {
            int flag = 0;
            string new_word;
            for (size_t i=0; i<index.size()+1; i++) {
                // Index 0 to first flag
                if (i == 0) {
                    new_word = word.substr(0, index[i]);
                }
                // Middle flags
                else if (i != index.size()) {
                    new_word = word.substr(flag, index[i]-flag);
                }
                // Last flag to final word
                else if (i == index.size()) {
                    new_word = word.substr(flag, word.size()-flag);
                }
                else { }
                // Add words to set
                if (new_word.size() >= 2) {
                    return_set.insert(new_word);
                }
                if (i != index.size()) {
                    flag = index[i]+1;
                }
            }
        }
    }
    // Print all keywords
    // cout << "====Keywords====" << endl;
    // for (set<string>::iterator it=return_set.begin(); it != return_set.end(); ++it) {
    //     cout << *it << endl;
    // }

    return return_set;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}