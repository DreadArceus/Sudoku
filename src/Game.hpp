#pragma once

#include <vector>
#include <set>
using namespace std;

class Board
{
public:
	Board(vector<sf::Sprite> nums);
	void makeMaster();
	void makeGrid();
	void move(int num);
	void select(int x, int y);
	bool blacklistCheck(int x, int y);
	bool win();
	sf::Sprite returnNumSprite(int x, int y) {return ((grid[x][y] == -1) ? sf::Sprite() : nums[grid[x][y]]);}
private:
	vector<vector<int>> masterGrid;
	vector<set<int>> validators;
	vector<vector<int>> grid;
	set<pair<int, int>> blacklist;
	vector<sf::Sprite> nums;
	pair<int, int> pos;
};