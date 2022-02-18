#include <iostream>

using namespace std; 

/// <summary>
/// Clears the screen by using VT100 terminal codes. (supported in win10+ only)
/// </summary>
void clear_screen()
{
	cout << "\033c";
}