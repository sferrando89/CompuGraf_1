#pragma once

//STD Libs
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

//SDL_OpenGl
#include <SDL.h>
#include <SDL_opengl.h>
//OUR Libs
#include "Vector3.h"



static std::vector<Vector3> loadOBJ(const char* file_name)
{
	//Vertex positions
	std::vector<Vector3> vertex_positions;

	//Face vectors
	std::vector<GLint> vertex_position_indicies;

	//Vertex array
	std::vector<Vector3> vertices;

	std::stringstream ss;
	std::ifstream in_file(file_name);
	std::string line = "";
	std::string prefix = "";
	Vector3 temp_vec3;
	
	GLint temp_glint = 0;

	//File open error check
	if (!in_file.is_open())
	{
		throw "ERROR::OBJLOADER::Could not open file.";
	}

	//Read one line at a time
	while (std::getline(in_file, line))
	{
		//Get the prefix of the line
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "#")
		{

		}
		else if (prefix == "o")
		{

		}
		else if (prefix == "s")
		{

		}
		else if (prefix == "use_mtl")
		{

		}
		else if (prefix == "v") //Vertex position
		{
			ss >> temp_vec3.x >> temp_vec3.y >> temp_vec3.z;
			vertex_positions.push_back(temp_vec3);
		}
		else if (prefix == "vt")
		{
			//Texturas 2D
		}
		else if (prefix == "vn")
		{
			//Normal de las texturas
		}
		else if (prefix == "f")
		{
			while (ss >> temp_glint)
			{
				vertex_position_indicies.push_back(temp_glint);	
			}
		}
		else
		{
			//Si viene otra cosa no hago nada
		}
	}

	//Build final vertex array (mesh)
	vertices.resize(vertex_position_indicies.size());

	//Load in all indices
	for (size_t i = 0; i < vertices.size(); ++i)
	{
		vertices[i] = vertex_positions[vertex_position_indicies[i] - 1];
		
	}

	//DEBUG
	/*
	std::cout << "Nr of vertices: " << vertices.size() << "\n";

	//Loaded success
	std::cout << "OBJ file loaded!" << "\n";

	*/
	return vertices;

}
