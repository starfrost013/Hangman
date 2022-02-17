// Global hangman stuff
#include <iostream>

using namespace std;

/// <summary>
/// Maximum number of hangman guesses
/// </summary>
const int HANGMAN_MAX_GUESSES = 8; // 8 on wikipedia

/// <summary>
/// Version string printed on start
/// </summary>
const char* HANGMAN_VERSION_STRING = "Hangman v1.0 © 2022 starfrost (February 17, 2022)"; // add a second line

/// <summary>
/// Clears the screen
/// </summary>
void clear_screen();