#pragma once

#include <vector>
#include <set>

using namespace std;

class Solver
{
public:
	Solver(){};
	Solver(vector<vector<int>> problem);
	void setProblem(vector<vector<int>> problem) {grid = problem;}
	void solve();
	vector<vector<int>> getSolution(){return grid;}
private:
	vector<vector<int>> grid;
	vector<set<int>> validators;
};