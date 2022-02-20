#include <iostream>

#include "../gfx/texture/texture.h"

int main() {
	libGL2D::Texture *texture = new libGL2D::Texture("./res/gfx/white_ball.png");
	texture->SaveToFile("hello.png");
	delete texture;

	return 0;
}