#include <iostream>
#include <algorithm>
#include <ctime>
#include <regex>
#include <locale>
using namespace std;

class String
{
public:
	char* text = nullptr;
private:
	unsigned int length = 0;
	unsigned int capacity = 80;

public:

	String() : String("", 80) {}

	String(const char* text) : String(text, 80) {}

	String(unsigned int capacity) : String("", capacity) {}

	String(const String& original) : String(original.text, original.capacity) {}

	String(const char* text, unsigned int capacity)
	{
		SetString(text, capacity);
	}

public:

	void SetString(const char* text, unsigned int capacity = 80)
	{
		length = strlen(text);

		if (length == 0)
		{
			this->capacity = capacity = 80;
		}

		else
		{
			if (capacity > length * 10)
				capacity = length * 10;

			if (capacity <= length)
				capacity = length + 1;

			this->capacity = capacity;
		}

		if (this->text != nullptr)
			delete[] this->text;

		this->text = new char[this->capacity];
		strcpy_s(this->text, length + 1, text);
	}

	void Print()
	{
		cout << text << "\n";
	}

	~String()
	{
		if (text != nullptr)
		{
			delete[] text;
			text = nullptr;
		}
	}

	void FromKeybord()
	{
		cout << "Enter text: ";
		char txt[100];
		cin.getline(txt, sizeof(txt));
		SetString(txt);
	}

	bool CompareTo(String& str)
	{
		for (int i = 0; i < strlen(text); i++)
		{
			if (text[i] == str.text[i])
			{
				cout << "true" << "\n";
				return true;
			}
			else
			{
				cout << "false" << "\n";
				return false;
			}

		}
	}

	bool Contains(String& txt)
	{
		return strstr(text, txt.text) != nullptr;
	}

	void Concat(String& txt)
	{
		unsigned int newLength = length + txt.length;
		char* temp = new char[newLength + 1];
		strcpy_s(temp, length + 1, text);
		strcpy_s(temp + length, txt.length + 1, txt.text);
		delete[] text;
		text = temp;
		length = newLength;
	}

	bool EndWith(String& txt)
	{
		if (txt.length > length)
			return false;

		return strcmp(text + length - txt.length, txt.text) == 0;
	}

	bool Startwith(String& txt)
	{
		if (txt.length > length)
			return false;
		return strncmp(text, txt.text, txt.length) == 0;
	}

	int IndexOf(char target)
	{
		for (int i = 0; i < length; ++i)
		{
			if (text[i] == target)
			{
				return i;
			}
		}
		return -1;
	}

	int LastIndexOf(char target)
	{
		for (int i = length - 1; i >= 0; --i)
		{
			if (text[i] == target)
			{
				return i;
			}
		}
		return -1;
	}

	void Remove(int start)
	{
		if (start >= 0 && start < length)
		{
			memmove(text + start, text + start + 1, length - start);
			length--;
			text[length] = '\0';
		}
	}

	void Remove(int start, int count)
	{
		if (start >= 0 && start < length && count > 0)
		{
			memmove(text + start, text + start + count, length - start - count);
			length -= count;
			text[length] = '\0';
		}
	}

	void Replce()
	{
		char oldsymbol = 'o';
		char newsymbol = 'd';
		for (unsigned int i = 0; i < length; ++i)
		{
			if (text[i] == oldsymbol)
			{
				text[i] = newsymbol;
			}
		}
		cout << text << "\n";
	}

	String ToLower()
	{
		_strlwr_s(text, 199);
		return text;
	}

	String ToUpper()
	{

		_strupr_s(text, 199);
		return text;
	}

	void Reverse()
	{
		cout << _strrev(text) << "\n\n";
	}

	void SortAZ()
	{
		sort(text, text + strlen(text));
		cout << text << "\n";
	}

	void SortZA()
	{
		sort(text, text + length, [](char a, char b)
			{
				return tolower(a, locale()) > tolower(b, locale());
			});
		cout << text << "\n";
	}

	void Shuffle()
	{
		random_shuffle(text, text + strlen(text));
		cout << text << "\n";
	}

	void RandomFill()
	{
		for (int f = 0; f < length; f++)
		{
			text[f] = rand() % length;
			text[f] = 'a' + rand() % 26;
			cout << text[f];
		}

	}

	String GetString() const
	{
		String copy = text;
		return text;
	}

	int GetLength() const
	{
		return length;
	}

	int GetCapacity() const
	{
		return capacity;
	}

	void Clear()
	{
		text[0] = '\0';
		length = 0;
	}

	char GetCharIndex(unsigned int index) const
	{
		if (index < length)
		{
			return text[index];
		}
		throw "incorrect index\n";
	}

	void ShrinkToFit()
	{
		if (length + 1 <= capacity)
		{
			return;
		}

		capacity = length + 1;
		char* temp = new char[capacity];
		strcpy_s(temp, capacity, text);
		delete[] text;
		text = temp;
	}

	void ShowInfo() const
	{
		cout << "Text: " << text << "\n";
		cout << "Length: " << length << "\n";
		cout << "Capacity: " << capacity << "\n";
	}
};

bool operator < (const String& a, const String& b)
{
	return strcmp(a.text, b.text) < 0;
}

bool operator > (const String& a, const String& b)
{
	return strcmp(a.text, b.text) > 0;
}

bool operator <= (const String& a, const String& b)
{
	return strcmp(a.text, b.text) <= 0;
}

bool operator >= (const String& a, const String& b)
{
	return strcmp(a.text, b.text) >= 0;
}

bool operator != (const String& a, const String& b)
{
	return strcmp(a.text, b.text) != 0;
}

bool operator == (const String& a, const String& b)
{
	return strcmp(a.text, b.text) == 0;
}

istream& operator>>(istream& i, String& str)
{
	cout << "Enter text: ";
	char txt[100];
	i.getline(txt, sizeof(txt));
	str.SetString(txt);
	return i;
}

ostream& operator<<(ostream& i, const String& str)
{
	cout << str.GetString();
	return cout;
}

int main()
{
	//String a("j");
//String b("Serju");

//if (a == b)
//{
//	cout << "==\n";
//}

//if (a > b)
//{
//	cout << ">\n";
//}

//if (a < b)
//{
//	cout << "<\n";
//}

//if (a >= b)
//{
//	cout << ">=\n";
//}

//if (a <= b)
//{
//	cout << "<=\n";
//}

//if (a != b)
//{
//	cout << "!=\n";
//}

	//String s;
	//cin >> s;
	//cout << s;

	//srand(time(0));
	//String a("Serju");
	//String b("softwear");
	//cout << a.GetCharIndex(0) << "\n";
	//cout << a.GetCharIndex(1) << "\n";
	//cout << a.GetCharIndex(2) << "\n";
	//cout << a.GetCharIndex(3) << "\n";
	//a.FromKeybord();
	//a.EndWith(b);
	//a.Concat(b);
	//a.Remove(2);
	//a.Remove(3, 6);
	//a.ShowInfo();
	//a.ShowInfo();
	//a.CompareTo(b);
	//a.Replce();
	//a.Reverse();
	//a.ToLower();
	//a.Shuffle();
	//a.SortAZ();
	//a.SortZA();
	//a.RandomFill();
	//cout << a.IndexOf('!') << "\n";
	//cout << a.LastIndexOf('!') << "\n";
}