#pragma once
#include <algorithm>
#include <d3dx9.h>
#define PI    ((FLOAT)  3.141592654f)
struct vertex
{
	float x, y, z, rhw;
	uint32_t color;
};

class Color {
public:
	Color()
	{
		*((int*)this) = 0;
	}

	Color(int color32)
	{
		*((int*)this) = color32;
	}

	Color(int _r, int _g, int _b)
	{
		set(_r, _g, _b, 255);
	}

	Color(int _r, int _g, int _b, int _a)
	{
		set(_r, _g, _b, _a);
	}

	void set(int _r, int _g, int _b, int _a = 255)
	{
		_color[0] = (unsigned char)_r;
		_color[1] = (unsigned char)_g;
		_color[2] = (unsigned char)_b;
		_color[3] = (unsigned char)_a;
	}

	void get(int& _r, int& _g, int& _b, int& _a) const
	{
		_r = _color[0];
		_g = _color[1];
		_b = _color[2];
		_a = _color[3];
	}

	int get_raw() const
	{
		return *((int*)this);
	}

	unsigned char* get_ptr_r() {
		return &_color[0];
	}
	unsigned char* get_ptr_g() {
		return &_color[1];
	}
	unsigned char* get_ptr_b() {
		return &_color[2];
	}
	unsigned char* get_ptr_a() {
		return &_color[3];
	}


	inline int get_red() const
	{
		return _color[0];
	}
	inline int get_green() const
	{
		return _color[1];
	}
	inline int get_blue() const
	{
		return _color[2];
	}
	inline int get_alpha() const
	{
		return _color[3];
	}

	inline void set_red(int value) {
		_color[0] = value;
	}
	inline void set_green(int value) {
		_color[1] = value;
	}
	inline void set_blue(int value) {
		_color[2] = value;
	}
	inline void set_alpha(int value) {
		_color[3] = value;
	}
	unsigned char& operator[](int index)
	{
		return _color[index];
	}

	const unsigned char& operator[](int index) const
	{
		return _color[index];
	}

	bool operator ==(const Color& rhs) const
	{
		return rhs.get_red() == this->get_red()
			&& rhs.get_green() == this->get_green()
			&& rhs.get_blue() == this->get_blue()
			&& rhs.get_alpha() == this->get_alpha();
	}

	bool operator !=(const Color& rhs) const
	{
		return !(operator==(rhs));
	}

	Color& operator=(const Color& rhs)
	{
		Color clr = rhs;
		set_u32(clr.u32());
		return *this;
	}
	void set_u32(unsigned long color32)
	{
		*((unsigned long*)_color) = color32;
	}
	inline unsigned long u32()
	{
		return *((unsigned long*)_color);
	}
	inline unsigned long rn32()
	{
		return(Color(_color[2], _color[1], _color[0], _color[3]).u32());
	}
	double get_hue()
	{
		double r = _color[0] / 255.f;
		double g = _color[1] / 255.f;
		double b = _color[2] / 255.f;

		double mx = max(r, max(g, b));
		double mn = min(r, min(g, b));
		if (mx == mn)
			return 0.f;

		double delta = mx - mn;

		double hue = 0.f;
		if (mx == r)
			hue = (g - b) / delta;
		else if (mx == g)
			hue = 2.f + (b - r) / delta;
		else
			hue = 4.f + (r - g) / delta;

		hue *= 60.f;
		if (hue < 0.f)
			hue += 360.f;

		return hue / 360.f;
	}

	double get_saturation()
	{
		double r = _color[0] / 255.f;
		double g = _color[1] / 255.f;
		double b = _color[2] / 255.f;

		double mx = max(r, max(g, b));
		double mn = min(r, min(g, b));

		double delta = mx - mn;

		if (mx == 0.f)
			return delta;

		return delta / mx;
	}

	double get_brightness()
	{
		double r = _color[0] / 255.f;
		double g = _color[1] / 255.f;
		double b = _color[2] / 255.f;

		return max(r, max(g, b));
	}

	D3DCOLOR GetDColor() {
		return D3DCOLOR_RGBA(_color[0], _color[1], _color[2], _color[3]);
	}

