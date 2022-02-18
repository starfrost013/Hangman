#include "HangmanState.h"
#include <iostream>

using namespace std; 

/// <summary>
/// HangmanGame.h
/// 
/// Hangman game class definition
/// 
/// © 2022 starfrost
/// </summary>
class HangmanGame
{
public: 

	/// <summary>
	/// Plays the game.
	/// </summary>
	void Play();

	/// <summary>
	/// Defines the wordlist that will be used for the game.
	/// </summary>
	static const char* Words[];

	/// <summary>
	/// Defines the list of permitted characters
	/// </summary>

	static const char* Characters[];
	
	/// <summary>
	/// Defines the current game state.
	/// </summary>
	HangmanState State;

private: // State and private functions

	/// <summary>
	/// Determines if the game is running.
	/// </summary>
	bool Running;

	/// <summary>
	/// Static: holds the current word that is to be guessed
	/// </summary>
	static string CurrentWord;

	/// <summary>
	/// Static: holds the current partially guessed string, containing all unguessed characters replaced with _s.
	/// </summary>
	static string PartiallyGuessedString;
	
	/// <summary>
	/// Holds the characters that have already been guessed.
	/// </summary>
	static string GuessedCharacters;

	/// <summary>
	/// Check if the user wishes to play again.
	/// </summary>
	bool Play_AskForAnotherPlay();
};