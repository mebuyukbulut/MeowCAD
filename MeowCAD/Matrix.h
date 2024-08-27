#pragma once

class Vector;

class Matrix{
	float n[3][3];
public:

	Matrix();
	Matrix(
		float n00, float n01, float n02,
		float n10, float n11, float n12,
		float n20, float n21, float n22);
	Matrix(
		const Vector& a,
		const Vector& b,
		const Vector& c);

	float& operator()(int i, int j);
	const float& operator()(int i, int j) const;
	Vector& operator[](int j);
	const Vector& operator[](int j) const;

	//cross
	friend Matrix operator *(const Matrix& A, const Matrix& B);
	friend Vector operator *(const Matrix& M, const Vector& v);


	friend Matrix operator +(const Matrix& A, const float& s);
	friend Matrix operator -(const Matrix& A, const float& s);
	friend Matrix operator *(const Matrix& A, const float& s);
	friend Matrix operator /(const Matrix& A, const float& s);
};

