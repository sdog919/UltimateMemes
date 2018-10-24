#include <iostream>
#include "Song.h"
#include <fstream>
#include <string>
using namespace std;

Song** createBracket(Song* songArr, int arrLength, int roundSize, int rounds);
void printBrackets(Song** brackets, int roundSize, int rounds);

int main()
{

	string title_;
	string artist_;
	ifstream inSongs("SongsDel.txt", ios_base::beg);
	inSongs.seekg(3);

	int count;
	int rsize;
	int rounds = 0;

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

	}

	cout << "Songs sorted" << endl;

	if (count % rsize == 0) rounds = count / rsize;
	else rounds = (count / rsize) + 1;

	Song** brackets = createBracket(songs, count, rsize, rounds);

	printBrackets(brackets, rsize, rounds);

	return 0;

}

Song** createBracket(Song* songArr, int arrLength, int roundSize, int rounds)
{

	int counter = 0;

	Song** brackets = new Song*[rounds];

	for(int i = 0; i < rounds; i++)
	{

		brackets[i] = new Song[roundSize];

	}

	for (int i = 0; i < rounds; i++)
	{

		for (int j = 0; j < roundSize; j++)
		{

			brackets[i][j] = songArr[counter];
			counter++;

		}

	}

	return brackets;

}

void printBrackets(Song** brackets, int roundSize, int rounds)
{

	for (int i = 0; i < rounds; i++)
	{

		cout << "Bracket " << i + 1 << ":" << endl;

		for (int j = 0; j < roundSize; j++)
		{

			cout << '\t';
			cout << j + 1 << ". " << brackets[i][j].title << " -- " << brackets[i][j].artist << endl;

		}

		cout << endl;

	}

}