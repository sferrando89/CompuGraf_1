#pragma once
#include <vector>
#include "Direction.h"
#include "Vector3.h"
using namespace std;

struct cube {
	int h;
	bool painted;
};

class Map
{
private:
	static Map* instance;
	Map(int m, int n, vector<vector<int>> init);
public:
	static Map* GetInstance();
	static Map* GetInstance(int m, int n, vector<vector<int>> init);
	int size_m, size_n;
	std::vector < std::vector <cube>> matrix; // Cambiar el struct cube por la clase cubo

	float isometricSize;
	float isometricOffset;
	float freeOffset;

	Map();
	Map(int m, int n, vector<vector<int>> init, float isoSize, float isoOffset, float fOffset);
	int GetCubeHeight(int i, int j);

	bool PaintCube(int i, int j);

	bool AllCubesPainted();

	void Print();
	void PrintWithCharacter(int i, int j);

	bool isCubePainted(int i, int j);

	bool validMovement(Direction dir,int old_x, int old_y,int x,int y);

	Vector3 getMapCenter();

};

