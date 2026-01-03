#include "CMath.h"


inline float isqrt(float _Xx)
{
	return (sqrtf(_Xx));
}
inline float VectorLength(const Vector& v)
{
	return (float)isqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

float Vector::DistTo(const Vector& vOther) const
{
	Vector delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.Length();
}

inline Vector& Vector::Clamp() {

	return *this;
}
inline Vector Vector::Normalized() const
{
	Vector res = *this;

	return res;
}
inline Vector Vector::operator-(float fl) const
{
	return Vector(x - fl, y - fl, z - fl);
}
inline Vector Vector::operator+(float fl) const
{
	return Vector(x + fl, y + fl, z + fl);
}
inline void VectorCrossProduct(const Vector& a, const Vector& b, Vector& result)
{
	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
}
inline float Vector::NormalizeMovement() const
{
	Vector res = *this;
	float l = res.Length();
	if (l != 0.0f)
	{
		res /= l;
	}
	else
	{
		res.x = res.y = res.z = 0.0f;
	}
	return l;
}
inline Vector Vector::Cross(const Vector& vOther)
{
	Vector res;
	VectorCrossProduct(*this, vOther, res);
	return res;
}
inline Vector& Vector::NormalizeAngles()
{
	return *this;
}

inline void Vector::Init(float ix, float iy, float iz) {
	x = ix; y = iy; z = iz;
}

inline Vector::Vector(float X, float Y, float Z) {
	x = X; y = Y; z = Z;
}

inline bool Vector::IsZero(float tolerance /*= 0.01f */)
{
	return (this->x > -tolerance && this->x < tolerance&&
		this->y > -tolerance && this->y < tolerance&&
		this->z > -tolerance && this->z < tolerance);
}

inline Vector::Vector(void) {}

inline void Vector::Zero() {
	x = y = z = 0.0f;
}

inline void VectorClear(Vector& a) {
	a.x = a.y = a.z = 0.0f;
}

inline Vector& Vector::operator=(const Vector& vOther) {
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}

inline float& Vector::operator[](int i) {
	return ((float*)this)[i];
}

inline float Vector::operator[](int i) const {
	return ((float*)this)[i];
}

inline bool Vector::operator==(const Vector& src) const {
	return (src.x == x) && (src.y == y) && (src.z == z);
}

inline bool Vector::operator!=(const Vector& src) const {
	return (src.x != x) || (src.y != y) || (src.z != z);
}

__forceinline  Vector& Vector::operator+=(const Vector& v) {
	x += v.x; y += v.y; z += v.z;
	return *this;
}

__forceinline  Vector& Vector::operator-=(const Vector& v) {
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}

__forceinline  Vector& Vector::operator*=(float fl) {
	x *= fl;
	y *= fl;
	z *= fl;
	return *this;
}

__forceinline  Vector& Vector::operator*=(const Vector& v) {
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

__forceinline Vector& Vector::operator+=(float fl) {
	x += fl;
	y += fl;
	z += fl;
	return *this;
}

__forceinline Vector& Vector::operator-=(float fl) {
	x -= fl;
	y -= fl;
	z -= fl;
	return *this;
}

__forceinline  Vector& Vector::operator/=(float fl) {
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;
	return *this;
}

__forceinline  Vector& Vector::operator/=(const Vector& v) {
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

inline Vector Vector::operator+(const Vector& v) const {
	Vector res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}


inline Vector Vector::operator-(const Vector& v) const {
	Vector res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}

inline Vector Vector::operator*(float fl) const {
	Vector res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}

inline Vector Vector::operator*(const Vector& v) const {
	Vector res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}

inline Vector Vector::operator/(float fl) const {
	Vector res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}

inline Vector Vector::operator/(const Vector& v) const {
	Vector res;
	res.x = x / v.x;
	res.y = y / v.y;
	res.z = z / v.z;
	return res;
}

inline Vector Vector::GetNormalized(void) {
	float length = this->Length();

	if (length != 0)
		return Vector(*this / this->Length());

	return Vector(0, 0, 1);
}
//inline void Vector::Normalize(void)
Vector Vector::Normalize()
{
	while (this->y > 180)
	{
		this->y -= 360;
	}
	while (this->y < -180)
	{
		this->y += 360;
	}

	while (this->x > 89)
	{
		this->x -= 180;
	}

	while (this->x < -89)
	{
		this->x += 180;
	}
	return *this;
}

inline float Vector::Dot(const Vector& vOther) const
{
	const Vector& a = *this;

	return(a.x * vOther.x + a.y * vOther.y + a.z * vOther.z);
}
inline float Vector::Dot(const float* fOther) const
{
	const Vector& a = *this;

	return(a.x * fOther[0] + a.y * fOther[1] + a.z * fOther[2]);
}
inline float Vector::Length2D(void) const
{
	float root = 0.0f;

	float sqst = x * x + y * y;

	__asm
	{
		sqrtss xmm0, sqst
		movss root, xmm0
	}

	return root;
}
inline float Vector::NormalizeInPlace()
{
	Vector& v = *this;

	float iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON

	v.x *= iradius;
	v.y *= iradius;
	v.z *= iradius;

	return 1;
}