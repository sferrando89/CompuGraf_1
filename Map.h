#pragma once
#include <vector>
#include "Direction.h"
using namespace std;

struct cube {
	int h;
	bool painted;
};

class Map
{
public:
	int size_m, size_n;
	std::vector < std::vector <cube>> matrix; // Cambiar el struct cube por la clase cubo
	Map();
	Map(int m, int n, vector<vector<int>> init);
	int GetCubeHeight(int i, int j);

	bool PaintCube(int i, int j);

	bool AllCubesPainted();

	void Print();
	void PrintWithCharacter(int i, int j);

	bool isCubePainted(int i, int j);

	bool validMovement(Direction dir,int old_x, int old_y,int x,int y);

};

