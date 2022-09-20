#include "ObjParser.h"

ObjParser::ObjParser() 
{

}
				
ObjParser::~ObjParser() 
{

}

void ObjParser::Parse(std::string& objFileSoource)
{
	std::istringstream iss(objFileSoource);
			
	std::string line;
	std::string type;
	while (std::getline(iss, line))
	{
		size_t split_pos = line.find_first_of(" ");
		type = line.substr(0, split_pos);
		line = line.substr(split_pos + 1, line.size());

		if (type == "#")
			continue;
				
		if (type == "o")
		{
			ParseName(line);
			continue;
		}

		if (type == "v")
		{
			ParseVertex(line);
			continue;
		}

		if (type == "vt")
		{
			ParseTex(line);
			continue;
		}

		if (type == "vn")
		{
			ParseNormal(line);
			continue;
		}

		if (type == "s")
		{
			ParseSmoothShading(line);
			continue;
		}

		if (type == "f")
		{
			ParseFace(line);
			continue;
		}
	}
}

void ObjParser::Parse(const char* filePath)
{
	m_fileReader.ReadFile(filePath);
	std::string fileData = m_fileReader.GetDataStr();
	Parse(fileData);
}

void ObjParser::ParseName(std::string& s)
{
	m_objData.name = s;
}

void ObjParser::ParseVertex(std::string& s)
{
	std::vector<std::string> splittedLine = StringUtils::Split(s, " ");
	for (
		std::vector<std::string>::iterator i = splittedLine.begin();
		i != splittedLine.end();
		++i
		)
	{
		m_objData.vertices.emplace_back(std::stof(*i));
	}
}

void ObjParser::ParseTex(std::string& s)
{
	std::vector<std::string> splittedLine = StringUtils::Split(s, " ");
	for (
		std::vector<std::string>::iterator i = splittedLine.begin();
		i != splittedLine.end();
		++i
		)
	{
		m_objData.texCoord.emplace_back(std::stof(*i));
	}
}

void ObjParser::ParseNormal(std::string& s)
{
	std::vector<std::string> splittedLine = StringUtils::Split(s, " ");
	for (
		std::vector<std::string>::iterator i = splittedLine.begin();
		i != splittedLine.end();
		++i
		)
	{
		m_objData.normals.emplace_back(std::stof(*i));
	}
}

void ObjParser::ParseSmoothShading(std::string& s)
{
	m_objData.smoothShading = s == "1" ? true : false;
}

void ObjParser::ParseFace(std::string& s)
{
	std::vector<std::string> splittedLine = StringUtils::Split(s, " ");
	for (
		std::vector<std::string>::iterator i = splittedLine.begin();
		i != splittedLine.end();
		++i
		)
	{
		std::vector<std::string> facesSplitted = StringUtils::Split(*i, "/");
				
		m_objData.vertexIndices.emplace_back(std::stoul(facesSplitted[0])-1);
		m_objData.texIndices.emplace_back(std::stoul(facesSplitted[1])-1);
		m_objData.normalIndices.emplace_back(std::stoul(facesSplitted[2])-1);
	}
}
