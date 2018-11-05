#pragma once
#include <string>
using namespace std;
struct Song
{

	string title;
	int votes;

	Song();

};

Song::Song()
{

	votes = 0;

}