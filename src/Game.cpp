#include "Game.hpp"
#include "Solver.hpp"
#include <ctime>
#include <random>
using namespace std;

Board::Board(vector<sf::Sprite> nums)
{
	pos = {-1, -1};
	this->nums = nums;
	grid.resize(9);
	for(int i = 0; i < grid.size(); i++)
	{
		grid[i] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
	}
	masterGrid = grid;
	for(int i = 0; i < 27; i++)
	{
		set<int> st;
		validators.push_back(st);
	}
	do
	{
		makeMaster();
		makeGrid();
	} while (!solvable());
}

void Board::makeMaster()
{
	srand(time(0));
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			int z = 0;
			if(i > 5)
			{
				if(j > 5)
				{
					z = 26;
				}
				else if(j > 2)
				{
					z = 25;
				}
				else
				{
					z = 24;
				}
			}
			else if(i > 2)
			{
				if(j > 5)
				{
					z = 23;
				}
				else if(j > 2)
				{
					z = 22;
				}
				else
				{
					z = 21;
				}

			}
			else
			{
				if(j > 5)
				{
					z = 20;
				}
				else if(j > 2)
				{
					z = 19;
				}
				else
				{
					z = 18;
				}
			}

			int x = rand() % 9 + 1;
			int cracks = 0;
			while(!(validators[i].count(x) == 0 && validators[9 + j].count(x) == 0 && validators[z].count(x) == 0))
			{
				x = rand() % 9 + 1;
				cracks++;
				if(cracks > 100)
				{
					masterGrid = grid;
					i = 0;
					j = -1;
					for(int i = 0; i < validators.size(); i++)
					{
						validators[i] = set<int>();
					}
					break;
				}
			}
			if(cracks > 100)
			{
				continue;
			}
			masterGrid[i][j] = x;
			validators[i].insert(x);
			validators[9 + j].insert(x);
			validators[z].insert(x);
		}
	}
}

void Board::makeGrid()
{
	for(int i = 0; i < 40; i++)
	{
		int x = rand() % 9, y = rand() % 9;
		while(grid[x][y] != -1)
		{
			x = rand() % 9;
			y = rand() % 9;
		}
		blacklist.insert({x, y});
		grid[x][y] = masterGrid[x][y];
	}
}

bool Board::solvable()
{
	Solver sl(grid);
	return masterGrid == sl.getSolution();
}

void Board::move(int num)
{
	if(blacklistCheck(pos.first, pos.second))
	{
		grid[pos.first][pos.second] = num;
	}
}

void Board::select(int x, int y)
{
	this->pos = {x, y};
}

bool Board::win()
{
	return grid == masterGrid;
}

bool Board::blacklistCheck(int x, int y)
{
	return blacklist.count({x, y}) == 0;
}