#include "example.h"

Util util = Util(800,800);
Example example = Example();

int main(int argc, char**argv)
{
	util.create_window(argc, argv);
	util.init_glew();

	example.init_shader();

	glutDisplayFunc(example.draw);
	glutReshapeFunc(example.reshape);
	glutKeyboardFunc(example.key_event);
	glutMouseFunc(example.mouse_event);
	glutTimerFunc(100, example.setTimer, 1);

	glutMainLoop();
	return 0;
}