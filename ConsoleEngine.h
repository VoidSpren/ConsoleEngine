#pragma once
#include <Windows.h>
#include <vector>
#include <thread>
#include <chrono>

void swap (int& n1, int& n2) { int t = n1; n1 = n2; n2 = t; };

/* simple vector struct */
template<typename T>
struct vec2{
	T x;
	T y;

	vec2(T x, T y) : x(x), y(y) {}
	vec2(const vec2<T>& other) : x(other.x), y(other.y) {}
};

/* class encapsuling console drawing functionality */
class ConsoleGraphics {
	int _width;
	int _height;
	int fSizeW;
	int fSizeH;

	bool _set;

protected:
	short color = 0x00FF;
	char pixChar = 0x2588;

	CHAR_INFO* screenBuffer;

	HANDLE hConsole;
	COORD bufferSize;
	SMALL_RECT windowRect;

	ConsoleGraphics() {}
	~ConsoleGraphics() { delete[] screenBuffer; }

	bool set() { return _set; }
	int width() { return _width; }
	int height() { return _height; }

public:
	/*start and setup console so that drawing is possible*/
	bool construct(int w, int h, int fsw, int fsh) {

		_width = w;
		_height = h;
		fSizeW = fsw;
		fSizeH = fsh;
		_set = false;

		screenBuffer = new CHAR_INFO[_width * _height];
		clear();

		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

		/*change NOTHING here, as it is platform dependent and changes in order of execution could cause missbehaviour*/
		windowRect = { 0,0,1,1 };
		bufferSize = { (short)_width, (short)_height };
		CONSOLE_FONT_INFOEX cfi;

		if (hConsole == INVALID_HANDLE_VALUE) return false;

		if (!SetConsoleWindowInfo(hConsole, true, &windowRect)) return false;

		if (!SetConsoleScreenBufferSize(hConsole, bufferSize)) return false;

		if (!SetConsoleActiveScreenBuffer(hConsole)) return false;

		windowRect = { 0, 0, (short)_width - 1, (short)_height - 1 };

		cfi.cbSize = sizeof(cfi);
		cfi.nFont = 0;
		cfi.dwFontSize.X = fSizeW;
		cfi.dwFontSize.Y = fSizeH;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = FW_NORMAL;
		wcscpy_s(cfi.FaceName, L"Consolas");
		if (!SetCurrentConsoleFontEx(hConsole, false, &cfi)) return false;

		if (!SetConsoleWindowInfo(hConsole, true, &windowRect)) return false;

		_set = true;
		return true;
	}

protected:
	/*cleans screenBuffer*/
	void clear() {
		for (int i = 0; i < _width * _height; i++) {
			screenBuffer[i].Char.UnicodeChar = ' ';
			screenBuffer[i].Attributes = 0;
		}
	}

	/*writes to the console whatever there is in the screenBuffer*/
	bool write() {
		if (_set) {
			WriteConsoleOutput(hConsole, screenBuffer, bufferSize, { 0,0 }, &windowRect);
			return true;
		}
		return false;
	}

	/*writes a pixel at the given location to the screenBuffer*/
	void point(int x, int y) {
		if (x < _width && x >= 0 && y < _height && y >= 0) {
			screenBuffer[y * _width + x].Char.UnicodeChar = pixChar;
			screenBuffer[y * _width + x].Attributes = color;
		}
	}
	void point(vec2<int>& pos) {
		point(pos.x, pos.y);
	}

	/*writes a line that goes from and to the given points*/
	void line(int x1, int y1, int x2, int y2) {
		std::vector<vec2<int>> pointBuffer;
		lineBuffer(x1, y1, x2, y2, pointBuffer);
	}

