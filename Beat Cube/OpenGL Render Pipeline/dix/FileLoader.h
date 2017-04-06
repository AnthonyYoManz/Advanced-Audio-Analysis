#pragma once
#include <fstream>
#include <string>
#include <iostream>
namespace dix
{
	class FileLoader
	{
	private:
		std::string m_fileContents;
	public:
		FileLoader(std::string _filename = "")
		{
			m_fileContents = "";
			if (_filename != "")
			{
				loadFile(_filename);
			}
		}

		const char* loadFile(std::string _filename)
		{
			std::ifstream reader;
			reader.open(_filename.c_str());
			if (reader.is_open())
			{
				m_fileContents = "";
				std::string line;
				while (std::getline(reader, line))
				{
					m_fileContents += line + "\n";
				}
				reader.close();
				return m_fileContents.c_str();
			}
			else
			{
				std::cout << "File: '" << _filename << "' did not open successfully.\n";
			}
			return "";
		}
		const char* getFileContents()
		{
			return m_fileContents.c_str();
		}
	};
}