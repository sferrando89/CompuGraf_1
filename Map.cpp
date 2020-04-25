#include "Map.h"
#include <vector>
#include <iostream>

using namespace std;

Map::Map()
{

}

Map :: Map(int m, int n, vector<vector<int>> init)
{
	size_m = m;
	size_n = n;
	matrix = vector<vector<cube>>(size_m, vector<cube>(size_n, { 1, false }));
	for (int i = 0; i < size_m; i++) {
		for (int j = 0; j < size_n; j++) {
			matrix[i][j].h = init[i][j];
		}
	}
}

int Map::GetCubeHeight(int i, int j) {
	return matrix[i][j].h;
}

void Map::PaintCube(int i, int j)
{
	matrix[i][j].painted = true;
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