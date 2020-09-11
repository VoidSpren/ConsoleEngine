#pragma once

#define _2D_ENGINE
#ifdef _3D_ENGINE
#undef _2D_ENGINE
#endif

#define F_PI 3.1415927f
#define D_PI 3.141592653589793

#include <Windows.h>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
#include <string>
#include <strstream>

void swap (int& n1, int& n2) { int t = n1; n1 = n2; n2 = t; };

/* simple vector2 struct */
template<typename T>
struct Vec2{
	T x;
	T y;

	Vec2() : x(0), y(0) {}
	Vec2(T x, T y) : x(x), y(y) {}
	Vec2(const Vec2& other) : x(other.x), y(other.y) {}

	static T dotProd(const Vec2& a, const Vec2& b) { return a.x * b.x + a.y * b.y; }
	static Vec2 unit(const Vec2& in) {
		float l = sqrtf(in.x * in.x + in.y * in.y);
		return { in.x / l, in.y / l };
	}

	void toUnit() {
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

	static T dotProd(const Vec3& a, const Vec3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
	static Vec3 cross(const Vec3& a, const Vec3& b) { return {a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x }; }
	static Vec3 unit(const Vec3& in) {
		float l = sqrtf(in.x * in.x + in.y * in.y + in.z * in.z);
		return { in.x / l, in.y / l,in.z / l };
	}

	void toUnit() {
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

	static T dotProd(const Vec4& a, const Vec4& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
	static Vec4 cross(const Vec4& a, const Vec4& b) { return { a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x }; }
	static Vec4 unit(const Vec4& in) {
		float l = sqrtf(in.x * in.x + in.y * in.y + in.z * in.z);
		if (l == 0) return { 0,0,0 };
		return { in.x / l, in.y / l,in.z / l };
	}

	void toUnit() {
		float l = sqrtf(x * x + y * y + z * z);
		if (l != 0) {
			x /= l; y /= l; z /= l;
		}
		else {
			x = 0; y = 0; z = 0;
		}
	}

	Vec4 operator + (const Vec4& o) { return { x + o.x, y + o.y, z + o.z }; }
	Vec4 operator - (const Vec4& o) { return { x - o.x, y - o.y, z - o.z }; }
	Vec4 operator * (const Vec4& o) { return { x * o.x, y * o.y, z * o.z }; }
	Vec4 operator * (const T s) { return { x * s, y * s, z * s }; }
	Vec4 operator / (const T s) { return { x / s, y / s, z / s }; }
	Vec4 operator += (const Vec4& o) { x += o.x; y += o.y; z += o.z; return *this; }
	Vec4 operator -= (const Vec4& o) { x -= o.x; y -= o.y; z -= o.z; return *this; }
	Vec4 operator *= (const Vec4& o) { x *= o.x; y *= o.y; z *= o.z; return *this; }
	Vec4 operator *= (const T s) { x *= s; y *= s; z *= s; return *this; }
};
typedef Vec4<int> Vec4i;
typedef Vec4<float> Vec4f;
typedef Vec4<double> Vec4d;

/*square mat4 struct*/
template<typename T>
struct Mat4 {
	T m[4][4] = { 0 };

	void identity() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				m[i][j] = 0;
			}
		}
		m[0][0] = (T)1;
		m[1][1] = (T)1;
		m[2][2] = (T)1;
		m[3][3] = (T)1;
	}

	Mat4 operator * (const Mat4& a) {
		Mat4 c;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				c.m[i][j] = m[i][0] * a.m[0][j] + m[i][1] * a.m[1][j] + m[i][2] * a.m[2][j] + m[i][3] * a.m[3][j];
			}
		}
		return c;
	}
	T* operator [] (const size_t pos) { return m[pos]; }
	Vec4<T> operator * (const Vec4<T>& vec) {
		return{
			vec.x * m[0][0] + vec.y * m[1][0] + vec.z * m[2][0] + vec.w * m[3][0],
			vec.x * m[0][1] + vec.y * m[1][1] + vec.z * m[2][1] + vec.w * m[3][1],
			vec.x * m[0][2] + vec.y * m[1][2] + vec.z * m[2][2] + vec.w * m[3][2],
			vec.x * m[0][3] + vec.y * m[1][3] + vec.z * m[2][3] + vec.w * m[3][3]
		};
	}
};
typedef Mat4<int> Mat4i;
typedef Mat4<float> Mat4f;
typedef Mat4<double> Mat4d;

