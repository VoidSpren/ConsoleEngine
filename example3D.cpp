#define _3D_ENGINE
#include "ConsoleEngine.h"

class Demo : public ConsoleEngine {

	float despX = 0;
	float despY = 0;
	float despZ = 0;
	float theta = 0;

	Mesh teapot;
	Mesh cube;

	void begin() {
		cube = Mesh(Vec4f(0, 0, 5.f), Vec4f(F_PI / 4.f, F_PI / 4.f, 0), 1.f, "resources/cube.obj");
	};
	void update(float elapsedTime) {
		clear();

		if (keyPressed(LEFT)) despX = -elapsedTime * 10.f;
		else if (keyPressed(RIGHT)) despX = elapsedTime * 10.f;
		else despX = 0;

		if (keyPressed(UP)) despY = -elapsedTime * 10.f;
		else if (keyPressed(DOWN)) despY = elapsedTime * 10.f;
		else despY = 0;

		if (keyPressed(W)) despZ = elapsedTime * 10.f;
		else if (keyPressed(S)) despZ = -elapsedTime * 10.f;
		else despZ = 0;

		if (keyPressed(A)) theta = -elapsedTime * 3.f;
		else if (keyPressed(D)) theta = elapsedTime * 3.f;
		else theta = 0;

		cube.rotation.y += theta;
		cube.pos.x += despX;
		cube.pos.y += despY;
		cube.pos.z += despZ;

		render(cube,X_ROT, Y_ROT);
	};
};

int main() {
	Demo demo;
	if (demo.construct(480, 270, 2, 2) && demo.construct3D(F_PI / 3.f)) {
		demo.start();
	}
}