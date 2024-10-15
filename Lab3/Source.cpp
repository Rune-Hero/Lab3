#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;

class Word
{
public:
	string ukrainian;
	string english;

	Word(string ukr,string eng) : ukrainian(ukr), english(eng) {}
	

	bool operator<(Word other) {
		return ukrainian < other.ukrainian;
	}

	bool operator>=(Word other) {
		return ukrainian >= other.ukrainian;
	}
	
};

class DICTIONARY
{
private:
	vector<Word> words;
public:

	DICTIONARY operator+(Word word)
	{
		words.push_back(word);
		return *this;
	}

	DICTIONARY operator-(Word word) {
		words.erase(remove_if(words.begin(), words.end(),
			[&](Word w) { return w.ukrainian == word.ukrainian && w.english == word.english; }),
			words.end());
		return *this;
	}

	Word operator[](string ukrWord) {
		for (auto word : words) {
			if (word.ukrainian == ukrWord) {
				return word;
			}
		}
	}
	string find(string ukrWord) {
		try {
			if (words.empty()) {
				throw runtime_error("������� �������\n"); 
			}

			for (const auto& word : words) {
				if (word.ukrainian == ukrWord) {
					return word.english;  
				}
			}

			return "�������� �� ��������"; 
		}
		catch (const exception& e) {
			cerr << e.what(); 
			return ""; 
		}
	}

	void print()
	{
		for (auto word : words)
		{
			cout << word.ukrainian << " - " << word.english << endl;
		}

	}
};
int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	DICTIONARY MyDictionary;

	MyDictionary + Word("�����", "hello");
	MyDictionary + Word("������", "dog");
	MyDictionary + Word("�����", "bird");

	cout << "�������:\n";
	MyDictionary.print();

	cout << "������� ���� ��������� ����� '�����':\n";
	MyDictionary - Word("�����", "bird");
	MyDictionary.print();

	//string translation = MyDictionary.find("�����");
	Word translation = MyDictionary["�����"];


	cout << "\n�������� ����� '�����' - " << translation.english << endl;

	translation = MyDictionary.find("egegd");
	cout << "�������� ����� 'egegd' - " << translation.ukrainian << endl;

	return 0;
}