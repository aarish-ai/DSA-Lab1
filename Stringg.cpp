#include <iostream>
#include <string>
using namespace std;

int findSubstring(string text, string pattern) {
    for (int i = 0; i <= text.length() - pattern.length(); i++) { // checks the indexes of the text to find the pattern
        int j = 0;

        while (j < pattern.length() && text[i + j] == pattern[j]) { // loops until the length of the pattern and keeps going forward as long as 
            j++;                                                    // the pattern is continuing
        }

        if (j == pattern.length()) {                // if it has completed a loop, and j has got to the length of the pattern it would mean the
            return i;                               // the pattern is there
        }
    }

    return -1;
}

int main() {
    // Pattern at the beginning
    cout << findSubstring("hello world", "hello") << endl;

    // Pattern at the end
    cout << findSubstring("hello world", "world") << endl;

    // Pattern not present
    cout << findSubstring("hello world", "abc") << endl;

    // Empty pattern
    cout << findSubstring("hello world", "") << endl;

}