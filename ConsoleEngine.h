#pragma once

#define _2D_ENGINE
#ifdef _3D_ENGINE
#undef _2D_ENGINE
#endif

#include <Windows.h>
#include <vector>
#include <thread>
#include <chrono>

void swap (int& n1, int& n2) { int t = n1; n1 = n2; n2 = t; };

/* simple vector2 struct */
template<typename T>
struct Vec2{
	T x;
	T y;

	Vec2() : x(0), y(0) {}
	Vec2(T x, T y) : x(x), y(y) {}
	Vec2(const Vec2& other) : x(other.x), y(other.y) {}

	static T dotProd(Vec2& a, Vec2& b) { return a.x * b.x + a.y * b.y; }
	static Vec2 normal(Vec2& in) {
		float l = sqrtf(in.x * in.x + in.y * in.y);
		return { in.x / l, in.y / l };
	}

	void normalize() {
		float l = sqrtf(x * x + y * y);
		x / l; y / l;
	}

	Vec2 operator + (const Vec2& o) { return { x + o.x, y + o.y }; }
	Vec2 operator - (const Vec2& o) { return { x - o.x, y - o.y }; }
	Vec2 operator * (const Vec2& o) { return { x * o.x, y * o.y }; }
	Vec2 operator * (const T s) { return { x * s, y * s }; }
	Vec2 operator += (const Vec2& o) { x += o.x; y += o.y; return *this; }
	Vec2 operator -= (const Vec2& o) { x -= o.x; y -= o.y; return *this; }
	Vec2 operator *= (const Vec2& o) { x *= o.x; y *= o.y; return *this; }
	Vec2 operator *= (const T& s) { x *= s; y *= s; return *this; }

};
typedef Vec2<int> Vec2i;
typedef Vec2<float> Vec2f;
typedef Vec2<double> Vec2d;

/* simple vector3 struct */
template<typename T>
struct Vec3 {
	T x, y, z;

	Vec3() : x(0), y(0), z(0) {}
	Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
	Vec3(const Vec3& other) : x(other.x), y(other.y), z (other.z) {}

	T vecMin() {
		if (x <= y && x <= z) return x;
		if (y <= x && y <= z) return y;
		if (z <= x && z <= y) return z;
	}
	T vecMax() {
		if (x >= y && x >= z) return x;
		if (y >= x && y >= z) return y;
		if (z >= x && z >= y) return z;
	}

	static T dotProd(Vec3& a, Vec3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
	static Vec3 cross(Vec3& a, Vec3& b) { return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x }; }
	static Vec3 normal(Vec3& in) {
		float l = sqrtf(in.x * in.x + in.y * in.y + in.z * in.z);
		return { in.x / l, in.y / l,in.z / l };
	}

	void normalize() {
		float l = sqrtf(x * x + y * y + z * z);
		x / l; y / l; z / l;
	}

	Vec3 operator + (const Vec3& o) { return { x + o.x, y + o.y, z + o.z }; }
	Vec3 operator - (const Vec3& o) { return { x - o.x, y - o.y, z - o.z }; }
	Vec3 operator * (const Vec3& o) { return { x * o.x, y * o.y, z * o.z }; }
	Vec3 operator * (const T s) { return { x * s, y * s, z * s }; }
	Vec3 operator += (const Vec3& o) { x += o.x; y += o.y; z += o.z; return *this; }
	Vec3 operator -= (const Vec3& o) { x -= o.x; y -= o.y; z -= o.z; return *this; }
	Vec3 operator *= (const Vec3& o) { x *= o.x; y *= o.y; z *= o.z; return *this; }
	Vec3 operator *= (const T& s) { x *= s; y *= s; z *= s; return *this; }

};
typedef Vec3<int> Vec3i;
typedef Vec3<float> Vec3f;
typedef Vec3<double> Vec3d;

/*simple vector4 struct*/
template<typename T>
struct Vec4 {
	T x, y, z, w;

	Vec4() : x(0), y(0), z(0), w((T)1) {}
	Vec4(T x, T y, T z) : x(x), y(y), z(z), w((T)1) {}
	Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
	Vec4(const Vec4& other) : x(other.x), y(other.y), z(other.z), w(other.w) {}

	/*the w component will be ignored in all vec to vec operations, it will only be used in vec to mat operations*/

	static T dotProd(Vec4& a, Vec4& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
	static Vec4 cross(Vec4& a, Vec4& b) { return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x }; }
	static Vec4 unit(Vec4& in) {
		float l = sqrtf(in.x * in.x + in.y * in.y + in.z * in.z);
		return { in.x / l, in.y / l,in.z / l };
	}

	void toUnit() {
		float l = sqrtf(x * x + y * y + z * z);
		x /= l; y /= l; z /= l;
	}

