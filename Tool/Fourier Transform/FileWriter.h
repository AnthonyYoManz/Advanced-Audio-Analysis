#pragma once
#include <fstream>

class FileWriter
{
private:
	std::ofstream m_writer;
public:
	~FileWriter();
	void open(const char* _filename);
	void write(const char* _text);
	void newLine();
	void close();
};