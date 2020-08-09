#define _3D_ENGINE
#include "ConsoleEngine.h"

class Demo : public ConsoleEngine {
	float aux = 3.f;
	float theta = 0;

	Vec4f p1 = { 3.f, 3.f, 1.f };
	Vec4f p2 = { 150.f, 72.f, 15.f };
	Vec4f p3 = { 3.f, 147.f, 1.f };

	Vec4f p4 = { 197.f, 3.f, 1.f };
	Vec4f p5 = { 50.f, 72.f, 15.f };
	Vec4f p6 = { 197.f, 147.f, 1.f };

	void begin() {};
	void update(float elapsedTime) {
		fillTriangle(p1, p2, p3);
		setColor(RED);
		fillTriangle(p4, p5, p6);
	};
};

int main() {
	Demo demo;
	if (demo.construct(200, 150, 2, 2)) {
		demo.start();
	}
}