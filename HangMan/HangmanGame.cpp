#include "HangmanGame.h"
#include "HangmanGlobals.h"
#include <iostream>

using namespace std;

string HangmanGame::CurrentWord;

string HangmanGame::PartiallyGuessedString;

string HangmanGame::GuessedCharacters;

/// <summary>
/// This is the word list.
/// </summary>
const char* HangmanGame::Words[] =
{
	"sheep", "box", "antidisestablishmentarianism", 
	"cabinet", "connection", "disconnected",
	"onomatopoeia", "owo", "uwu", 
	"netherlands", "algebra", "differentiation",
	"osmosis", "zephyr", "gold", 
	"blues", "post-hardcore", "nwa",
	"xylophone", "penis", "vagina", 
	"computer", "linux", "windows",
	"arrow", "detective", "crash", 
	"turkmenistan", "llanfair­pwllgwyngyll­gogery­chwyrn­drobwll­llan­tysilio­gogo­goch", "5,10,15,20-tetrakis(alpha,alpha,alpha-2-pivalamidophenyl)porphyrin",
	"wooden", "integration", "trigonometry", 
	"macos","gentoo", "russia",
	"engine", "technology", "desk",
	"silicon", "caesium", "domain", 
	"range", "function", "variety", 
	"melanin", "chubbyemu", "catastrophe",
	"dave", "incompleteness" "ukraine", 
	"taiwan", "UbUntU", "hobo",
	"sex", "stadium", "mcdonalds", 
	"kfc", "france", "entrance"
	"liberia", "hungary", "czechia", 
	"trump", "biden", "boris", 
	"girl", "boy", "enby", 
	"balls", "cbt", "bondage"
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
			// Clear the screen (Win10+ only, has vt100 control character support for console)
			clear_screen(); 

			cout << HANGMAN_VERSION_STRING << endl;
			cout << "Welcome to Hangman!\n" << endl;

			// Get the current unix time
			// use that as a seed
			
			int num_of_words = sizeof(Words) / sizeof(Words[0]);
			int num_of_characters = sizeof(Characters) / sizeof(Characters[0]);

			time_t system_time = time(nullptr);

			srand(system_time);

			// get word number
			
			// rand % with total number of items in array. (size of array) / (size of first item of array)
			// SHOULD equal number of items in array. Hopefully
			int word_number = rand() % num_of_words; 
			int string_length = strlen(Words[word_number]);

			// Initialise the two strings we have created
			CurrentWord.resize(string_length);
			PartiallyGuessedString.resize(string_length);

			GuessedCharacters.resize(0);

			// lowercase the current word
			for (int i = 0; i < string_length; i++) CurrentWord[i] = tolower(Words[word_number][i]);

			// Add terminator to prevent garbage information
			CurrentWord[string_length] = 0x00;
			
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
				cout << "Remaining guesses: " << (HANGMAN_MAX_GUESSES - guesses) << "/" << HANGMAN_MAX_GUESSES << endl; // another two lines

				cout << "Guessed characters: ";
				for (int i = 0; i < GuessedCharacters.length(); i++) cout << GuessedCharacters[i] << " ";
				cout << endl;

				cout << PartiallyGuessedString << "\n" << endl; // two lines
				cout << "Please enter a single character: " << endl;

				cin >> cur_char;

				int input_length = cur_char.length(); 

				
				if (input_length != 1) 
				{
					clear_screen();
					cout << "Too many characters input!\n" << endl;
					continue; 
				}

				// check for a part of 
				if (GuessedCharacters.find_first_of(cur_char) != string::npos)
				{
					clear_screen(); 
					cout << "You've already guessed that letter!\n" << endl; // two lines
					continue; 
				}

				// this is fucking stupid code

				for (int i = 0; i < input_length; i++) cur_char[i] = tolower(cur_char[i]);

				const char* partial_cstr = PartiallyGuessedString.c_str();
				const char* curword_cstr = CurrentWord.c_str();

				// end of the fucking stupid code

				// Holds the number of matches for the current character
				int matches = 0;

				//looks hackish.
				//but we already guaranteed that this string is  one-length earlier in the code.
				char first_char = cur_char[0];

				for (int i = 0; i < strlen(curword_cstr); i++)
				{
					// add to the guessed word
					if (CurrentWord[i] == first_char)
					{
						matches++;

						PartiallyGuessedString[i] = first_char;
					}
				}

				// add to the guessed characters
				// make sure there are no duplicates
				if (GuessedCharacters.find_first_of(first_char) == string::npos
					&& matches == 0) // like real hangman only the letters you *haven't* guessed should be displayed.)
				{
					// spaghetti but *ok* in this case?
					GuessedCharacters.append(cur_char);
					//GuessedCharacters.append(" ");
				}

				if (matches == 0) guesses++; // no matches, so increase number of failed guesses

				// Clear the screen
				clear_screen(); 

				// win the game if you have guessed every letter
				if (strcmp(partial_cstr, curword_cstr) == 0)
				{
					won = true;
					State = HangmanState::Win;
				}
			}

			// too many guesses so you lose
			if (!won)
			{
				State = HangmanState::Lose;
				continue; // prevent running into next line of code i guess
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
			cout << "You lose.\nThe word was: " << CurrentWord << "\n" << endl;

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
		cout << "Play again? (Y/N): " << endl;
		cin >> user_response;

		user_response = toupper(user_response);

		if (user_response == 'Y')
		{
			return true;
		}
		else if (user_response == 'N')
		{
			return false; 
		}
		// other values will loop
	}

	// return true by default (exit program) if this line of code somehow runs
	return true; 
}