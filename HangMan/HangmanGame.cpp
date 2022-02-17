#include "HangmanGame.h"
#include "HangmanGlobals.h"
#include <iostream>

using namespace std;

/// <summary>
/// This is the word list.
/// </summary>
const char* HangmanGame::Words[] =
{
	"sheep", "box",
	"antidisestablishmentarianism", "cabinet",
	"uwu", "netherlands",
	"algebra", "differentiation",
	"osmosis", "zephyr",
	"gold", "blues",
	"rnb", "rap",
	"xylophone", "penis",
	"vagina", "computer",
	"linux", "windows",
	"arrow", "detective",
	"cop", "turkmenistan",
	"llanfair­pwllgwyngyll­gogery­chwyrn­drobwll­llan­tysilio­gogo­goch", "5,10,15,20-tetrakis(alpha,alpha,alpha-2-pivalamidophenyl)porphyrin",
	"wooden", "integration",
	"trigonometry", "macos",
	"UbUntU", "hobo",
	"sex", "stadium",
	"entrance"
	"hungary", "czechia",
	"trump", "biden",
	"boris", "balls",
	"cbt"
};

const char* HangmanGame::Characters[] =
{
	"a", "b", "c",
	"d", "e", "f",
	"g", "h", "i",
	"j", "k", "l",
	"m", "n", "o",
	"p", "q", "r",
	"s", "t", "u",
	"v", "w", "x",
	"y", "z"
};

/// <summary>
/// Hangman State Machine
/// </summary>
void HangmanGame::Play()
{
	Running = true; 

	while (Running)
	{
		switch (State)
		{
		// Run at game init.
		case HangmanState::Start:
		{
			// Clear the screen (Win10+ only, has vt100 control character support for console)_ - have a function for this?
			clear_screen(); 
			
			
			cout << HANGMAN_VERSION_STRING << endl;
			cout << "Welcome to Hangman!\n" << endl;

			// Get the current unix time
			// pick a seed, add parts of the time
			time_t system_time = time(nullptr);
			tm system_time_tm;
			localtime_s(&system_time_tm, &system_time);

			int sys_seed = system_time_tm.tm_year
				+ system_time_tm.tm_hour
				+ system_time_tm.tm_min
				+ system_time_tm.tm_sec;

			//seed srand to get random word from wordlist 
			srand(sys_seed);

			// get word number
			
			// rand % with total number of items in array. (size of array) / (size of first item of array)
			// SHOULD equal number of items in array. Hopefully
			int word_number = rand() % sizeof(Words) / sizeof(Words[0]);

			int string_length = strlen(Words[word_number]);
			
			CurrentWord = new char[string_length];

			// lowercase the current word
			for (int i = 0; i < string_length; i++) CurrentWord[i] = tolower(Words[word_number][i]);

			// Add terminator to prevent garbage information
			CurrentWord[string_length] = 0x00;

			// create a new string for the string that contains the user's currently guessed letters
			// and initialise it to be the same length as the user
			PartiallyGuessedString = new char[string_length];
			
			for (int i = 0; i < string_length; i++) PartiallyGuessedString[i] = 0x5F;

			// ...and add another terminator to prevent garbage information
			PartiallyGuessedString[string_length] = 0x00;

			State = HangmanState::Guessing;
		}

		// Run during the main guessing part of the game
		case HangmanState::Guessing:
		{
			// Did you win?
			bool won = false;

			// Number of total guesses
			int guesses = 0;

			// Number guessed correctly
			int num_guessed_correctly = 0;

			string cur_char;

			while (!won && guesses < HANGMAN_MAX_GUESSES)
			{
				// Print out the partially-guessed string, the number of unsuccessful guesses the user has,
				// and prompt them to enter a single character
				cout << "Unsuccessful guesses: " << guesses << "/" << HANGMAN_MAX_GUESSES << endl; // another two lines
				cout << PartiallyGuessedString << "\n" << endl; // two lines
				cout << "Please enter a single character: " << endl;

				cin >> cur_char;

				// this is fucking stupid code
				if (cur_char.length() != 1) continue; // too many characters input

				const char* cur_char_cst = cur_char.c_str();
				// get char
				const char cur_char_cs2 = *cur_char_cst;

				// end of the fucking stupid code

				// Holds the number of matches for the current character
				int matches = 0;

				for (int i = 0; i < strlen(CurrentWord); i++)
				{
					if (CurrentWord[i] == cur_char_cs2)
					{
						matches++;
						// i don't think there is an issue here
						// as we are initialising partiallyguessedstring to the same length
						PartiallyGuessedString[i] = cur_char_cs2;
					}
				}

				if (matches == 0) guesses++; // no matches

				// Clear the screen (Win10+ only, has vt100 control character support for console)_ - have a function for this?
				clear_screen(); 

				// win the game if you have guessed every letter
				if (strcmp(PartiallyGuessedString, CurrentWord) == 0)
				{
					won = true;
					State = HangmanState::Win;
				}

				// too many guesses, lose
				if (!won) State = HangmanState::Lose;
			}
		}
		// run when the player wins
		case HangmanState::Win:
		{
			cout << "You win!\nThe word was: " << CurrentWord << "\n" << endl;

			if (HangmanGame::Play_AskForAnotherPlay())
			{
				State = HangmanState::Start;
			}
			else
			{
				Running = false; 
			}

			// probably shouldn't be necessary
			continue;
		}
		// run when the player loses
		case HangmanState::Lose:
		{
			cout << "You lose.\n The word was: " << CurrentWord << "\n" << endl;

			if (HangmanGame::Play_AskForAnotherPlay())
			{
				State = HangmanState::Start;
			}
			else
			{
				Running = false;
			}

			// probably shouldn't be necessary
			continue;
		}
		}
	}
}

bool HangmanGame::Play_AskForAnotherPlay()
{
	char user_response; 
	bool valid_response = false;

	// this repeats it while no valid response entered
	while (!valid_response)
	{
		cout << "Play again? (Y/N): ";
		cin >> user_response;

		user_response = toupper(user_response);

		if (user_response == 0x59) // 'Y' 
		{
			return true;
		}
		else if (user_response == 0x4E) // 'N'
		{
			return false; 
		}
		
	}

	// return true by default (exit program) if this line of code somehow runs
	return true; 
}