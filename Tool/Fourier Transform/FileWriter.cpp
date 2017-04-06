#include "FileWriter.h"

FileWriter::~FileWriter()
{
	m_writer.close();
}

void FileWriter::open(const char * _filename)
{
	m_writer.open(_filename);
}

void FileWriter::write(const char * _text)
{
	if (m_writer.is_open())
	{
		m_writer << _text;
	}
}

void FileWriter::newLine()
{
	write("\n");
}

void FileWriter::close()
{
	if (m_writer.is_open())
	{
		m_writer.close();
	}
}
