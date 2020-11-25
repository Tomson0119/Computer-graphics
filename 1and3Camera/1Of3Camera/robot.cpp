#include "robot.h"
#include "shader.h"
#include "cube.h"

Robot::Robot()
{
	outWorld = glm::mat4(1.0f);

	pos = glm::vec3(0.0f);
	firstPos = pos;

	angle_all = 0.0f;
	angle_arm = 0.0f;
	increse_arm = 0.6f;
	face = 0.0f;
	gap = 0.2f;

	float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	float g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	float b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

	// Head
	objs.push_back(new Cube(1.0f, 1.0f, 0.0f));
	objs.at(0)->setWorldScale(0.3f);
	objs.at(0)->setWorldTranslate(0.0f, -0.38f, 0.0f);

	// Body
	objs.push_back(new Cube(r, g, b));
	objs.at(1)->setWorldScale(0.3f, 0.4f, 0.3f);
	objs.at(1)->setWorldTranslate(0.0f, -0.66f, 0.0f);

	// Left Arm
	objs.push_back(new Cube(g, b, r));
	objs.at(2)->setWorldScale(0.15f, 0.4f, 0.3f);
	objs.at(2)->setWorldTranslate(-0.6f, -0.66f, 0.0f);

	// Right Arm
	objs.push_back(new Cube(g, b, r));
	objs.at(3)->setWorldScale(0.15f, 0.4f, 0.3f);
	objs.at(3)->setWorldTranslate(0.6f, -0.66f, 0.0f);

	// Left Leg
	objs.push_back(new Cube(b, r, g));
	objs.at(4)->setWorldScale(0.15f, 0.4f, 0.3f);
	objs.at(4)->setWorldTranslate(-0.24f, -1.05f, 0.0f);

	// Right Leg
	objs.push_back(new Cube(b, r, g));
	objs.at(5)->setWorldScale(0.15f, 0.4f, 0.3f);
	objs.at(5)->setWorldTranslate(0.24f, -1.05f, 0.0f);

	// Face
	objs.push_back(new Cube(0.8f, 0.8f, 0.8f));
	objs.at(6)->setWorldScale(0.23f);
	objs.at(6)->setWorldTranslate(0.0f, -0.52f, 0.14f);

	// Heart
	objs.push_back(new Cube(1.0f, 0.0f, 0.0f));
	objs.at(7)->setWorldScale(0.1f);
	objs.at(7)->setWorldTranslate(0.2f, -2.2f, 0.5f);
}

Robot::~Robot()
{
	for (auto object : objs)
		delete object;
	std::vector<Object*>().swap(objs);
}

void Robot::setPlayer()
{
	// Indicator
	objs.push_back(new Cube(1.0f, 0.0f, 0.0f));
	objs.at(8)->setWorldScale(0.1f);
}

void Robot::reset()
{
	face = 0.0f;
	angle_all = 0.0f;
	translateWorld(firstPos.x - pos.x, firstPos.y - pos.y, firstPos.z - pos.z);
}

glm::vec3 Robot::getBehindPos()
{
	glm::vec3 vec;
	if (face == 180.0f)
		vec = glm::vec3(0.0f, 0.0f, gap);
	else if (face == -90.0f)
		vec = glm::vec3(gap, 0.0f, 0.0f);
	else if (face == 90.0f)
		vec = glm::vec3(-gap, 0.0f, 0.0f);
	else
		vec = glm::vec3(0.0f, 0.0f, -gap);

	return pos + vec;
}

void Robot::translateAlong(const glm::vec2& target, float speed)
{
	float dx = target.x - pos.x;
	float dz = target.y - pos.z;

	float distance = sqrt(pow(dx, 2) + pow(dz, 2));

	if (distance == 0) return;

	float x = dx / distance * speed;
	float z = dz / distance * speed;

	translateWorld(x, pos.y, z);
}

void Robot::translateWorld(const glm::vec3& vec)
{
	pos += vec;
}

void Robot::translateWorld(float x, float y, float z)
{
	pos += glm::vec3(x, y, z);
}

void Robot::rotateAroundCenter(float angle)
{
	angle_all += angle;
}

void Robot::rotateDirection(float angle)
{
	face = angle;
}

void Robot::setTimer()
{
	angle_arm += increse_arm;
	if (angle_arm < -10.0f || angle_arm > 10.0f)
		increse_arm *= -1.0f;
}

void Robot::draw(Shader* shader)
{
	for (unsigned int i = 0; i < objs.size(); i++)
	{
		outWorld = glm::mat4(1.0f);
		outWorld = glm::rotate(outWorld, glm::radians(angle_all), glm::vec3(0.0f, 1.0f, 0.0f));
		outWorld = glm::translate(outWorld, pos);
		outWorld = glm::rotate(outWorld, glm::radians(face), glm::vec3(0.0f, 1.0f, 0.0f));

		float anim = 0.0f;
		if (i == 2 || i == 5)
			anim = angle_arm;
		else if (i == 3 || i == 4)
			anim = -angle_arm;

		outWorld = glm::rotate(outWorld, glm::radians(anim), glm::vec3(1.0f, 0.0f, 0.0f));

		shader->setMat4("outWorld", outWorld);
		objs.at(i)->draw(shader);
	}
}
