#pragma once
#include "ObjParser.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace Elite;
ObjParser::ObjParser(const char* filepath)
	: m_FilePath(filepath)
	, m_IndexBuffer()
	, m_VertexBuffer()
{
	InitializeParsing();
}

void ObjParser::InitializeParsing()
{
	//Start parsing file
	std::ifstream file;
	file.open(m_FilePath, std::ios::in);

	if (!file.is_open())
	{
		std::cout << "Could not parse given file: \" " << m_FilePath << " \" \n";
		return;
	}
		
	std::string line;
	while (!file.eof())
	{
		std::getline(file, line);
		std::stringstream ss{ line };

		if (line[0] == 'v') //meaning we're looking at a vertex
		{
			FPoint3 vertex;

			//reusing string line to put the first letter in there, then put the 3 numbers in a point
			ss >> line >> vertex.x >> vertex.y >> vertex.z; 
			m_VertexBuffer.push_back(vertex);
		}
		else if (line[0] == 'f') //meaning we're looking at indices
		{
			int indices[3];
			//reusing string line to put the first letter in there, then put the 3 indices in the buffer
			ss >> line;
			for (unsigned int i = 0; i < 3; ++i)
			{
				//Push index to int array
				ss >> indices[i];

				//Keep in mind! The indices in the obj file start from 1 and not 0
				m_IndexBuffer.push_back(indices[i] - 1); 
			}
		}
	}
}

void ObjParser::LoadBuffers(std::vector<int>& indexBuffer, std::vector<Elite::FPoint3>& vertexBuffer)
{
	indexBuffer = m_IndexBuffer;
	vertexBuffer = m_VertexBuffer;
}
