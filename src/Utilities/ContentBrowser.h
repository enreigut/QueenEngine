#pragma once

#include <filesystem>

struct FolderAndFile
{
	std::vector<std::filesystem::directory_entry> p_folders;
	std::vector<std::filesystem::directory_entry> p_files;
};

class ContentBrowser
{
public:
	ContentBrowser() {};
	~ContentBrowser() {};

	// Getters

	// Setters

	// Derived
	FolderAndFile GetDirectoryData()
	{
		FolderAndFile res = { {}, {} };

		std::string path;
		for (auto& p : std::filesystem::directory_iterator(p_currentPath))
		{
			path = p.path().string();
			if (p.is_directory())
				res.p_folders.push_back(p);
			else
				res.p_files.push_back(p);
		}

		return res;
	}

public:
	const char* p_directories[1] = { "D:/Dev/Projects/QueenEngine/Assets" };
	int p_count = 0;
	std::filesystem::path p_currentPath = p_directories[0];
};