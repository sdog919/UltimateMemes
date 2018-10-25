#pragma once
#include <string>
using namespace std;
struct Song
{

	string title;
	string artist;
	int roundVotes;
	int ranking;
	bool loser;

	Song();

};

Song::Song()
{

	roundVotes = 0;
	ranking = 0;
	loser = false;

}