#include "Vector.h"
#include <math.h>   


Vector operator+(const Vector& lhs, const Vector rhs){
	return Vector(
		lhs.x + rhs.x, 
		lhs.y + rhs.y, 
		lhs.z + rhs.z);
}
Vector operator-(const Vector& lhs, const Vector rhs){
	return Vector(
		lhs.x - rhs.x,
		lhs.y - rhs.y,
		lhs.z - rhs.z);
}
Vector operator*(const Vector& lhs, const float rhs){
	return Vector(
		lhs.x * rhs,
		lhs.y * rhs,
		lhs.z * rhs);
}
Vector operator*(const float& lhs, const Vector rhs){
	return rhs * lhs;
}

Vector operator/(const Vector& lhs, const float rhs){
	return lhs * (1.f/rhs);
}

Vector operator-(const Vector& v){
	return Vector(-v.x, -v.y, -v.z);
}

Vector::Vector() :x{}, y{}, z{} {}
Vector::Vector(float x, float y, float z) :x{ x }, y{ y }, z{ z } {}

Vector::Vector(const Vector& v) :x{ v.x }, y{ v.y }, z{ v.z } {}


float& Vector::operator[](int i) {
	return (&x)[i];
}
const float& Vector::operator[](int i) const {
	return (&x)[i];
}

Vector& Vector::operator+=(float s){
	x += s;
	y += s;
	z += s;
	return *this;
}
Vector& Vector::operator-=(float s){
	x -= s;
	y -= s;
	z -= s;
	return *this;
}
Vector& Vector::operator*=(float s){
	x *= s;
	y *= s;
	z *= s;
	return *this;
}
Vector& Vector::operator/=(float s){
	s = 1.f / s;
	x *= s;
	y *= s;
	z *= s;
	return *this;
}

Vector& Vector::operator+=(const Vector& v){
	x += v.x;
	y += v.y;
	z += v.z;
}
Vector& Vector::operator-=(const Vector& v){
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

float Vector::magnitude() const {
	return sqrt(x*x + y*y + z*z);
}

Vector Vector::normalize(const Vector& v){
	return v / v.magnitude();
}

