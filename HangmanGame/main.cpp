#include <iostream>
#include <string>
#include <vector>
using namespace std;
/*
	------
	|    |
	|    O
	|   \|/
	|    |
	|   / \
   / \
*/

int main()
{
	vector<string> strings;
	strings.push_back("programming");
	strings.push_back("network");
	strings.push_back("engineer");
	string secretStr = strings[rand() % strings.size()];
	string displayedStr(secretStr.length(), '-');
	string guessedChars;
	int life = 10;
	cout << displayedStr << endl;
	while (true)
	{
		cout << "Your chance: " << life << endl;
		cout << "Guessed letter:" << guessedChars << endl;
		
		char input;
		do
		{
			cout << "Guess a character: ";
			cin >> input;
		} while ((displayedStr.find(input) != displayedStr.npos) ||
			(guessedChars.find(input) != guessedChars.npos));

		int indexFound = secretStr.find(input);
		guessedChars = guessedChars + " " + input;
		if (indexFound == secretStr.npos)
		{
			life--;
		}
		else
		{
			while (indexFound != secretStr.npos)
			{
				displayedStr[indexFound] = secretStr[indexFound];
				indexFound = secretStr.find(input, indexFound + 1);
			}
		}
		cout << displayedStr << endl;
		if (displayedStr == secretStr)
		{
			cout << "Congratulation!" << endl;
			break;
		}
		else if (life == 0)
		{
			cout << "You hanged.." << endl;
			cout << "The word was " << secretStr << "." << endl;
			break;
		}
	}
	
	return 0;
}