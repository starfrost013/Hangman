/// <summary>
/// HangmanState
/// 
/// February 16, 2022
/// 
/// Defines the current hangman game state.
/// </summary>
enum class HangmanState
{
	Start = 0,
	Guessing = 1,
	Win = 2,
	Lose = 3
};