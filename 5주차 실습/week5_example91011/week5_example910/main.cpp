#include "example.h"
#include "second_example.h"
#include "third_example.h"

Util util = Util(800, 600);
Third_example example = Third_example();

int main(int argc, char** argv)
{
	util.create_window(argc, argv);
	util.init_glew();

	example.init_shader();

	glutDisplayFunc(example.draw);
	glutReshapeFunc(example.reshape);
	glutKeyboardFunc(example.key_event);
	
	// For second_example
	//glutTimerFunc(100, example.setTimer, 1);

	// For third_example
	glutMouseFunc(example.mouse_event);
	glutMotionFunc(example.motion);

	glutMainLoop();
	return 0;
}