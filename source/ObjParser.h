#pragma once
#include "EMath.h"
#include <string>
#include <vector>

class ObjParser final
{
public:
	ObjParser(const char* filepath);
	ObjParser(const ObjParser& o) = delete;
	ObjParser(ObjParser&& o) = delete;
	ObjParser& operator=(const ObjParser& o) = delete;
	ObjParser& operator=(ObjParser&& o) = delete;

	/* Copies over the IndexBuffer and VertexBuffer to the passed parameters */
	void LoadBuffers(std::vector<int>& indexBuffer, std::vector<Elite::FPoint3>& vertexBuffer);

private:
	void InitializeParsing();

	std::string m_FilePath;
	std::vector<int> m_IndexBuffer;
	std::vector<Elite::FPoint3> m_VertexBuffer;
};

