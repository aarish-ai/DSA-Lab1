#include <iostream>
#include <string>
#include <cctype>

using namespace std;


bool isPalindrome(const string& str) {

    int left = 0;

    int right = static_cast<int>(str.length()) - 1;

    while (left < right) {

        // Skip from left
        while (left < right && !isalnum(static_cast<unsigned char>(str[left]))) {


            left++;
        }

        // Skip from right
        while (left < right && !isalnum(static_cast<unsigned char>(str[right]))) {
            right--;
        }

        // Case-insensitively
        if (tolower(static_cast<unsigned char>(str[left])) !=


            tolower(static_cast<unsigned char>(str[right]))) {

            return false;
        }

        // Move pointers inward
        left++;

        right--;
    }

    return true;
}

int main() {
    string input;

    cout << "Enter a string: ";
    if (getline(cin, input)) {

        if (isPalindrome(input)) {


            cout << "\"" << input << "\" is a palindrome." << endl;

        } else {
            cout << "\"" << input << "\" is not a palindrome." << endl;
            
        }
    }

}
