#pragma once

#include <sstream>

class FileReader
{
public:
	FileReader();
	~FileReader();

	// Getters
	inline const char* GetData() const { return m_data.c_str(); }
	inline std::string GetDataStr() const { return m_data; }

	// Setters

	// Derived
	void ReadFile(const char* filePath);

private:
	std::string m_data;
};