	Vec4 operator + (const Vec4& o) { return { x + o.x, y + o.y, z + o.z }; }
	Vec4 operator - (const Vec4& o) { return { x - o.x, y - o.y, z - o.z }; }
	Vec4 operator * (const Vec4& o) { return { x * o.x, y * o.y, z * o.z }; }
	Vec4 operator * (const T s) { return { x * s, y * s, z * s }; }
	Vec4 operator += (const Vec4& o) { x += o.x; y += o.y; z += o.z; return *this; }
	Vec4 operator -= (const Vec4& o) { x -= o.x; y -= o.y; z -= o.z; return *this; }
	Vec4 operator *= (const Vec4& o) { x *= o.x; y *= o.y; z *= o.z; return *this; }
	Vec4 operator *= (const T& s) { x *= s; y *= s; z *= s; return *this; }
};
typedef Vec4<int> Vec4i;
typedef Vec4<float> Vec4f;
typedef Vec4<double> Vec4d;

template<typename T>
struct Mat4 {
	T m[4][4] = { 0 };

	Mat4 operator * (const Mat4& a) {
		Mat4 c;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				c.m[i][j] = m[i][0] * a.m[0][j] + m[i][1] * a.m[1][j] + m[i][2] * a.m[2][j] + m[i][3] * a.m[3][j];
			}
		}
		return c;
	}
	T* operator [] (const int pos) { return m[pos]; }
	Vec4<T> operator * (const Vec4<T>& vec) {
		return{
			vec.x * m[0][0] + vec.y * m[1][0] + vec.z * m[2][0] + vec.w * m[3][0],
			vec.x * m[0][1] + vec.y * m[1][1] + vec.z * m[2][1] + vec.w * m[3][1],
			vec.x * m[0][2] + vec.y * m[1][2] + vec.z * m[2][2] + vec.w * m[3][2],
			vec.x * m[0][3] + vec.y * m[1][3] + vec.z * m[2][3] + vec.w * m[3][3]
		};
	}
	//Vec4<T> * operator (const Vec4<T>& vec) {
	//	return{
	//		vec.x * m[0][0] + vec.y * m[1][0] + vec.z * m[2][0] + vec.w * m[3][0],
	//		vec.x * m[0][1] + vec.y * m[1][1] + vec.z * m[2][1] + vec.w * m[3][1],
	//		vec.x * m[0][2] + vec.y * m[1][2] + vec.z * m[2][2] + vec.w * m[3][2],
	//		vec.x * m[0][3] + vec.y * m[1][3] + vec.z * m[2][3] + vec.w * m[3][3]
	//	};
	//}
};
typedef Mat4<int> Mat4i;
typedef Mat4<float> Mat4f;
typedef Mat4<double> Mat4d;

template<typename T>
Vec4<T> operator * (const Vec4<T>& vec, Mat4<T>& mat) {
	return{
		vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + vec.w * mat.m[3][0],
		vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + vec.w * mat.m[3][1],
		vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + vec.w * mat.m[3][2],
		vec.x * mat.m[0][3] + vec.y * mat.m[1][3] + vec.z * mat.m[2][3] + vec.w * mat.m[3][3]
	};
}


/* class encapsuling console drawing functionality */
class ConsoleGraphics {
	int _width;
	int _height;
	int fSizeW;
	int fSizeH;

	bool _set;

	short _color = 0xFF;

protected:
	wchar_t pixChar = 0x2592;

	CHAR_INFO* screenBuffer;

	HANDLE hConsole;
	COORD bufferSize;
	SMALL_RECT windowRect;
	
	typedef enum : uint8_t {
		BLACK, DARK_BLUE = 0x11, DARK_GREEN = 0x22, DARK_CYAN = 0x33,
		DARK_RED = 0x44, DARK_MAGENTA = 0x55, DARK_YELLOW = 0x66, LIGHT_GREY = 0x77,
		GREY = 0x88, BLUE = 0x99, GREEN = 0xAA, CYAN = 0xBB,
		RED = 0xCC, MAGENTA = 0xDD, YELLOW = 0xEE, WHITE = 0xFF
	} Color;

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
	//TODO: documentation
	bool setColor(Color c, uint8_t brightness = 6) {
		if (brightness > 6) return 0;
		switch (brightness)
		{
		case 0:
			_color = 0;
			break;
		case 1:
			_color = 0x0F & (c - 0x8);
			break;
		case 2:
			_color = 0xF0 & (c - 0x80);
			break;
		case 3:
			_color = c - 0x88;
			break;
		case 4:
			_color = c - 0x80;
			break;
		case 5:
			_color = c - 0x08;
			break;
		case 6:
			_color = c;
			break;
		}
		return 1;
	}

	bool blendColor(Color main, Color second, uint8_t blend = 0) {
		if (blend > 3) return 0;
		switch (blend)
		{
		case 0:
			_color = main;
			break;
		case 1:
			_color = (main & 0xF0) | (second & 0x0F);
			break;
		case 2:
			_color = (main & 0x0F) | (second & 0xF0);
			break;
		case 3:
			_color = second;
			break;
		}
		return 1;
	}

	bool greyScale(uint8_t brightness = 11) {
		if (brightness < 4) blendColor(BLACK, GREY, brightness);
		else if (brightness < 8) blendColor(GREY, LIGHT_GREY, brightness - 4);
		else if (brightness < 12) blendColor(LIGHT_GREY, WHITE, brightness - 8);
		else return 0;
		return 1;
	}

