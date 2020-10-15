#pragma once

#include "object.h"
#include "vertexarray.h"

class Line : public Object
{
private:
	float* vPos;

	float* vColor;
	unsigned int* index;

	const unsigned int vNum = 6;
	const unsigned int iNum = 2;

	VertexArray* vertexArray;
public:
	Line(const char* type) {
		if (type == "x") 
		{
			vPos = new float[vNum] { -1.0f, 0.0f, 0.5f,
				1.0f, 0.0f, 0.5f };
		}
		else if (type == "y")
		{
			vPos = new float[vNum] { 0.0f, -1.0f, 0.5f,
				0.0f, 1.0f, 0.5f };
		}
		else
		{
			vPos = new float[vNum] { 0.0f, 0.0f, -1.0f,
				0.0f, 0.0f, 1.0f };
		}
		
		vColor = new float[vNum] { 0.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 0.0f };
		index = new unsigned int[iNum] { 0, 1 };
		vertexArray = nullptr;
	}

	~Line() override {
		delete vertexArray;
	}

	void setVertexArray() override
	{
		vertexArray = new VertexArray(vPos, vColor, index, vNum, iNum);
	}

	void draw() override
	{
		vertexArray->setActive();
		glDrawElements(GL_LINE_LOOP, iNum, GL_UNSIGNED_INT, nullptr);
	}
};