	/*writes the triangle described by the given points*/
	void triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
		std::vector<vec2<int>> pointBuffer;
		lineBuffer(x1, y1, x2, y2, pointBuffer);
		lineBuffer(x2, y2, x3, y3, pointBuffer);
		lineBuffer(x3, y3, x1, y1, pointBuffer);
	}

	/*writes a rectangle with his top-left corner at the given point, and with the given dimensions*/
	void rect(int x, int y, int w, int h) {
		for (int hor = x; hor <= x + w; hor++) {
			point(hor, y);
			point(hor, y + h);
		}
		for (int ver = y + 1; ver < y + h; ver++) {
			point(x, ver);
			point(x + w, ver);
		}
	}

	/*writes a circle centered at the given point, and with the given radius*/
	void circle(int x, int y, int r) {
		int xc = 0, yc = r, d = 3 - (2 * r);

		octant(xc, yc, x, y);
		while (yc >= xc) {
			xc++;
			if (d < 0) d = d + 4 * xc + 6;
			else d = d + 4 * (xc - --yc) + 10;
			octant(xc, yc, x, y);
		}
	}

	/*writes a triangle just as the triangle function, and fill it*/
	void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
		auto horLine = [&](int xi, int xe, int y) {
			if (xe < xi) swap(xi, xe);
			for (int i = xi; i <= xe; i++) point(i, y);
		};

		if (y1 > y3) { swap(y1, y3); swap(x1, x3); }
		if (y1 > y2) { swap(y1, y2); swap(x1, x2); }
		if (y2 > y3) { swap(y2, y3); swap(x2, x3); }

		std::vector<vec2<int>> legs;
		std::vector<vec2<int>> hyp;

		lineBuffer(x1, y1, x2, y2, legs, true);
		legs.pop_back();
		lineBuffer(x2, y2, x3, y3, legs, true);
		legs.pop_back();
		lineBuffer(x1, y1, x3, y3, hyp, true);
		hyp.pop_back();

		for (u_int i = 0; i < legs.size(); i++) horLine(legs[i].x, hyp[i].x, legs[i].y);
	}

	/*writes a rectangle just as the rectangle function and fill it*/
	void fillRect(int x, int y, int w, int h) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				point(x + j, y + i);
			}
		}
	}
	/*writes a circle just as the circle function, and fill it*/
	void fillCircle(int x, int y, int r) {
		int xc = 0, yc = r, d = 3 - (2 * r), yf = 0;
		auto octLine = [&](int yi) {
			for (; yi <= yc; yi++) {
				octant(xc, yi, x, y);
			}
		};

		octLine(yf++);
		while (yc >= xc) {
			xc++;
			if (d < 0) d = d + 4 * xc + 6;
			else d = d + 4 * (xc - --yc) + 10;
			octLine(yf++);
		}
	}

private:
	/* modifies an array, adding the points that wold make part of a line from and to the given points, uses the
	bresenham's line algorithm (without integer operations only optimization). if the critPoints flag is set only
	points with different y will be added (specifically the points previous to the y change)*/
	void lineBuffer(int x1, int y1, int x2, int y2, std::vector<vec2<int>>& out, bool critPoints = false) {
		int xFactor = x2 - x1;
		int yFactor = y2 - y1;
		float err = 0;
		int x = x1;
		int y = y1;
		if (xFactor != 0) {
			float dErr = abs((float)yFactor / (float)xFactor);
			if (dErr <= 1) {
				if (critPoints) out.reserve(out.size() + abs(yFactor) + 1);
				for (; ((xFactor > 0) ? x <= x2 : x >= x2); x += (xFactor > 0) ? 1 : -1) {
					if (!critPoints) point(x, y);
					err += dErr;
					if (err >= 0.5) {
						if (critPoints) out.emplace_back(vec2<int>(x, y));
						y += (yFactor > 0) ? 1 : -1;
						err -= 1.0f;
					}
				}
				if (critPoints) {
					if (out.size() < out.capacity()) {
						out.emplace_back(vec2<int>(x - 1, y));
					}
				}
			}
			else {
				dErr = 1 / dErr;
				if(critPoints) out.reserve(out.size() + abs(yFactor) + 1);
				for (; ((yFactor > 0) ? y <= y2 : y >= y2); y += (yFactor > 0) ? 1 : -1) {
					if (critPoints) out.emplace_back(vec2<int>(x, y));
					else point(x, y);
					err += dErr;
					if (err >= 0.5) {
						x += (xFactor > 0) ? 1 : -1;
						err -= 1.0f;
					}
				}
			}
		}
		else {
			if(critPoints) out.reserve(out.size() + abs(yFactor) + 1);
			if (y1 > y2) {
				y = y2;
				swap(y1, y2);
			}
			for (; y <= y2; y++) {
				if (critPoints) out.emplace_back(vec2<int>(x, y));
				else point(x, y);
			}
		}
	}

	/*writes points radially simmetrycally in each octant of a circle*/
	void octant(int xc, int yc, int x, int y) {
		point(xc + x, yc + y);
		point(-xc + x, yc + y);
		point(-xc + x, -yc + y);
		point(xc + x, -yc + y);
		point(yc + x, xc + y);
		point(-yc + x, xc + y);
		point(-yc + x, -xc + y);
		point(yc + x, -xc + y);
	}

};

