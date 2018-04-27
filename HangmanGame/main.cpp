#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
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
	srand((unsigned int)time(0));
	vector<string> words;
	words.push_back("thinkpad");
	words.push_back("samsung");
	words.push_back("amazon");
	words.push_back("protein");
	random_shuffle(words.begin(), words.end());
	const string THE_WORD = words[0];
	string soFar(THE_WORD.size(), '-');
	string used;
	constexpr int MAX_WRONG = 8;
	unsigned int wrong = 0;

	cout << "Welcome to Hangman. Good luck!\n\n\n";
	while ((wrong < MAX_WRONG) && (soFar != THE_WORD))
	{
		system("CLS");
		cout << "You have " << (MAX_WRONG - wrong) << " incorrect guesses left.\n\n";

		cout << "You've used the following letters: " << used << "\n\n\n";
		cout << "So far, the words is: \n" << soFar << "\n\n\n";
		
		// control user input
		cout << "Enter your guess: ";
		char guess;
		cin >> guess;
		while (used.find(guess) != used.npos)
		{
			cout << "Enter your guess: ";
			cin >> guess;
		}
		cout << "\n\n\n";
		used = used + guess + ", ";

		// modify string soFar
		int matchCount = 0;
		int i = THE_WORD.find(guess);
		while (i != THE_WORD.npos)
		{
			soFar[i] = guess;
			matchCount++;
			i = THE_WORD.find(guess, i + 1);
		}
		if (matchCount == 0)
		{
			wrong++;
		}
	}
	if (soFar == THE_WORD)
	{
		cout << "Congratulation! You guessed it, \"" << soFar << "\"!\n\n";
	}
	else
	{
		cout << "You've been hanged!\n\n" << endl;
	}
	return 0;
}