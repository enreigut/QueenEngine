#pragma once

#include "FileReader.h"
#include "StringUtils.h"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct ObjData
{
	std::string name;
	std::vector<float> vertices;
	std::vector<float> texCoord;
	std::vector<float> normals;
	bool smoothShading;
	std::vector<unsigned int> vertexIndices;
	std::vector<unsigned int> texIndices;
	std::vector<unsigned int> normalIndices;
};

class ObjParser
{
public:
	ObjParser();
	~ObjParser();
			
	// Getter
	inline const ObjData& GetObjData() { return m_objData; }

	// Setter

	// Derived
	void Parse(std::string& objFileSoource);
	void Parse(const char* filePath);

private:
	void ParseName(std::string& s);
	void ParseVertex(std::string& s);
	void ParseTex(std::string& s);
	void ParseNormal(std::string& s);
	void ParseSmoothShading(std::string& s);
	void ParseFace(std::string& s);

private:
	ObjData m_objData;
	FileReader m_fileReader;
};
