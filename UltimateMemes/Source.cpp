#include <iostream>
#include "Song.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

Song** createBracket(Song* songArr, int arrLength, int roundSize, int rounds, bool uneven);
void printBrackets(Song** brackets, int roundSize, int rounds, bool uneven);

int main()
{

	string title_;
	ifstream inSongs("songNames.txt", ios_base::beg);

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

	cout << endl;

	ifstream inVotes("winners.tsv", ios_base::beg);

	string str;
	vector<string> strings;

	while (getline(inVotes, str))
	{

		strings.push_back(str);

	}

	for (int i = 0; i < strings.size(); i++)
	{

		for (int j = 0; j < count; j++)
		{

			if (strings[i].find(songs[j].title) != string::npos)
				songs[j].votes += 1;

		}

	}

	brackets = createBracket(songs, count, rsize, rounds, uneven);

	cout << "Votes Tallied" << endl;

	float avgVote = 0;
	for (int i = 0; i < count; i++)
	{

		avgVote += songs[i].votes;

	}

	avgVote = avgVote / count;

	cout << "Average Vote Per Song: " << avgVote << endl;

	int option;
	bool stop = false;

	while (!stop)
	{

		cout << "What would you like to do?" << endl;
		cout << "1. Print Brackets" << endl;
		cout << "2. Construct final bracket" << endl;
		cout << "3. Search Song" << endl;
		cout << "4. Sort and Print" << endl;
		cin >> option;

		if (option == 1)
			printBrackets(brackets, rsize, rounds, uneven);

		if (option == 2)
		{

			int victoryCount = 0;

			int t;
			cout << "Threshold: ";
			cin >> t;
			cout << "Threshold: " << t << " votes!" << endl;

			for (int i = 0; i < count; i++)
			{

				if (songs[i].votes >= t)
				{
					victoryCount++;
					cout << songs[i].title << endl;
				}

			}

			cout << "Songs on Final Ballot: " << victoryCount << endl;

		}

		if (option == 3)
		{

			cout << "Enter Search Query: ";
			string search;
			cin >> search;
			int count_ = 1;

			for (int i = 0; i < count; i++)
			{

				if (songs[i].title.find(search) != string::npos)
				{
					cout << count_ << ". " << songs[i].title << " --- Votes: " << songs[i].votes << endl;
					count_++;
				}

			}

		}

		if (option == 4)
		{

			//Insertion sort
			for (int i = 1; i < count; i++)
			{

				int j = i; // Goes through the whole list sorting value by value

				while (j > 0 && songs[j].votes > songs[j - 1].votes) // Continues until colors[j] is alphabetically smaller than the name before it or until it is in front of the list (aka properly sorted)
				{

					Song temp = songs[j];
					songs[j] = songs[j - 1];
					songs[j - 1] = temp;
					j--;

				}

			}

			for (int i = 0; i < count; i++)
			{

				cout << i + 1 << ". " << songs[i].title << "  ---  Votes: " << songs[i].votes << endl;

			}

		}

		cout << "Exit?" << endl;

		char ans;
		cin >> ans;
		if (ans == 'y') stop = true;

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
			cout << j + 1 << ". " << brackets[i][j].title << " --- Votes: " << brackets[i][j].votes << endl;

		}

		cout << endl;

	}

	cout << "Bracket " << rounds << ":" << endl;

	if (uneven)
	{

		for (int j = 0; j < roundSize - 1; j++)
		{

			cout << '\t';
			cout << j + 1 << ". " << brackets[rounds-1][j].title << " --- Votes: " << brackets[rounds - 1][j].votes << endl;

		}

	}
	else
	{

		for (int j = 0; j < roundSize; j++)
		{

			cout << '\t';
			cout << j + 1 << ". " << brackets[rounds-1][j].title << " --- Votes: " << brackets[rounds - 1][j].votes << endl;

		}

	}

	cout << endl;

}
