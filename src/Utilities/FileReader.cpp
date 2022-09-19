#include "FileReader.h"

#include <fstream>
#include <exception>

FileReader::FileReader()
{

}

FileReader::~FileReader()
{

}

void FileReader::ReadFile(const char* filePath)
{
	std::ifstream file(filePath);
	if (file)
	{
		std::stringstream ss;
		ss << file.rdbuf();
		m_data = ss.str();
	}
}