template<typename T>
Vec4<T> operator * (const Vec4<T>& vec, const Mat4<T>& mat) {
	return{
		vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + vec.w * mat.m[3][0],
		vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + vec.w * mat.m[3][1],
		vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + vec.w * mat.m[3][2],
		vec.x * mat.m[0][3] + vec.y * mat.m[1][3] + vec.z * mat.m[2][3] + vec.w * mat.m[3][3]
	};
}

/*3D triangle struct*/
struct Tri {
	Vec4f vert[3];
private:
	Vec4f _normal;
public:

	Tri() {
		vert[0] = { 0,0,0 }; vert[1] = { 0,0,0 }; vert[2] = { 0,0,0 };
		_normal = { 0,0,0 };
	}
	Tri(const Vec4f& v1, const Vec4f& v2, const Vec4f& v3) {
		vert[0] = v1; vert[1] = v2; vert[2] = v3;

		Vec4f l2 = vert[2] - vert[0];
		Vec4f l1 = vert[1] - vert[0];
		_normal = Vec4f::cross(l1, l2);
		_normal.toUnit();
	}

	Vec4f& normal() {
		if (_normal.x == 0 && _normal.y == 0 && _normal.z == 0) {
			Vec4f l2 = vert[2] - vert[0];
			Vec4f l1 = vert[1] - vert[0];
			_normal = Vec4f::cross(l1, l2);
			_normal.toUnit();
		}
		return _normal;
	}
	
	Vec4f& calcNormal() {
		Vec4f l2 = vert[2] - vert[0];
		Vec4f l1 = vert[1] - vert[0];
		_normal = Vec4f::cross(l1, l2);
		_normal.toUnit();
		return _normal;
	}
};

/*3D mesh of triangles*/
struct Mesh {
	Vec4f pos;
	Vec4f rotation;
	float scale;

private:
	std::vector<Tri> _tris;

public:
	Mesh() {}
	Mesh(const Vec4f& pos, const Vec4f& rotation, float scale) : pos(pos), rotation(rotation), scale(scale) {}
	Mesh(const Vec4f& pos, const Vec4f& rotation, float scale, const std::string& filePath) : pos(pos), rotation(rotation), scale(scale) {
		loadFromFile(filePath);
	}

	std::vector<Tri>& tris() {
		return _tris;
	}

