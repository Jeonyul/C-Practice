#include <iostream>
using namespace std;

constexpr char NUMBER = '7';
struct Token
{
	char kind;
	double value;
};
class TokenStream
{
public:
	TokenStream();
	Token GetToken();
	bool GetIsFull() { return mbIsFull; }
	void PutbackToken(Token t);
private:
	bool mbIsFull;
	Token mBuffer;
};
TokenStream::TokenStream()
	:mbIsFull{ false }, mBuffer{ '0', 0 }
{
}
Token TokenStream::GetToken()
{
	if (mbIsFull)
	{
		mbIsFull = false;
		return mBuffer;
	}
	else
	{
		char c;
		cin >> c;
		switch (c)
		{
		case ';': // for print
		case 'q': // for quit
		case '(': case ')': case '+': case '-': case '*': case '/':
			return Token{ c };
		case '.':
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			cin.putback(c);
			double d;
			cin >> d;
			return Token{ NUMBER, d };
		default:
			cout << "Bad Token" << endl;
			break;
		}

	}
}
void TokenStream::PutbackToken(Token t)
{
	if (!mbIsFull)
	{
		mBuffer = t;
		mbIsFull = true;
	}
	else
	{
		cout << "Buffer is full!" << endl;
	}
}
TokenStream ts;

double expression();
double primary()
{
	Token t = ts.GetToken();
	switch (t.kind)
	{
	case NUMBER:
		return t.value;
	case '-':
		return -primary();
	case '+':
		return primary();
	case '(':
	{
		double d = expression();
		t = ts.GetToken();
		if (t.kind != ')')
		{
			cout << "error: ')' expected" << endl;
		}
		return d;
		break;
	}
	default:
		cout << "error: primary expected" << endl;
		break;
	}
}
double term()
{
	double left = primary();
	Token t = ts.GetToken();
	while (true)
	{
		switch (t.kind)
		{
		case '*':
			left *= primary();
			t = ts.GetToken();
			break;
		case '/':
		{
			double d = primary();
			if (d != 0)
			{
				left /= primary();
				t = ts.GetToken();
			}
			else
			{
				cout << "divide by zero" << endl;
			}
			break;
		}
		default:
			ts.PutbackToken(t);
			return left;
		}
	}
}
double expression()
{
	double left = term();
	Token t = ts.GetToken();
	while (true)
	{
		switch (t.kind)
		{
		case '+':
			left += term();
			t = ts.GetToken();
			break;
		case '-':
			left -= term();
			t = ts.GetToken();
			break;
		default:
			ts.PutbackToken(t);
			return left;
		}
	}
}

int main()
{
	double val = 0;
	while (cin)
	{
		if (!ts.GetIsFull())
		{
			cout << "> ";
		}
		Token t = ts.GetToken();
		if (t.kind == 'q')
		{
			break;
		}
		if (t.kind == ';')
		{
			cout << "= " << val << endl;
		}
		else
		{
			ts.PutbackToken(t);
		}
		if (!ts.GetIsFull())
		{
			cout << "> ";
		}
		val = expression();

	}
	return 0;
}