class ConsoleEngine: public ConsoleGraphics {
	bool keyState[254] = { 0 };
protected:
	typedef enum : uint8_t {
		LMB = 0x01, RMB, CANCEL, MMB, X1MB, X2MB, BACK = 0x08, TAB, CLEAR = 0x0C, RETURN, SHIFT = 0x10, CTRL, ALT, PAUSE, CAPS_LOCK,
		KANA, IME_ON, JUNJA, FINAL, KANJI, IME_OFF, ESC, CONVERT, NONCONVERT, ACCEPT, MODECHANGE, SPACE, PAGE_UP, PAGE_DOWN, END,
		HOME, LEFT, UP, RIGHT, DOWN, SELECT, PRINT, EXECUTE, PRINT_SCREEN, INS, DEL, HELP, K0, K1, K2, K3, K4, K5, K6, K7, K8, K9,
		A = 0x41, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, LWIN, RWIN, APPS, SLEEP = 0x5F, NPAD0,
		NPAD1, NPAD2, NPAD3, NPAD4, NPAD5, NPAD6, NPAD7, NPAD8, NPAD9, MULT, ADD, SEPARATOR, SUB, DECIMAL, DIV, F1, F2, F3, F4, F5,
		F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24, NUM_LOCK = 0x090, SCROLL_LOCK,
		LSHIFT = 0xA0, RSHIFT, LCTRL, RCTRL, LALT, RALT, BROWSER_BACK, BROWSER_FORDWARD, BROWSER_REFRESH, BROWSER_STOP, BROWSER_SEARCH,
		BROWSER_FAV, BROWSER_HOME, VOL_MUTE, VOL_DOWN, VOL_UP, NEXT_TRACK, PREV_TRACK, MEDIA_STOP, MEDIA_PLAY, MAIL, MEDIA_SELECT,
		APP1, APP2, OEM1 = 0xBA, OEM_PLUS, OEM_COMMA, OEM_MINUS, OEM_PERIOD, OEM2, OEM3, OEM4 = 0xDB, OEM5, OEM6, OEM7, OEM8,
		OEM102 = 0xE2, PROCESS_KEY = 0xE5, PACKET = 0XE7, ATTN = 0XF6, CRSEL, EXSEL, ERASE_EOF, PLAY, ZOOM, NONAME, PA1, OEM_CLEAR
	} keyAccess;

public:
	ConsoleEngine() {}

protected:
	/* *pure virtual* It's executed once when the start function is called*/
	virtual void begin() = 0;

	/* *pure virtua* It's executed every frame after the start function is called*/
	virtual void update(float elapsedTime) = 0;

	/*returns true if the specified key has gone down since the last keyState [keyDown, keyUp, keyPressed] function call*/
	bool keyDown(keyAccess key) {
		short state = GetAsyncKeyState(key);
		if ((0x8000 & state) != 0) {
			if (!keyState[key]) {
				keyState[key] = true;
				return true;
			}
		}
		else {
			keyState[key] = false;
		}
		return false;
	}

	/*returns true if the specified key has gone up since the last keyState [keyDown, keyUp, keyPressed] function call*/
	bool keyUp(keyAccess key) {
		short state = GetAsyncKeyState(key);
		if ((0x8000 & state) == 0) {
			if (keyState[key]) {
				keyState[key] = false;
				return true;
			}
		}
		else {
			keyState[key] = true;
		}
		return false;
	}

	/*returns true if the specified key is pressed in the moment the function is called*/
	bool keyPressed(keyAccess key) {
		keyState[key] = (0x8000 & GetAsyncKeyState(key)) != 0;
		return keyState[key];
	}

public:
	/*starts the engine loop if the renderer is properly set*/
	bool start() {
		if (this->set()) {
			std::thread loop(&ConsoleEngine::engineLoop, this);
			loop.join();
		}
		return 0;
	}

private:
	void engineLoop() {
		auto ts1 = std::chrono::system_clock::now();
		begin();
		auto ts2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = ts2 -ts1;
		float fElapsedTime;

		while (true) {
			ts1 = std::chrono::system_clock::now();
			elapsedTime = ts1 - ts2;
			fElapsedTime = elapsedTime.count();
			ts2 = ts1;

			update(fElapsedTime);

			WriteConsoleOutput(hConsole, screenBuffer, bufferSize, { 0,0 }, &windowRect);
		}
	}
};