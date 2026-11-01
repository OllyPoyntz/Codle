/* This file contains miscellaneous algorithms needed by other modules,
which don't specifically relate to Codle but are generally useful.

- Binary search algorithm for a list of words
- Loading a list of words from a file
- Conversion of a string to uppercase
- Random selection from a list of words

Also, because I know my teacher is going to complain about this:
Vectors are equivalent to lists, and I'm not using linked lists because
they have terrible random access speeds.
*/
#pragma once
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace codle {

/* Converts a string to uppercase by swapping lowercase letters with uppercase letters:*/
std::string to_upper(const std::string& instring) {
    // Copy the string to a non-const string:
    std::string outstring = instring;
    const size_t length = instring.length();

    // Iterate over each character in the string:
    for (size_t i = 0; i < length; i++) {
        char current_character = instring[i];

        // Check if it is lowercase (this method looks cursed, but it works):
        if ((current_character >= 'a') && (current_character <= 'z')) {
            outstring[i] = current_character + ('A' - 'a');
        }
    }
    // Return the uppercase string:
    return outstring;
}

/* Loads a list of words from a file, taking the filename and an empty vector as input.
Returns the number of words read from the file. */

size_t load_words(std::vector<std::string>& words, const std::string& filename) {
    size_t words_read = 0;

    // Open the file:
    std::ifstream infile(filename);

    // Print an error message and return 0 if unable to open the file:
    if (!(infile.is_open())) {
        std::cerr << "Unable to open file " << filename << " for reading!" << std::endl;
        return 0;
    }

    // Keep reading lines from the file until everything has been read:
    std::string buffer;
    while (std::getline(infile, buffer)) {
        // Each line gets read to the buffer, ignoring the trailing newline.
        if (buffer.length() > 2) {
            // Make the word uppercase and append it to the list:
            std::string uppercase_word = to_upper(buffer);
            words.push_back(uppercase_word);

            // Increment the number of words read:
            words_read++;
        }
    }
    infile.close();
    return words_read;
}

/* Random word selection. using the built-in rand() function.
Can only choose from the first 65536 values in a list, but there are only 2309 words to guess from. */

std::string random_word(const std::vector<std::string>& words) {
    const size_t length = words.size();
    size_t index_selected = length + 1;

    // Keep choosing a new index until it is inside the list:
    while (!(index_selected < length)) {
        index_selected = rand();
    }

    // Return the word at the randomly generated index:
    return words[index_selected];
}

/* Basic linear search algorithm, used as emergency fallback by the binary search algorithm:*/

bool linear_search(const std::vector<std::string>& words, const std::string target_word) {
    const size_t length = words.size();
    // Iterate over each word in the list:
    for (size_t i = 0; i < length; i++) {
        if (words[i] == target_word) {
            return true;
        }
    }
    return false;
}
/* Binary search algorithm to determine if a word is in a list.
   O(log N) is much better than the O(N) of a linear search, so the more complicated algorithm is worth it.
   Of course, this means the input has to be sorted, but that can be done externally. */

bool binary_search(const std::vector<std::string>& words, const std::string target_word) {
    const size_t length = words.size();

    // Handle edge cases:
    if (length < 10) { return linear_search(words, target_word); }

    // Indexes being searched between:
    size_t left_index = 0;
    size_t right_index = length - 1;

    while (true) {
        // Search in between the 'fencepost' indexes:
        size_t current_index = (left_index + right_index) / 2;
        if (current_index >= length) {
            return false;
        }
        std::string item = words[current_index];
        if (item == target_word) {
            // Match found; terminate
            return true;
        }
        if (item < target_word) {
            // Ignore everything to the left:
            left_index = current_index + 1;
        }
        else {
            // Ignore everything to the right:
            right_index = current_index - 1;
        }
        if (right_index < left_index) {
            break;
        }
    }
    // Failed to locate the target word:
    return false;
}

}