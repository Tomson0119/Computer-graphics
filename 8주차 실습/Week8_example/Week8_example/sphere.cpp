#include <cmath>

#include "Sphere.h"

// constants //////////////////////////////////////////////////////////////////
const int MIN_SECTOR_COUNT = 3;
const int MIN_STACK_COUNT = 2;


Sphere::Sphere(const char *color)
{
	this->color = color;
	clearArrays();
	buildVertices(color);
}

Sphere::~Sphere()
{
	clearArrays();
}

void Sphere::clearArrays()
{
	std::vector<glm::vec3>().swap(vertices);
	std::vector<glm::vec3>().swap(colors);
	std::vector<unsigned int>().swap(indices);

	delete vertexArray;
}


///////////////////////////////////////////////////////////////////////////////
// build vertices of sphere with smooth shading using parametric equation
// x = r * cos(u) * cos(v)
// y = r * cos(u) * sin(v)
// z = r * sin(u)
// where u: stack(latitude) angle (-90 <= u <= 90)
//       v: sector(longitude) angle (0 <= v <= 360)
///////////////////////////////////////////////////////////////////////////////
void Sphere::buildVertices(const char *color)
{
	const float PI = acosf(-1);

	float x, y, z, xy;                              // vertex position

	float sectorStep = 2 * PI / sectorCount;
	float stackStep = PI / stackCount;
	float sectorAngle, stackAngle;

	for (unsigned int i = 0; i <= stackCount; ++i)
	{
		stackAngle = PI / 2 - i * stackStep;        // starting from pi/2 to -pi/2
		xy = radius * cosf(stackAngle);             // r * cos(u)
		z = radius * sinf(stackAngle);              // r * sin(u)

		// add (sectorCount+1) vertices per stack
		// the first and last vertices have same position and normal, but different tex coords
		for (unsigned int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;           // starting from 0 to 2pi

			// vertex position
			x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
			y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
			addVertex(x, y, z);
		}
	}

	// indices
	//  k1--k1+1
	//  |  / |
	//  | /  |
	//  k2--k2+1
	unsigned int k1, k2;
	for (unsigned int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);     // beginning of current stack
		k2 = k1 + sectorCount + 1;      // beginning of next stack

		for (unsigned int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			// 2 triangles per sector excluding 1st and last stacks
			if (i != 0)
			{
				addIndices(k1, k2, k1 + 1);   // k1---k2---k1+1
			}

			if (i != (stackCount - 1))
			{
				addIndices(k1 + 1, k2, k2 + 1); // k1+1---k2---k2+1
			}
		}
	}
}

void Sphere::addVertex(float x, float y, float z)
{
	glm::vec3 vertex(x, y, z);
	vertices.push_back(vertex);
	addColor();
}

void Sphere::addColor()
{
	if (color == "red")
		colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
	else if (color == "blue")
		colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
	else if (color == "green")
		colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
	else if (color == "gray")
		colors.push_back(glm::vec3(0.3f, 0.3f, 0.3f));
	else if (color == "yellow")
		colors.push_back(glm::vec3(1.0f, 1.0f, 0.0f));
	else
		colors.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
}

void Sphere::addIndices(unsigned int i1, unsigned int i2, unsigned int i3)
{
	indices.push_back(i1);
	indices.push_back(i2);
	indices.push_back(i3);
}

void Sphere::setVertexArray()
{
	vertexArray = new VertexArray(vertices, colors, indices);
}

void Sphere::draw(Shader* shader)
{
	shader->setWorldTransform(getWorldTransformMat());
	vertexArray->setActive();
	glDrawElements(GL_LINE_LOOP, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, nullptr);
}
