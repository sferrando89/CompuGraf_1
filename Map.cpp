#include "Map.h"
#include <vector>
#include <iostream>

using namespace std;

Map::Map()
{

}

Map :: Map(int m, int n, vector<vector<int>> init,float isoSize, float isoOffset, float fOffset)
{
	size_m = m;
	size_n = n;
	matrix = vector<vector<cube>>(size_m, vector<cube>(size_n, { 1, false }));
	for (int i = 0; i < size_m; i++) {
		for (int j = 0; j < size_n; j++) {
			matrix[i][j].h = init[i][j];
		}
	}

	isometricSize = isoSize;
	isometricOffset = isoOffset;
	freeOffset = fOffset;
}

int Map::GetCubeHeight(int i, int j) {
	return matrix[i][j].h;
}

bool Map::PaintCube(int i, int j){
	if (matrix[i][j].painted) {
		return false;
	}
	matrix[i][j].painted = true;
	return true;
}

bool Map::AllCubesPainted() {
	for (int i = 0; i < size_m; i++) {
		for (int j = 0; j < size_n; j++) {
			if (matrix[i][j].h > 0 && !matrix[i][j].painted)
			{
				return false;
			}
		}
	}
	return true;
}

void Map :: Print()
{

	for (int i = 0; i < size_m; i++) {
		for (int j = 0; j < size_n; j++) {
			cout << "["<< matrix[i][j].h << " , " << matrix[i][j].painted << "]";
		}
		cout << "\n";
	}
	
}

void Map :: PrintWithCharacter(int i, int j)
{
	char aux;
	for (int i_aux = 0; i_aux < size_m; i_aux++) {
		for (int j_aux = 0; j_aux < size_n; j_aux++) {

			if (i == i_aux && j == j_aux) {
				aux = '*';
			}
			else
			{
				if (matrix[i_aux][j_aux].painted) {
					aux = 't';
				}
				else {
					aux = 'f';
				}
			}
			cout << "[" << matrix[i_aux][j_aux].h << " , " << aux << "]";
		}
		cout << "\n";
	}

	cout << "------------------------------------------------------\n";
}

bool Map::isCubePainted(int i, int j)
{
	return matrix[i][j].painted;
}

bool Map::validMovement(int old_x, int old_y, int x, int y) {
	if (abs(matrix[old_x][old_y].h- matrix[x][y].h)>=2 || matrix[x][y].h == 0) {
		return false;
	}
	return true;
}

Vector3 Map::getMapCenter() {
	float z = 0;
	for (int i = 0; i++; i < size_m) {
		for (int j = 0; j++; j < size_n) {
			if (matrix[i][j].h > z) {
				z = matrix[i][j].h;
			}
		}
	}

	Vector3 center;
	center = Vector3(size_m / 2, size_n / 2, z / 2);
	return center;
}