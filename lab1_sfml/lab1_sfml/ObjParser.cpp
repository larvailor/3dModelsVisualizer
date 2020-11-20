#include "ObjParser.hpp"

#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>

std::vector<Vertex> ObjParser::parseObj(const std::string& pathToObjFile)
{
	std::vector<glm::vec3> vertexPosition;   // координаты вершины в 3х мерном пространстве
	std::vector<glm::vec3> vertexTexCoord;   // текстурные координаты вершины
	std::vector<glm::vec3> vertexNormal;	 // вектор нормали вершины

	std::vector<unsigned> vertexPositionIndicies;
	std::vector<unsigned> vertexTexCoordIndicies;
	std::vector<unsigned> vertexNormalIndicies;

	std::vector<Vertex> verticies;

	std::ifstream objFile;
	objFile.open(pathToObjFile, std::ios::in);
	if (!objFile.is_open())
	{
		throw "Error! Could not load obj";
	}

	std::string line, prefix;
	std::stringstream ss;
	glm::vec3 vec3(1.0f);
	unsigned index;
	unsigned counter;
	while (std::getline(objFile, line))
	{
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "v")
		{
			ss >> vec3.x >> vec3.y >> vec3.z;
			vertexPosition.push_back(vec3);
		}
		else if (prefix == "vt")
		{
			ss >> vec3.x >> vec3.y >> vec3.z;
			vertexTexCoord.push_back(vec3);
		}
		else if (prefix == "vn")
		{
			ss >> vec3.x >> vec3.y >> vec3.z;
			vertexNormal.push_back(vec3);
		}
		else if (prefix == "f")
		{
			// f 24/1/24 25/2/25 26/3/26
			counter = 0;

			ss.str(line.substr(2));
			while (ss >> index)
			{
				if (counter == 0)
				{
					vertexPositionIndicies.push_back(index);
				}
				else if (counter == 1)
				{
					vertexTexCoordIndicies.push_back(index);
				}
				else if (counter == 2)
				{
					vertexNormalIndicies.push_back(index);
				}

				if (ss.peek() == '/')
				{
					counter++;
					ss.ignore(1, '/');
				}
				else if (ss.peek() == ' ')
				{
					counter = 0;
				}

			}

			//std::istringstream ss(line.substr(2));
			//std::vector<glm::ivec3> polygon;
			//for (auto i = 0; i < 3; i++)
			//{
			//	std::string vertexInfo;
			//	ss >> vertexInfo;
			//	std::replace(vertexInfo.begin(), vertexInfo.end(), '/', ' ');
			//	std::istringstream tmpSs(vertexInfo);
			//	glm::ivec3 vec3(1.0f);
			//	tmpSs >> vec3.x;
			//	tmpSs >> vec3.y;
			//	tmpSs >> vec3.z;
			//	polygon.push_back(vec3);
			//}
			//obj->F.push_back(polygon);
		}
	}

	verticies.resize(vertexPositionIndicies.size(), Vertex());

	for (unsigned i = 0; i < verticies.size(); i++)
	{
		verticies[i].position = vertexPosition[vertexNormalIndicies[i] - 1];
		verticies[i].texCoord = vertexTexCoord[vertexTexCoordIndicies[i] - 1];
		verticies[i].normal = vertexNormal[vertexNormalIndicies[i] - 1];
		verticies[i].color = glm::vec3(1.0f, 1.0f, 1.0f);
	}

	objFile.close();

	return verticies;
}