	static Color hsb(float hue, float saturation, float brightness)
	{
		auto clamp = [](float value, float min, float max) {
			if (value > max) return max;
			else if (value < min) return min;
			return value;
		};
		hue = clamp(hue, 0.f, 1.f);
		saturation = clamp(saturation, 0.f, 1.f);
		brightness = clamp(brightness, 0.f, 1.f);

		float h = (hue == 1.f) ? 0.f : (hue * 6.f);
		float f = h - static_cast<int>(h);
		float p = brightness * (1.f - saturation);
		float q = brightness * (1.f - saturation * f);
		float t = brightness * (1.f - (saturation * (1.f - f)));

		if (h < 1.f)
			return Color((int)(brightness * 255), (int)(t * 255), (int)(p * 255));
		else if (h < 2.f)
			return Color((int)(q * 255), (int)(brightness * 255), (int)(p * 255));
		else if (h < 3.f)
			return Color((int)(p * 255), (int)(brightness * 255), (int)(t * 255));
		else if (h < 4)
			return Color((int)(p * 255), (int)(q * 255), (int)(brightness * 255));
		else if (h < 5)
			return Color((int)(t * 255), (int)(p * 255), (int)(brightness * 255));
		else
			return Color((int)(brightness * 255), (int)(p * 255), (int)(q * 255));
	}
	Color manage_alpha(int alpha) {
		return Color((*this)[0], (*this)[1], (*this)[2], alpha);
	}
	static Color increase(Color clr, int value, bool consider_alpha = false) {
		return Color(clr.get_red() + value, clr.get_green() + value, clr.get_blue() + value, clr.get_alpha() + consider_alpha * value);
	}
private:
	unsigned char _color[4];
};








class Vector {
public:
	float x, y, z;
	Vector(void);

	Vector(float X, float Y, float Z);
	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	float operator[](int i) const;
	float& operator[](int i);
	inline void Zero();
	Vector& Clamp();
	Vector& NormalizeAngles();
	Vector Cross(const Vector& vOther);
	float NormalizeMovement() const;
	inline float LengthSqr() {
		return (x * x + y * y + z * z);
	}
	inline float Length() {
		return sqrtf(LengthSqr());
	}
	__inline bool IsValid() const
	{
		return isfinite(x) && isfinite(y) && isfinite(z);
	}
	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;
	__forceinline Vector& operator+=(const Vector& v);
	__forceinline Vector& operator-=(const Vector& v);
	__forceinline Vector& operator*=(const Vector& v);
	__forceinline Vector& operator*=(float s);
	__forceinline Vector& operator/=(const Vector& v);
	__forceinline Vector& operator/=(float s);
	__forceinline Vector& operator+=(float fl);
	__forceinline Vector& operator-=(float fl);
	Vector& operator=(const Vector& vOther);
	Vector	operator-(const Vector& v) const;
	Vector	operator+(const Vector& v) const;
	Vector	operator*(const Vector& v) const;
	Vector	operator/(const Vector& v) const;
	Vector	operator*(float fl) const;
	Vector	operator/(float fl) const;
	inline Vector operator+(float fl) const;
	inline Vector operator-(float fl) const;
	inline Vector GetNormalized(void);
	//inline void Normalize(void);
	inline Vector Normalize(void);
	inline bool IsZero(float tolerance = 0.01f);

	__forceinline float DistTo(const Vector& vOther) const;

	float Dot(const Vector& vOther) const;
	float Dot(const float* fOther) const;
	float Length2D(void) const;
	float NormalizeInPlace();
	inline Vector Normalized() const;
	auto MultAdd(const Vector& vOther, float fl) {
		x += fl * vOther.x;
		y += fl * vOther.y;
		z += fl * vOther.z;
	}

	Vector normalized() const
	{
		Vector res = *this;
		float l = res.Length();
		if (l != 0.0f) {
			res /= l;
		}
		else {
			res.x = res.y = res.z = 0.0f;
		}
		return res;
	}

};
class Vector2D
{
public:
	float x, y;

	Vector2D() { x = 0; y = 0; };
	Vector2D(float X, float Y) { x = X; y = Y; };
	Vector2D(Vector vec) { x = vec.x; y = vec.y; }

	inline Vector2D operator*(const float n) const { return Vector2D(x * n, y * n); }
	inline Vector2D operator+(const Vector2D& v) const { return Vector2D(x + v.x, y + v.y); }
	inline Vector2D operator-(const Vector2D& v) const { return Vector2D(x - v.x, y - v.y); }
	inline void operator+=(const Vector2D& v)
	{
		x += v.x;
		y += v.y;
	}
	inline void operator-=(const Vector2D& v)
	{
		x -= v.x;
		y -= v.y;
	}

	bool operator==(const Vector2D& v) const { return (v.x == x && v.y == y); }
	bool operator!=(const Vector2D& v) const { return (v.x != x || v.y != y); }

	inline float Length()
	{
		return sqrt((x * x) + (y * y));
	}
};

