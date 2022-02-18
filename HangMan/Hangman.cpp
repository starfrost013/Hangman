
#include <iostream>
#include "HangmanGame.h"

/// <summary>
/// Hangman
/// ©2022 starfrost
/// 
/// A simple hangman game for learning C/C++.
/// 
/// Version 0.9.2 (February 17, 2022)
/// 
/// Stuff that probably should be done:
/// * use std::vector instead of arrays
/// * change all the operations that use C const char* to use std::string 
/// * allow the user to define the wordlist
/// * find something else than a hackneyed seed algorithm 
/// </summary>
/// <returns></returns>
int main()
{
    HangmanGame* HG = new HangmanGame();

    HG->Play(); 
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