	bool brightColor(Color c, uint8_t brightness = 8) {
		if (brightness < 6) setColor(c, brightness);
		else if (brightness < 9) {
			blendColor(c, WHITE, brightness - 6);
		}
		else return 0;
		return 1;
	}

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
			screenBuffer[y * _width + x].Attributes = _color;
		}
	}
	void point(Vec2<int>& pos) {
		point(pos.x, pos.y);
	}

	/*writes a line that goes from and to the given points*/
	void line(int x1, int y1, int x2, int y2) {
		bool vert = false;

		if (abs(x2 - x1) < abs(y2 - y1)) {
			swap(x1, y1);
			swap(x2, y2);
			vert = true;
		}
		if (x2 < x1) {
			swap(x1, x2);
			swap(y1, y2);
		}

		int dx = x2 - x1;
		int dy = y2 - y1;
		int D = 2 * abs(dy) - abs(dx);
		int y = y1;

		for (int x = x1; x <= x2; x++) {
			if(vert) point(y, x);
			else point(x, y);

			if (D > 0) {
				y += (dy < 0)? -1: 1;
				D -= 2 * abs(dx);
			}
			D += 2 * abs(dy);
		}
	}
	void line(Vec2<int>& a, Vec2<int>& b) {
		line(a.x, a.y, b.x, b.y);
	}

	/*writes the triangle described by the given points*/
	void triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
		line(x1, y1, x2, y2);
		line(x2, y2, x3, y3);
		line(x3, y3, x1, y1);
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
	virtual void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
		Vec3i xComp(x1, x2, x3);
		Vec3i yComp(y1, y2, y3);

		Vec2i bbmin(xComp.vecMin(), yComp.vecMin());
		Vec2i bbmax(xComp.vecMax(), yComp.vecMax());

		Vec3f a(xComp.y - xComp.x, xComp.z - xComp.x, 0);
		Vec3f b(yComp.y - yComp.x, yComp.z - yComp.x, 0);

		Vec3f barycentric;

		for (int x = bbmin.x; x <= bbmax.x; x++) {
			for (int y = bbmin.y; y <= bbmax.y; y++) {
				a.z = xComp.x - x;
				b.z = yComp.x - y;
				Vec3f u = Vec3f::cross( a, b );

				if (abs(u.z) < 1) continue;
				barycentric = { 1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z };

				if (barycentric.x >= 0 && barycentric.y >= 0 && barycentric.z >= 0)
					point(x, y);
			}
		}
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


//still incomplete, use at own discrecion
class Console3DGraphics : public ConsoleGraphics {
	float* _zBuffer;

protected:

	Console3DGraphics() {}
	~Console3DGraphics() { delete[] _zBuffer; }

	bool construct3D() {
		_zBuffer = new float[width() * height()];
		for (int i = 0; i < width() * height(); i++) {
			_zBuffer[i] = 0;
		}
		return 1;
	}

	float get_zBuffer(int x, int y) {
		if (x < width() && x >= 0 && y < height() && y >= 0) {
			return _zBuffer[y * width() + x];
		}
	}
	void set_zBuffer(int x, int y, float n) {
		if (x < width() && x >= 0 && y < height() && y >= 0) {
			_zBuffer[y * width() + x] = n;
		}
	}

	void fillTriangle(Vec4f& p1, Vec4f& p2, Vec4f& p3) {
		float z;

		Vec3f xComp(p1.x, p2.x, p3.x);
		Vec3f yComp(p1.y, p2.y, p3.y);

		Vec2i bbmin(xComp.vecMin(), yComp.vecMin());
		Vec2i bbmax(xComp.vecMax(), yComp.vecMax());

		Vec3f a(xComp.y - xComp.x, xComp.z - xComp.x, 0);
		Vec3f b(yComp.y - yComp.x, yComp.z - yComp.x, 0);

		Vec3f barycentric;

		for (int x = bbmin.x; x <= bbmax.x; x++) {
			for (int y = bbmin.y; y <= bbmax.y; y++) {
				a.z = xComp.x - x;
				b.z = yComp.x - y;
				Vec3f u = Vec3f::cross(a, b);

				if (abs(u.z) < 1) continue;
				barycentric = { 1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z };

				if (barycentric.x >= 0 && barycentric.y >= 0 && barycentric.z >= 0) {
					z = 0;
					z += p1.z * barycentric.x;
					z += p2.z * barycentric.y;
					z += p3.z * barycentric.z;

					if(get_zBuffer(x, y) < z){
						set_zBuffer(x, y, z);
						point(x, y);
					}
				}
			}
		}
	}
};


//to use 3D options define _3D_ENGINE before including the header
#ifdef _2D_ENGINE
class ConsoleEngine: public ConsoleGraphics {
#endif
#ifdef _3D_ENGINE
class ConsoleEngine : public Console3DGraphics {
#endif
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
	 virtual bool start() {
		if (set()) {
#ifdef _3D_ENGINE
			construct3D();
#endif
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

			write();
		}
	}
};