	bool loadFromFile(const std::string& filePath) {
		std::ifstream file(filePath);
		if (!file.is_open()) return 0;

		std::string line;
		std::vector<Vec4f> verts;
		while (getline(file, line)) {
			std::strstream s;
			s << line;

			char junk;
			if (line[0] == 'v') {
				Vec4f v;
				s >> junk >> v.x >> v.z >> v.y;
				verts.push_back(v);
			}
			if (line[0] == 'f') {
				int f[3];
				s >> junk >> f[0] >> f[1] >> f[2];
				_tris.push_back({ verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] });
			}
		}
		return 1;
	}
};


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

	/*set the color with pure color being max brigthness*/
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

	/*blends color from the first to the second*/
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

	/*greyScale, max brightness is 11*/
	bool greyScale(uint8_t brightness = 11) {
		if (brightness < 4) blendColor(BLACK, GREY, brightness);
		else if (brightness < 8) blendColor(GREY, LIGHT_GREY, brightness - 4);
		else if (brightness < 12) blendColor(LIGHT_GREY, WHITE, brightness - 8);
		else return 0;
		return 1;
	}

	/*set the color with almost white color being max brigthness*/
	bool brightColor(Color c, uint8_t brightness = 8) {
		if (brightness < 6) setColor(c, brightness);
		else if (brightness < 9) {
			blendColor(c, WHITE, brightness - 6);
		}
		else return 0;
		return 1;
	}

	/*writes a pixel at the given location to the screenBuffer*/
	void point(int x, int y) {
		if (x < _width && x >= 0 && y < _height && y >= 0) {
			screenBuffer[y * _width + x].Char.UnicodeChar = pixChar;
			screenBuffer[y * _width + x].Attributes = _color;
		}
	}
	void point(Vec2i& pos) {
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
	void line(const Vec2i& a, const Vec2i& b) {
		line(a.x, a.y, b.x, b.y);
	}

	/*writes the triangle described by the given points*/
	void triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
		line(x1, y1, x2, y2);
		line(x2, y2, x3, y3);
		line(x3, y3, x1, y1);
	}
	void triangle(const Vec2i& p1, const Vec2i& p2, const Vec2i& p3) {
		triangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
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
	void rect(const Vec2i& pos, const Vec2i& size) {
		rect(pos.x, pos.y, size.x, size.y);
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
	void circle(const Vec2i& pos, int r) {
		circle(pos.x, pos.y, r);
	}

	/*writes a triangle just as the triangle function, and fill it*/
	void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3) {
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
	void fillTriangle(const Vec2i& p1, const Vec2i& p2, const Vec2i& p3) {
		fillTriangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
	}

	/*writes a rectangle just as the rectangle function and fill it*/
	void fillRect(int x, int y, int w, int h) {
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				point(x + j, y + i);
			}
		}
	}
	void fillRect(const Vec2i& pos, const Vec2i& size) {
		fillRect(pos.x, pos.y, size.x, size.y);
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
	void fillCircle(const Vec2i& pos, int r) {
		fillCircle(pos.x, pos.y, r);
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
	float fovTan;
	bool _set_3D = false;

	Vec4f camera = { 0,0,0 };

	Mat4f xRot;
	Mat4f zRot;
	Mat4f yRot;
	Mat4f rotMat;

protected:
	typedef enum : uint8_t { NO_ROT, X_ROT, Y_ROT, Z_ROT } rot;

public:
	/*start and setup 3D environment so that 3D rendering is possible*/
	bool construct3D(float fov) {
		if (!set()) return 0;
		if (fov >= F_PI || fov == 0) return 0;

		fovTan = 1.f / tanf(fov / 2.f);
		xRot.identity();
		yRot.identity();
		zRot.identity();

		_zBuffer = new float[width() * height()];
		clear3D();
		_set_3D = true;
		return 1;
	}

protected:
	Console3DGraphics() {}
	~Console3DGraphics() { delete[] _zBuffer; }

	bool set_3D() { return _set_3D; }

	/*clears the ZBuffer*/
	void clear3D() {
		for (int i = 0; i < width() * height(); i++) {
			_zBuffer[i] = FLT_MAX;
		}
	}

	/*writes a filled triangle in 3D space*/
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

				barycentric = { 1.f - (u.x + u.y) / u.z, u.y / u.z, u.x / u.z };

				if (barycentric.x >= 0 && barycentric.y >= 0 && barycentric.z >= 0) {
					z = 0;
					z += p1.z * barycentric.x;
					z += p3.z * barycentric.y;
					z += p2.z * barycentric.z;

					if(zBuffer(x, y) > z){
						zBuffer(x, y, z);
						point(x, y);
					}
				}
			}
		}
	}

	/*renders the given mesh, no textures and simple shading*/
	void renderMesh(Mesh& mesh, rot rot1 = NO_ROT, rot rot2 = NO_ROT, rot rot3 = NO_ROT) {
		rotMat.identity();

		if (rot1 != NO_ROT || rot2 != NO_ROT || rot3 != NO_ROT) {
			create_RotXMat(mesh.rotation.x, xRot);
			create_RotYMat(mesh.rotation.y, yRot);
			create_RotZMat(mesh.rotation.z, zRot);
			rotMult(rot1);
			rotMult(rot2);
			rotMult(rot3);
		}

		for (auto tri : mesh.tris()) {
			triRotate(tri, rotMat);
			triScale(tri, mesh.scale);
			triTranslate(tri, mesh.pos);

			Vec4f camToTri = tri.vert[0] - camera;
			camToTri.toUnit();
			float dProd = Vec4f::dotProd(tri.normal(), camToTri);
			if(dProd > 0){
				triProj(tri);

				float a = (float)width() / 2.f;
				for (int i = 0; i < 3; i++) {
					tri.vert[i].x *= a; tri.vert[i].y *= a;
					tri.vert[i].x += width() / 2.f; tri.vert[i].y += height() / 2.f;
				}
				
				greyScale(dProd * 12);
				fillTriangle(tri.vert[0], tri.vert[1], tri.vert[2]);
			}
		}
	}

