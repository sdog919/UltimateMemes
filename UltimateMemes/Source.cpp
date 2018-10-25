#include <iostream>
#include "Song.h"
#include <fstream>
#include <string>
#include <array>
using namespace std;

Song** createBracket(Song* songArr, int arrLength, int roundSize, int rounds, bool uneven);
void printBrackets(Song** brackets, int roundSize, int rounds, bool uneven);
void updateStorage(Song**, int, int, int, bool);

int main()
{

	string title_;
	string artist_;
	string rank;
	string loser;
	ifstream inSongs("storage.txt", ios_base::beg);

	int count;
	int rsize;
	int rounds = 0;
	bool uneven = false;

	cout << "How many songs?" << endl;
	cout << "Songs: ";
	cin >> count;
	cout << "How many songs per round?" << endl;
	cout << "Songs per round: ";
	cin >> rsize;

	Song* songs = new Song[count];

	for (int i = 0; i < count; i++)
	{

		getline(inSongs, title_);
		songs[i].title = title_;

		getline(inSongs, artist_);
		songs[i].artist = artist_;

		getline(inSongs, rank);
		songs[i].ranking = stoi(rank);

		getline(inSongs, loser);
		songs[i].loser = (bool)stoi(loser);

	}

	cout << "Songs sorted" << endl;

	if (count % rsize == 0) rounds = count / rsize;
	else
	{

		rounds = (count / rsize) + 1;
		uneven = true;

	}

	Song** brackets = createBracket(songs, count, rsize, rounds, uneven);
	cout << "Brackets created" << endl;

	updateStorage(brackets, count, rsize, rounds, uneven);

	cout << endl;

	int option;
	cout << "What would you like to do?" << endl;
	cout << "1. Print Brackets" << endl;
	cout << "2. Report Votes" << endl;
	cin >> option;

	if(option == 1)
		printBrackets(brackets, rsize, rounds, uneven);

	if (option == 2)
	{

		cout << "Which bracket are you entering results for?" << endl;

		int bracketNum;
		cout << "Bracket: ";
		cin >> bracketNum;
		cout << endl;

		if (uneven && (bracketNum == rounds - 1))
		{

			for (int j = 0; j < count % rsize; j++)
			{

				cout << '\t';
				cout << j + 1 << ". " << brackets[bracketNum][j].title << " -- " << brackets[bracketNum][j].artist << endl;

			}

			cout << endl;

		}
		else
		{

			for (int j = 0; j < rsize; j++)
			{

				cout << '\t';
				cout << j + 1 << ". " << brackets[bracketNum][j].title << " -- " << brackets[bracketNum][j].artist << endl;

			}

			cout << endl;

		}

		cout << endl;
		cout << "Which songs won?" << endl;

		int song1, song2, song3;
		cin >> song1 >> song2 >> song3;

		cout << endl;

	}

	return 0;

}

Song** createBracket(Song* songArr, int arrLength, int roundSize, int rounds, bool uneven)
{

	int counter = 0;

	Song** brackets = new Song*[rounds];

	if (uneven)
	{

		for (int i = 0; i < rounds - 1; i++)
		{

			brackets[i] = new Song[roundSize];

		}

		brackets[rounds - 1] = new Song[arrLength % roundSize];

	}
	else
	{

		for (int i = 0; i < rounds; i++)
		{

			brackets[i] = new Song[roundSize];

		}

	}

	if (uneven)
	{
		for (int i = 0; i < rounds - 1; i++)
		{

			for (int j = 0; j < roundSize; j++)
			{

				brackets[i][j] = songArr[counter];
				counter++;

			}

		}

		for (int j = 0; j < arrLength % roundSize; j++)
		{

			brackets[rounds-1][j] = songArr[counter];
			counter++;

		}

	}

	else
	{

		for (int i = 0; i < rounds; i++)
		{


			for (int j = 0; j < roundSize; j++)
			{

				brackets[i][j] = songArr[counter];
				counter++;

			}

		}

	}

	return brackets;

}

void printBrackets(Song** brackets, int roundSize, int rounds, bool uneven)
{

	for (int i = 0; i < rounds - 1; i++)
	{

		cout << "Bracket " << i + 1 << ":" << endl;

		for (int j = 0; j < roundSize; j++)
		{

			cout << '\t';
			cout << j + 1 << ". " << brackets[i][j].title << " -- " << brackets[i][j].artist << " --- Ranking: " << brackets[i][j].ranking << endl;

		}

		cout << endl;

	}

	cout << "Bracket " << rounds << ":" << endl;

	if (uneven)
	{

		for (int j = 0; j < roundSize - 1; j++)
		{

			cout << '\t';
			cout << j + 1 << ". " << brackets[rounds-1][j].title << " -- " << brackets[rounds-1][j].artist << " --- Ranking: " << brackets[rounds - 1][j].ranking << endl;

		}

	}
	else
	{

		for (int j = 0; j < roundSize; j++)
		{

			cout << '\t';
			cout << j + 1 << ". " << brackets[rounds-1][j].title << " -- " << brackets[rounds-1][j].artist << " --- Ranking: " << brackets[rounds - 1][j].ranking << endl;

		}

	}

	cout << endl;

}

void updateStorage(Song** brackets, int count, int rsize, int rounds, bool uneven)
{

	ofstream storageFile("storage.txt", ios_base::beg);

	for (int i = 0; i < rounds - 1; i++)
	{

		for (int j = 0; j < rsize; j++)
		{

			storageFile << brackets[i][j].title << endl;
			storageFile << brackets[i][j].artist << endl;
			storageFile << brackets[i][j].ranking << endl;
			storageFile << brackets[i][j].loser << endl;

		}

	}

	if (uneven)
	{

		for (int j = 0; j < count % rsize; j++)
		{

			storageFile << brackets[rounds-1][j].title << endl;
			storageFile << brackets[rounds-1][j].artist << endl;
			storageFile << brackets[rounds-1][j].ranking << endl;
			storageFile << brackets[rounds-1][j].loser << endl;

		}

	}
	else
	{

		for (int j = 0; j < rsize; j++)
		{

			storageFile << brackets[rounds-1][j].title << endl;
			storageFile << brackets[rounds-1][j].artist << endl;
			storageFile << brackets[rounds - 1][j].ranking << endl;
			storageFile << brackets[rounds - 1][j].loser << endl;

		}

	}

}