#pragma once
struct Vector{
	float x, y, z;

	Vector();
	Vector(float, float, float);
	Vector(const Vector&);
	//copy const
	//copy assignment
	//move const
	//move assignment


	float& operator[](int i);
	const float& operator[](int i) const;

	Vector& operator+= (float s);
	Vector& operator-= (float s);
	Vector& operator*= (float s);
	Vector& operator/= (float s);

	Vector& operator+= (const Vector& v);
	Vector& operator-= (const Vector& v);


	friend Vector operator+(const Vector& lhs, const Vector rhs);
	friend Vector operator-(const Vector& lhs, const Vector rhs);

	friend Vector operator*(const Vector& lhs, const float rhs);
	friend Vector operator*(const float& lhs, const Vector rhs);
	friend Vector operator/(const Vector& lhs, const float rhs);

	friend Vector operator-(const Vector& v);


	float magnitude() const;
	Vector normalize(const Vector& v);

};

