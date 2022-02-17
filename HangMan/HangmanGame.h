#include "HangmanState.h"

/// <summary>
/// HangmanGame.H
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

private:

	/// <summary>
	/// Determines if the game is running.
	/// </summary>
	bool Running;

	/// <summary>
	/// Holds the currently selected word.
	/// </summary>
	char* CurrentWord;

	/// <summary>
	/// Holds the current string modified to replace the characters not currently guessed by the user with the _ character.
	/// </summary>
	char* PartiallyGuessedString; 

	/// <summary>
	/// Check if the user wishes to play again.
	/// </summary>
	bool Play_AskForAnotherPlay();
};