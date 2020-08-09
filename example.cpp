#include "ConsoleEngine.h"

class Demo : public ConsoleEngine {
	float aux = 3.f;
	float theta = 0;



	void begin() {};
	void update(float elapsedTime) {
		for (int i = 0; i < 4; i++) {
			blendColor(BLUE,MAGENTA, i);
			pixChar = 0x2592;
			fillRect(aux, 3, 50, 30);
			aux += 50;
		}
		aux = 3;
	};
};

int main() {
	Demo demo;
	if (demo.construct(206, 36, 2, 2)) {
		demo.start();
	}
}