private:
	float zBuffer(int x, int y) {
		if (x < width() && x >= 0 && y < height() && y >= 0) {
			return _zBuffer[y * width() + x];
		}
		return 0;
	}

	float zBuffer(int x, int y, float z) {
		if (x < width() && x >= 0 && y < height() && y >= 0) {
			_zBuffer[y * width() + x] = z;
		}
		return 0;
	}

	/*makes the given matrix into a rotation matrix for the X axis*/
	void create_RotXMat(float theta, Mat4f& mat) {
		mat.identity();
		mat[0][0] = 1.0f;
		mat[1][1] = cosf(theta);
		mat[1][2] = sinf(theta);
		mat[2][1] = -sinf(theta);
		mat[2][2] = cosf(theta);
		mat[3][3] = 1.0f;
	}
	/*makes the given matrix into a rotation matrix for the Y axis*/
	void create_RotYMat(float theta, Mat4f& mat) {
		mat.identity();
		mat[0][0] = cosf(theta);
		mat[0][2] = -sinf(theta);
		mat[1][1] = 1.0f;
		mat[2][0] = sinf(theta);
		mat[2][2] = cosf(theta);
		mat[3][3] = 1.0f;
	}
	/*makes the given matrix into a rotation matrix for the Z axis*/	
	void create_RotZMat(float theta, Mat4f& mat) {
		mat.identity();
		mat[0][0] = cosf(theta);
		mat[0][1] = sinf(theta);
		mat[1][0] = -sinf(theta);
		mat[1][1] = cosf(theta);
		mat[2][2] = 1.0f;
		mat[3][3] = 1.0f;
	}
	/*multiplies the specified rotation matrix axis, to the full rotation matrix*/
	void rotMult(rot arg) {
		if (arg == X_ROT) rotMat = rotMat * xRot;
		else if (arg == Y_ROT) rotMat = rotMat * yRot;
		else if (arg == Z_ROT) rotMat = rotMat * zRot;
	}

	/*apllies the given rotation matrix to the vertices of the given triangle*/
	void triRotate(Tri& tri, Mat4f& mat) {
		for (int i = 0; i < 3; i++) {
			tri.vert[i] = tri.vert[i] * mat;
		}
		tri.normal() = tri.normal() * mat;
	}
	/*adds the given position to the vertices of the given triangle*/
	void triTranslate(Tri& tri, Vec4f& pos) {
		for (int i = 0; i < 3; i++) {
			tri.vert[i] += pos;
		}
	}
	/*multiplies the vertices of the given triangle by the given scalar*/
	void triScale(Tri& tri, float scale) {
		for (int i = 0; i < 3; i++) {
			tri.vert[i] *= scale;
		}
	}
	/*projects the given triangle into 2D space*/
	void triProj(Tri& tri) {
		for (int i = 0; i < 3; i++) {
			tri.vert[i].x *= fovTan;
			tri.vert[i].y *= fovTan;
			if (tri.vert[i].z > 0) {
				tri.vert[i].x /= tri.vert[i].z;
				tri.vert[i].y /= tri.vert[i].z;
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
	 bool start() {
		if (set()) {
#ifdef _3D_ENGINE
			if (!set_3D()) return 0;
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

			//TODO: find better way to do this
#ifdef _3D_ENGINE
			clear3D();
#endif // _3D_ENGINE

			update(fElapsedTime);

			write();
		}
	}
};
