#ifndef OBJ_PARSER_HPP
#define OBJ_PARSER_HPP

#include <vector>
#include <string>

#include "glm/glm.hpp"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 texCoord;
	glm::vec3 normal;
};


class Obj
{
public:
	Obj() = default;

	std::vector<glm::vec4> V;  // координаты вершины в 3х мерном пространстве
	std::vector<glm::vec3> Vt; // текстурные координаты вершины
	std::vector<glm::vec3> Vn; // вектор нормали вершины
	std::vector<std::vector<glm::ivec3>> F;  // полигон, где не менее 3х вершин, описанных через пробел
};

class ObjParser
{
public:
	ObjParser() = delete;

	static std::vector<Vertex> parseObj(const std::string& pathToObjFile);
};


#endif // OBJ_PARSER_HPP
