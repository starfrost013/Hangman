// Global hangman stuff
#include <iostream>

using namespace std;

/// <summary>
/// Maximum number of hangman guesses
/// </summary>
const int HANGMAN_MAX_GUESSES = 8; // 8 seems to be the most common, per wikipedia?

/// <summary>
/// Version string printed on start
/// </summary>
const char* HANGMAN_VERSION_STRING = "Hangman v1.5 © 2022 starfrost (February 18, 2022)"; // add a second line

/// <summary>
/// Clears the screen
/// </summary>
void clear_screen();