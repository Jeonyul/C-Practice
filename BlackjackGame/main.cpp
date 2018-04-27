#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//////////////// Card ////////////////
class Card
{
public:
	enum class eRank { Ace = 1, Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Quin, King };
	enum class eSuit { Clubs, Diamonds, Hearts, Spades };
	friend ostream& operator<<(ostream& os, Card& c);
	Card(eRank rank, eSuit suit, bool isFaceUp = true);
	void Flip();
	int GetValue() const;
private:
	eRank mRank;
	eSuit mSuit;
	bool mbIsFaceUp;

};
Card::Card(eRank rank, eSuit suit, bool isFaceUp)
	: mRank{ rank }, mSuit{ suit }, mbIsFaceUp{ isFaceUp }
{
}
void Card::Flip()
{
	mbIsFaceUp = !mbIsFaceUp;
}
int Card::GetValue() const
{
	int value{ 0 };
	if (mbIsFaceUp)
	{
		value = (int)mRank;
		if (value > 10)
		{
			value = 10;
		}
	}
	return value;
}
ostream& operator<<(ostream& os, Card& c)
{
	/*if (c.mbIsFaceUp)
	{
		if (c.mRank <= Card::eRank::Ten)
		{
			os << (int)c.mRank;
		}
		else if (c.mRank == Card::eRank::Jack)
		{
			os << 'J';
		}
		else if (c.mRank == Card::eRank::Quin)
		{
			os << 'Q';
		}
		else if (c.mRank == Card::eRank::King)
		{
			os << 'K';
		}
		if (c.mSuit == Card::eSuit::Clubs)
		{
			os << 'c';
		}
		else if (c.mSuit == Card::eSuit::Diamonds)
		{
			os << 'd';
		}
		else if (c.mSuit == Card::eSuit::Hearts)
		{
			os << 'h';
		}
		else if (c.mSuit == Card::eSuit::Spades)
		{
			os << 's';
		}
	}
	else
	{
		os << 'X' << 'X';
	}*/
	const char RANKS[] = { '0', 'A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K' };
	const char SUITS[] = { 'c', 'd', 'h', 's' };
	if (c.mbIsFaceUp)
	{
		os << RANKS[static_cast<int>(c.mRank)] << SUITS[static_cast<int>(c.mSuit)];
	}
	else
	{
		os << "XX";
	}

	return os;
}
//-------------------- Hand --------------------//
class Hand
{
public:
	Hand();
	virtual ~Hand();
	void Add(Card* pCard);
	void Clear();
	int GetTotal() const;
protected:
	vector<Card*> mCards;
};
Hand::Hand()
{
	mCards.reserve(7);
}
Hand::~Hand()
{
	Clear();
}
void Hand::Add(Card* pCard)
{
	mCards.push_back(pCard);
}
void Hand::Clear()
{
	//vector<Card*>::iterator iter;
	for (auto iter = mCards.begin(); iter != mCards.end(); iter++)
	{
		delete *iter;
		*iter = nullptr;
	}
	mCards.clear();
}
int Hand::GetTotal() const
{
	if (mCards.empty())
	{
		return 0;
	}
	if (mCards[0]->GetValue() == 0)
	{
		return 0;
	}
	int total = 0;
	for (Card* pCard : mCards)
	{
		total += pCard->GetValue();
	}
	bool IsContainingAce = false;
	for (Card* pCard : mCards)
	{
		if (pCard->GetValue() == static_cast<int>(Card::eRank::Ace))
		{
			IsContainingAce = true;
		}
	}
	if (IsContainingAce && total <= 11)
	{
		total += 10;
	}
	return total;
}
//-------------------- GenericPlayer --------------------//
class GenericPlayer : public Hand
{
public:
	GenericPlayer(const string& name = "") { mName = name; }
	virtual ~GenericPlayer() {}
	virtual bool IsHitting() const = 0;
	bool IsBusted() const;
	void Bust() const;
	friend ostream& operator<<(ostream& os, const GenericPlayer& gp);
protected:
	string mName;
};
bool GenericPlayer::IsBusted() const
{
	if (GetTotal() > 21)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void GenericPlayer::Bust() const
{
	cout << mName << " busts.\n\n";
}
ostream& operator<<(ostream& os, const GenericPlayer& gp)
{
	os << gp.mName << ":\t";
	/*for (Card* c : gp.mCards)
	{
		os << *c << "\t";
	}
	if (!(gp.mCards.empty()) && gp.mCards[0]->GetValue() != 0)
	{
		os << '(' << gp.GetTotal() << ')';
	}*/
	if (!gp.mCards.empty())
	{
		for (Card* c : gp.mCards)
		{
			os << *c << "\t";
		}
		if (gp.mCards[0]->GetValue() != 0)
		{
			os << '(' << gp.GetTotal() << ')';
		}
	}
	else
	{
		os << "<empty>";
	}
	return os;
}
//-------------------- Player --------------------//
class Player : public GenericPlayer
{
public:
	Player(const string& name);
	bool IsHitting() const;
	void Win() const;
	void Lose() const;
	void Push() const;
};
Player::Player(const string& name) : GenericPlayer(name)
{
}
bool Player::IsHitting() const
{
	char c;
	do
	{
		cout << mName << ", do you want a hit? (Y/N): ";
		cin >> c;
		if (c == 'Y' || c == 'y')
		{
			return true;
		}
		else if (c == 'N' || c == 'n')
		{
			cout << endl;
			return false;
		}
	} while (true);
}
void Player::Win() const
{
	cout << mName << " wins.\n";
}
void Player::Lose() const
{
	cout << mName << " loses.\n";
}
void Player::Push() const
{
	cout << mName << " pushes.\n";
}
//-------------------- House --------------------//
class House : public GenericPlayer
{
public:
	House();
	bool IsHitting() const;
	void FlipFirstCard();
};
House::House() : GenericPlayer("House")
{
}
bool House::IsHitting() const
{
	return (GetTotal() <= 16);
}
void House::FlipFirstCard()
{
	if (!mCards.empty())
	{
		mCards[0]->Flip();
	}
	else
	{
		cout << "No card to flip!\n";
	}
}
//-------------------- Deck --------------------//
class Deck : public Hand
{
public:
	Deck();
	void Populate();
	void Shuffle();
	void Deal(GenericPlayer& aGenericPlayer);
	//void Deal(Hand& ahand);
	void AdditionalCards(GenericPlayer& aGenericPlayer);
};
Deck::Deck()
{
	mCards.reserve(52);
	Populate();
}
void Deck::Populate()
{
	Clear();
	for (int i = static_cast<int>(Card::eSuit::Clubs); i <= static_cast<int>(Card::eSuit::Spades); i++)
	{
		for (int j = (int)Card::eRank::Ace; j <= (int)Card::eRank::King; j++)
		{
			Add(new Card(static_cast<Card::eRank>(j), static_cast<Card::eSuit>(i)));
		}
	}
}
void Deck::Shuffle()
{
	if (!mCards.empty())
	{
		random_shuffle(mCards.begin(), mCards.end());
	}
	else
	{
		cout << "No cards to shuffle!\n";
	}
}

void Deck::Deal(GenericPlayer& aGenericPlayer)
{
	if (!mCards.empty())
	{
		aGenericPlayer.Add(mCards.back());
		mCards.pop_back();
	}
	else
	{
		cout << "Out of cards. Unable to deal.";
	}
}
//void Deck::Deal(Hand& ahand)
//{
//	if (!mCards.empty())
//	{
//		ahand.Add(mCards.back());
//		mCards.pop_back();
//	}
//	else
//	{
//		cout << "Out of cards. Unable to deal.";
//	}
//}

void Deck::AdditionalCards(GenericPlayer& aGenericPlayer)
{
	while (!(aGenericPlayer.IsBusted()) && (aGenericPlayer.IsHitting()))
	{
		Deal(aGenericPlayer);
		cout << aGenericPlayer << endl;
		if (aGenericPlayer.IsBusted())
		{
			aGenericPlayer.Bust();
		}
	}

}
//---------- Game ----------//
class Game
{
public:
	Game(const vector<string>& names);
	void Play();
private:
	Deck mDeck;
	House mHouse;
	vector<Player> mPlayers;
};
Game::Game(const vector<string>& names)
{
	for (const string& name : names)
	{
		mPlayers.push_back(Player(name));
	}
	srand(static_cast<unsigned int>(time(0)));
	mDeck.Shuffle();
}
void Game::Play()
{
	/*
	// Deal them two initial cards
	for (int i = 0; i < mPlayers.size(); i++)
	{
		for (int j = 0; j < 2; j++)
		{
			mDeck.Deal(mPlayers[i]);
		}
	}
	for (int i = 0; i < 2; i++)
	{
		mDeck.Deal(mHouse);
		if (i == 0)
		{
			mHouse.FlipFirstCard();
		}
	}
	// Display hands
	cout << endl;
	for (int i = 0; i < mPlayers.size(); i++)
	{
		cout << mPlayers[i] << endl;
	}
	cout << mHouse << endl << endl;
	for (int i = 0; i < mPlayers.size(); i++)
	{
		while (mPlayers[i].IsHitting())
		{
			mDeck.AdditionalCards(mPlayers[i]);
			cout << mPlayers[i] << endl;
			if (mPlayers[i].IsBusted())
			{
				mPlayers[i].Bust();
				break;
			}
		}
		cout << endl;
	}
	mHouse.FlipFirstCard();
	cout << mHouse << endl;
	while (mHouse.IsHitting())
	{
		mDeck.AdditionalCards(mHouse);
		cout << mHouse << endl;
		if (mHouse.IsBusted())
		{
			mHouse.Bust();
		}
	}
	*/

	// vector<Player>::iterator pPlayer;
	for (int i = 0; i < 2; i++)
	{
		/*for (auto pPlayer = mPlayers.begin(); pPlayer != mPlayers.end(); pPlayer++)
		{
			mDeck.Deal(*pPlayer);
		}*/
		for (Player& p : mPlayers)
		{
			mDeck.Deal(p);
		}
		mDeck.Deal(mHouse);
	}
	mHouse.FlipFirstCard();
	
	cout << endl;
	for (const Player& p : mPlayers)
	{
		cout << p << endl;
	}
	cout << mHouse << endl;

	for (Player& p : mPlayers)
	{
		mDeck.AdditionalCards(p);
	}
	mHouse.FlipFirstCard();
	cout << mHouse << endl;
	mDeck.AdditionalCards(mHouse);

	if (mHouse.IsBusted())
	{
		for (const Player& p : mPlayers)
		{
			if (!p.IsBusted())
			{
				p.Win();
			}
		}
	}
	else
	{
		for (const Player& p : mPlayers)
		{
			if (!p.IsBusted())
			{
				if (mHouse.GetTotal() < p.GetTotal())
				{
					p.Win();
				}
				else if (mHouse.GetTotal() > p.GetTotal())
				{
					p.Lose();
				}
				else
				{
					p.Push();
				}
			}
		}
	}
	for (Player& p : mPlayers)
	{
		p.Clear();
	}
	mHouse.Clear();
}
//////////////// main ////////////////
int main()
{
	cout << "\tWelcome to Blackjack!\n\n";
	int numPlayers = 0;
	while (numPlayers < 1 || numPlayers > 7)
	{
		cout << "How many players? (1 - 7): ";
		cin >> numPlayers;
	}
	vector<string> names;
	string name;
	for (int i = 0; i < numPlayers; i++)
	{
		cout << "Enter player name: ";
		cin >> name;
		names.push_back(name);
	}

	Game aGame(names);
	char again = 'y';
	while (again != 'n' && again != 'N')
	{
		aGame.Play();
		cout << "Do you want to play again? (Y/N): ";
		cin >> again;
	}
	return 0;
}
