#pragma once

class Window
{
private:
	int window_width;
	int window_height;

	const char* title = "Program";

public:
	Window(int width, int height);

	void create_window(int argc, char** argv);
	void init_glew();

	int getWindowWidth() { return window_width; }
	int getWinodwHeight() { return window_height; }
};
