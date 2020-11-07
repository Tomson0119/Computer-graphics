#include "util.h"

#include <iostream>
#include <ctime>

Util::Util()
{
	srand((unsigned int)time(0));
}

float Util::ccw(const glm::vec2& p1, const glm::vec2& p2, const glm::vec2& p3)
{
	return (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
}

bool Util::isIntersection(Line* line1, Line* line2)
{
	float l1_l2 = ccw(line1->getPoint1(), line1->getPoint2(), line2->getPoint1())
		* ccw(line1->getPoint1(), line1->getPoint2(), line2->getPoint2());
	float l2_l1 = ccw(line2->getPoint1(), line2->getPoint2(), line1->getPoint1())
		* ccw(line2->getPoint1(), line2->getPoint2(), line1->getPoint2());

	return (l1_l2 <= 0) && (l2_l1 <= 0);
}

glm::vec2 Util::getIntersectPoint2(Line* line1, Line* line2)
{
	glm::vec2 p1 = line1->getPoint1(), p2 = line1->getPoint2();
	glm::vec2 p3 = line2->getPoint1(), p4 = line2->getPoint2();

	float x = ((p1.x * p2.y - p1.y * p2.x) * (p3.x - p4.x) 
		- (p1.x - p2.x) * (p3.x * p4.y - p3.y * p4.x)) 
		/ ((p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x));

	float y = ((p1.x * p2.y - p1.y * p2.x) * (p3.y - p4.y) 
		- (p1.y - p2.y) * (p3.x * p4.y - p3.y * p4.x)) 
		/ ((p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x));

	return glm::vec2(x, y);
}

float Util::getPointPosition(const glm::vec2& p0, const glm::vec2& p1, const glm::vec2& p2)
{
	float ret = (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
	std::cout << ret << std::endl;

	return ret;
}

float Util::generateFloat(float low, float high)
{
	return low + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (high - low));
}

glm::vec2 Util::convert_xy(int x, int y)
{
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	float pos_x = static_cast<float>(x - width / 2) /
		static_cast<float>(width / 2);

	float pos_y = static_cast<float>(height / 2 - y) /
		static_cast<float>(height / 2);

	return glm::vec2(pos_x, pos_y);
}