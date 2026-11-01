/* This file handles the main game logic.*/
#pragma once
#include <clocale>
#include <ctime>
#include "guess.hpp"

namespace codle {

// Setup function which performs miscellaneous tasks:
void setup() {
    // Set the locale to Great Britain, UTF-8 (allowing the printing of Unicode characters):
    setlocale(LC_ALL, "en_GB.utf8");

    // Initialise the random number generator using the current time:
    srand(time(0));

    
}

/* Main game loop */

int gameloop() {
    // Load the words from their files:
    std::vector<std::string> guesswords;
    std::vector<std::string> puzzlewords;

    size_t num_guesswords = load_words(guesswords, "wordlists/guesswords.txt");
    size_t num_puzzlewords = load_words(puzzlewords, "wordlists/puzzlewords.txt");

    // Load failure:
    if ((num_guesswords == 0) || (num_puzzlewords == 0)) {
        return 1;
    }



    // Print an introductory message:
    printf("%s\n%s\n", "Welcome to Codle!", "You have 6 attempts to guess a 5-letter word.");
    bool quit = false;
    while (!quit) {
        // Attempt counter:
        int8_t attempts_left = 6;
        // Generate a random puzzle:
        std::string puzzle = random_word(puzzlewords);
        // Debugging-only:
        #if (DEBUG == true)
        std::cout << "DEBUG: The word is " << puzzle << std::endl;
        #endif

        while (attempts_left > 0) {
            // The guess is validated in get_user_guess(), no need to check it again:
            std::string guess = get_user_guess(guesswords);

            // Evaluate the guess against the puzzle:
            bool success = check_guess(guess, puzzle);
            // Output a congratulatory message:
            if (success) {
                std::cout << "Correct!" << std::endl;
                std::cout << "You got the Codle in " << (7 - attempts_left);
                // Ensure grammatical correctness:
                if (attempts_left != 6) {
                    std::cout << " guesses!" << std::endl;
                }
                else {
                    std::cout << " guess!" << std::endl;
                }
                break;
            }
            // Decrement the number 
            attempts_left--;
        }
        if (attempts_left == 0) {
            // Say what the word was then insult the user:
            std::cout << "The word was \"" << puzzle << "\"" << std::endl;
            std::cout << "Wow. I expected better from you. Can\'t even narrow it down within 6 guesses? You disgust me. Get out of my sight and go back in your time machine." << std::endl;

            // Beep at the user if a function exists to do so:
            #ifdef beep

            for (int i = 0; i < 10; i++) {
                beep(1000, 1000);
            }

            #endif
        }
    
        // Ask the user if they want to play again:
        std::cout << "Play again? (y/n)";
        std::string play_again;
        std::getline(std::cin, play_again);

        play_again = to_upper(play_again);
        if ((play_again.length() == 0) || (play_again[0] != 'Y')) {
            quit = true;
        }
    }
    return 0;
}

}