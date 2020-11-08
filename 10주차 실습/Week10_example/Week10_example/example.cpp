#include "example.h"
#include "line.h"
#include "rectangle.h"
#include "triangle.h"

#include <gl/freeglut.h>
#include <gl/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

#include <iostream>

using namespace glm;

Example::Example(int window_w, int window_h)
{
    shader = new Shader();
    camera = new Camera(window_w, window_h);

    lightPos = vec3(0.0f, 0.0f, 1.0f);

    background = nullptr;

    polygon_mode = GL_FILL;
    isCube = true;
    angle_y = 0.0f, angle_x = 0.0f;
}

Example::~Example()
{
    for (auto object : cube)
        delete object;
    std::vector<Object*>().swap(cube);

    delete shader;
    delete camera;
}

void Example::init()
{
    shader->make_shader("shader.vs", "shader.fs");
    
    camera->translateCameraPos(1.0f, 1.0f, 0.0f);

    background = new Rect("sky.png");
    background->setWorldTranslate(0.0f, 0.0f, -2.0f);
    background->setWorldRotate(10.0f, 0.0f, 1.0f, 0.0f);
    background->setWorldScale(12.0f);

    cube.emplace_back(new Line("y"));
    cube.emplace_back(new Line("x"));
    cube.emplace_back(new Line("z"));
    cube.push_back(new Rect("A.png"));
    cube.push_back(new Rect("B.png"));
    cube.push_back(new Rect("C.png"));
    cube.push_back(new Rect("D.png"));
    cube.push_back(new Rect("E.png"));
    cube.push_back(new Rect("F.png"));

    for (unsigned int i = 3; i < cube.size(); i++)
    {
        cube.at(i)->setPos(0.0f, 0.0f, 0.4f);
        cube.at(i)->translateToPos();
    }

    pyramid.push_back(new Rect("E.png"));
    pyramid.push_back(new Triangle("A.png"));
    pyramid.push_back(new Triangle("B.png"));
    pyramid.push_back(new Triangle("C.png"));
    pyramid.push_back(new Triangle("D.png"));

    for (unsigned int i = 0; i < pyramid.size(); i++)
    {
        pyramid.at(i)->setPos(0.0f, 0.0f, 0.4f);
        pyramid.at(i)->translateToPos();
    }
}

