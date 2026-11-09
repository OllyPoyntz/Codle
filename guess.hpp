/* This file contains functions relating to user guesses,
including actual I/O, validation, and comparison to the word.*/

#pragma once
#include "algo.hpp"

namespace codle {

// Take user input until the word is of the correct length and permissible:
std::string get_user_guess(const std::vector<std::string> valid_words, const uint8_t guesses_left) {
    // Declare a string to store the guess;
    std::string guess;
    // Repeat until the guess is of appropriate length:
    bool word_valid = false;
	static const std::string numbers[6] = {"first", "second", "third", "fourth", "fifth", "sixth"};
    while (!word_valid) {
        std::cout << "Enter your " << numbers[6 - guesses_left] << " guess.\n->";

        // Read guess from standard input:
        std::getline(std::cin, guess);
        if (guess.length() != 5) {
            std::cout << "Your guess must be exactly 5 letters." << std::endl;
        }
        else if (!binary_search(valid_words, to_upper(guess))) {
            std::cout << "\"" << guess << "\" is not a valid word." << std::endl;
        }
        else {
            word_valid = true;
        }
    }
    return to_upper(guess);
}

/* Output feedback to the user based on a list of colours. */
void output_feedback(const std::vector<std::string>& colours) {
    // Constant characters:
    const char green = 'O';
    const char grey = 'X';
    const char yellow = '~';

    // ANSI terminal colour codes:
    #ifdef __ansi__
    const std::string code_green = "\033[32m";
    const std::string code_yellow = "\033[33m";
    const std::string code_reset = "\033[0m";
    #endif

    // Start by printing two characters to match the input offset:
    std::cout << "<-";
    // Loop over each colour and print the corresponding symbol:
    for (size_t i = 0; i < 5; i++) {
        std::string colour = colours[i];
        if (colour == "GREY") {
            std::cout << grey;
        }
        else if (colour == "YELLOW") {
            #ifdef __ansi__
            std::cout << code_yellow << yellow << code_reset;
            #else
            std::cout << yellow;
            #endif
        }
        else {
            #ifdef __ansi__
            std::cout << code_green << green << code_reset;
            #else
            std::cout << green;
            #endif
        }
    }
    
    // Flush the output stream:
    std::cout << "->" << std::endl;
}

/* Guess checking algorithm - writes to a list of colours, then outputs feedback.
   Returns true if the guess is fully correct. */

bool check_guess(const std::string guess, const std::string word) {
    // The iterator only needs to range from 0-4, so we only need one byte forit:
    uint8_t i, j;
    // Initialise the output list with grey:
    std::vector<std::string> colours;
    colours.clear();
    colours.reserve(5);
    for (i = 0; i < 5; i++) {
        colours.push_back("GREY");
    }

    // Iterate over each letter in the word, checking for matches:
    for (i = 0; i < 5; i++) {
        if (word[i] == guess[i]) {
            // Character matches; store "GREEN" in the output list
            colours[i] = "GREEN";
        }
    }

    // Find correct letters in the wrong position:
    for (i = 0; i < 5; i++) {
        if (colours[i] == "GREY") {
            char letter = guess[i];
            for (j = 0; j < 5; j++) {
                // If the position matches and hasn't been marked green:
                if ((word[j] == letter) && (colours[j] != "GREEN")){
                    colours[i] = "YELLOW";
                }
            }
        }
    }
    output_feedback(colours);
    // Return if the guess matches the puzzle word:
    return guess == word;
}

}