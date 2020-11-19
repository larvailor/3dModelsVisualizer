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

	std::vector<glm::vec4> V;  // ���������� ������� � 3� ������ ������������
	std::vector<glm::vec3> Vt; // ���������� ���������� �������
	std::vector<glm::vec3> Vn; // ������ ������� �������
	std::vector<std::vector<glm::ivec3>> F;  // �������, ��� �� ����� 3� ������, ��������� ����� ������
};

class ObjParser
{
public:
	ObjParser() = delete;

	static std::vector<Vertex> parseObj(const std::string& pathToObjFile);
};


#endif // OBJ_PARSER_HPP
