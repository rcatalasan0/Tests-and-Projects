#include <iostream>
#include <iomanip>
#include <cstring>
#include <string>

using namespace std;

bool palindromeChecker(string);

int main() {
    string word;
    getline(cin,word);              // grabbing word to input

    cout << word << " is ";
    if(!palindromeChecker(word)) {      // wording/grammar for the output :P
        cout << "not ";
    }
    cout << "a palindrome!" << endl;
}

// refurbished to be its own function.
bool palindromeChecker(string input) {
    bool isAPalindrome = true;
    string cmpInput;                        // will be carrying a completely lowercase version of the string input
    for(int i=0; i<input.length(); i++) {   // this removes case sensitivity when checking characters.
        cmpInput[i] = tolower(input[i]);
    }
    int limit = input.length()/2;       // this is the limit of the loop; it's declared here so that it can be adjusted
                                        // depending on the length of the word.
    if(input.length() % 2 != 0) {       // this accounts for inputs that are odd numbers in length
        limit += 1;
    }

    for(int i=0; i < limit; i++) {
        if(cmpInput[i] != (cmpInput[input.length()-i-1])) {
            isAPalindrome = false;                  // don't wanna play with fire by including multiple return statements
            break;                                  // this is just a safer bet :P
        }
        // cout << input[i] << " vs. " << input[input.length()-i-1] << endl;
    }

    return isAPalindrome;           // returns a boolean value; true if a palindrome, false if not
}