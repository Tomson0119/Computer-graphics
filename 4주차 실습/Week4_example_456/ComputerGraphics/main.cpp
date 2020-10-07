#include "triangle_example.h"
#include "circle_example.h"

Util util = Util();
CircleExample example = CircleExample();

int main(int argc, char** argv)
{
	// Create Window
	util.create_window(argc, argv);

	// Initialize GLEW
	util.init_glew();
	
	// Shader program
	example.init_shader();

	// Call_back function
	glutDisplayFunc(example.draw);
	glutReshapeFunc(example.reshape);
	glutKeyboardFunc(example.key_event);
	glutMouseFunc(example.mouse_event);
	
	// Only for circle_example
	glutTimerFunc(100, example.setTimer, 1);

	glutMainLoop();

	return 0;
}