void Example::draw()
{
    // Spheres
    shader->use_program();

    shader->setMat4("view", camera->getViewMat());
    shader->setMat4("proj", camera->getProjMat());	
    shader->setVec3("lightColor", vec3(1.0f, 1.0f, 1.0f));
    shader->setVec3("lightPos", lightPos);
    shader->setVec3("viewPos", camera->getPosition());


    shader->setVec3("objectColor", vec3(1.0f,1.0f,1.0f));	
    background->draw(shader);
    for (unsigned int i = 0; i < 3; i++)
        cube.at(i)->draw(shader);

    if (isCube) {
        shader->setVec3("objectColor", vec3(1.0f, 0.0f, 0.0f));
        cube.at(3)->setWorldMat(1.0f);
        cube.at(3)->setWorldRotate(angle_x, 1.0f, 0.0f, 0.0f);
        cube.at(3)->setWorldRotate(angle_y, 0.0f, 1.0f, 0.0f);
        cube.at(3)->translateToPos();
        cube.at(3)->draw(shader);

        shader->setVec3("objectColor", vec3(0.0f, 1.0f, 0.0f));
        cube.at(4)->setWorldMat(1.0f);
        cube.at(4)->setWorldRotate(angle_x, 1.0f, 0.0f, 0.0f);
        cube.at(4)->setWorldRotate(90.0f + angle_y, 0.0f, 1.0f, 0.0f);
        cube.at(4)->translateToPos();
        cube.at(4)->draw(shader);

        shader->setVec3("objectColor", vec3(0.0f, 0.0f, 1.0f));
        cube.at(5)->setWorldMat(1.0f);
        cube.at(5)->setWorldRotate(angle_x, 1.0f, 0.0f, 0.0f);
        cube.at(5)->setWorldRotate(-90.0f + angle_y, 0.0f, 1.0f, 0.0f);
        cube.at(5)->translateToPos();
        cube.at(5)->draw(shader);

        shader->setVec3("objectColor", vec3(1.0f, 1.0f, 0.0f));
        cube.at(6)->setWorldMat(1.0f);
        cube.at(6)->setWorldRotate(angle_x, 1.0f, 0.0f, 0.0f);
        cube.at(6)->setWorldRotate(180.0f + angle_y, 0.0f, 1.0f, 0.0f);
        cube.at(6)->translateToPos();
        cube.at(6)->draw(shader);

        shader->setVec3("objectColor", vec3(0.0f, 1.0f, 1.0f));
        cube.at(7)->setWorldMat(1.0f);
        cube.at(7)->setWorldRotate(90.0f + angle_x, 1.0f, 0.0f, 0.0f);
        cube.at(7)->setWorldRotate(-angle_y, 0.0f, 0.0f, 1.0f);
        cube.at(7)->translateToPos();
        cube.at(7)->draw(shader);

        cube.at(8)->setWorldMat(1.0f);
        cube.at(8)->setWorldRotate(-90.0f + angle_x, 1.0f, 0.0f, 0.0f);
        cube.at(8)->setWorldRotate(angle_y, 0.0f, 0.0f, 1.0f);
        cube.at(8)->translateToPos();
        cube.at(8)->draw(shader);
    }
    else
    {
        shader->setVec3("objectColor", vec3(1.0f, 0.0f, 0.0f));
        pyramid.at(0)->setWorldMat(1.0f);
        pyramid.at(0)->setWorldRotate(90.0f + angle_x, 1.0f, 0.0f, 0.0f);
        pyramid.at(0)->setWorldRotate(-angle_y, 0.0f, 0.0f, 1.0f);
        pyramid.at(0)->translateToPos();
        pyramid.at(0)->draw(shader);

        shader->setVec3("objectColor", vec3(0.0f, 1.0f, 0.0f));
        pyramid.at(1)->setWorldMat(1.0f);
        pyramid.at(1)->setWorldRotate(angle_x, 1.0f, 0.0f, 0.0f);
        pyramid.at(1)->setWorldRotate(angle_y, 0.0f, 1.0f, 0.0f);
        pyramid.at(1)->translateToPos();
        pyramid.at(1)->draw(shader);

        shader->setVec3("objectColor", vec3(0.0f, 0.0f, 1.0f));
        pyramid.at(2)->setWorldMat(1.0f);
        pyramid.at(2)->setWorldRotate(angle_x, 1.0f, 0.0f, 0.0f);
        pyramid.at(2)->setWorldRotate(90.0f + angle_y, 0.0f, 1.0f, 0.0f);
        pyramid.at(2)->translateToPos();
        pyramid.at(2)->draw(shader);

        shader->setVec3("objectColor", vec3(1.0f, 1.0f, 0.0f));
        pyramid.at(3)->setWorldMat(1.0f);
        pyramid.at(3)->setWorldRotate(angle_x, 1.0f, 0.0f, 0.0f);
        pyramid.at(3)->setWorldRotate(-90.0f + angle_y, 0.0f, 1.0f, 0.0f);
        pyramid.at(3)->translateToPos();
        pyramid.at(3)->draw(shader);

        shader->setVec3("objectColor", vec3(0.0f, 1.0f, 1.0f));
        pyramid.at(4)->setWorldMat(1.0f);
        pyramid.at(4)->setWorldRotate(angle_x, 1.0f, 0.0f, 0.0f);
        pyramid.at(4)->setWorldRotate(180.0f + angle_y, 0.0f, 1.0f, 0.0f);
        pyramid.at(4)->translateToPos();
        pyramid.at(4)->draw(shader);
    }
}

void Example::key_event(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: case 'q': case 'Q':
        glutDestroyWindow(glutGetWindow());
        exit(0);

    case 'm': case 'M':
        polygon_mode = (polygon_mode == GL_FILL) ? GL_LINE : GL_FILL;
        glPolygonMode(GL_FRONT_AND_BACK, polygon_mode);
        break;

    case 'y': case 'Y':
        angle_y += 1.5f;
        break;

    case 'x': case 'X':
        angle_x += 1.5f;
        break;

    case 's': case 'S':
        angle_x = 0.0f;
        angle_y = 0.0f;
        break;

    case 'p': case 'P':
        isCube = !isCube;
        break;
    }
}

void Example::setTimer()
{
 
}
