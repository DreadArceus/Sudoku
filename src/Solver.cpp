#include "Solver.hpp"

Solver::Solver(vector<vector<int>> problem)
{
	grid = problem;
	for(int i = 0; i <27; i++)
	{
		set<int> st;
		validators.push_back(st);
	}
	solve();
}

void Solver::solve()
{
	//initialising validators
	for(int i = 0; i < grid.size(); i++)
	{
		for(int j = 0; j < grid.size(); j++)
		{
			if(grid[i][j] == -1)
			{
				continue;
			}
			int z = 17;
			if(i > 5)
			{
				if(j > 5)
				{
					z += 9;
				}
				else if(j > 2)
				{
					z += 8;
				}
				else
				{
					z += 7;
				}
			}
			else if(i > 2)
			{
				if(j > 5)
				{
					z += 6;
				}
				else if(j > 2)
				{
					z += 5;
				}
				else
				{
					z += 4;
				}
			}
			else
			{
				if(j > 5)
				{
					z += 3;
				}
				else if(j > 2)
				{
					z += 2;
				}
				else
				{
					z++;
				}
			}

			validators[i].insert(grid[i][j]);
			validators[9 + j].insert(grid[i][j]);
			validators[z].insert(grid[i][j]);
		}
	}
	//solving Loop
	set<int> allPossibilities = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	for(int i = 0; i < grid.size(); i++)
	{
		for(int j = 0; j < grid.size(); j++)
		{
			if(grid[i][j] == -1)
			{
				int z = 17;
				if(i > 5)
				{
					if(j > 5)
					{
						z += 9;
					}
					else if(j > 2)
					{
						z += 8;
					}
					else
					{
						z += 7;
					}
				}
				else if(i > 2)
				{
					if(j > 5)
					{
						z += 6;
					}
					else if(j > 2)
					{
						z += 5;
					}
					else
					{
						z += 4;
					}
				}
				else
				{
					if(j > 5)
					{
						z += 3;
					}
					else if(j > 2)
					{
						z += 2;
					}
					else
					{
						z++;
					}
				}
				//Possiblility Calculation
				set<int> possis = allPossibilities;
				for(auto it : validators[i])
				{
					possis.erase(it);
				}
				for(auto it : validators[9 + j])
				{
					possis.erase(it);
				}
				for(auto it : validators[z])
				{
					possis.erase(it);
				}
				//Basic AI Moves:
				if(possis.size() == 1)
				{
					grid[i][j] = *possis.begin();
					validators[i].insert(grid[i][j]);
					validators[9 + j].insert(grid[i][j]);
					validators[z].insert(grid[i][j]);
					i = 0;
					j = -1;
					continue;
				}
			}
		}
	}
}