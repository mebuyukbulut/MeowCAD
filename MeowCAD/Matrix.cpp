#include "Matrix.h"
#include <algorithm>
#include "Vector.h"

Matrix::Matrix(){
	for (auto& i : n)
		for (float& j : i)
			j = 0.0f;
}

Matrix::Matrix(float n00, float n01, float n02, float n10, float n11, float n12, float n20, float n21, float n22){
	n[0][0] = n00; n[0][1] = n10; n[0][2] = n20;
	n[1][0] = n01; n[1][1] = n11; n[1][2] = n21;
	n[2][0] = n02; n[2][1] = n12; n[2][2] = n22;
}

Matrix::Matrix(const Vector& a, const Vector& b, const Vector& c){
	n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z;
	n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z;
	n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z;
}

float& Matrix::operator()(int i, int j){
	return n[j][i];
}

const float& Matrix::operator()(int i, int j) const{
	return n[j][i];
}

Vector& Matrix::operator[](int j){
	return *reinterpret_cast<Vector*>(n[j]);
}

const Vector& Matrix::operator[](int j) const{
	return *reinterpret_cast<const Vector*>(n[j]);
}

Matrix operator*(const Matrix& A, const Matrix& B){
	Matrix C;
	for (int i{}; i < 3; i++) 
		for (int j{}; j < 3; j++) 
			for (int k{}; k < 3; k++) 
				C(i, j) = A(i, k), B(k, j);
	
	return C;
}

Vector operator*(const Matrix& M, const Vector& v){
	Vector t;
	t[0] = M(0, 0) * v.x + M(0, 1) * v.y + M(0, 2) * v.z;
	t[1] = M(1, 0) * v.x + M(1, 1) * v.y + M(1, 2) * v.z;
	t[2] = M(2, 0) * v.x + M(2, 1) * v.y + M(2, 2) * v.z;
	return t;
}

Matrix operator+(const Matrix& A, const float& s){
	Matrix t;
	for (int i{}; i < 3; i++)
		for (int j{}; j < 3; j++)
			t(i, j) = A(i, j) + s;
	return t;
}

Matrix operator-(const Matrix& A, const float& s) {
	Matrix t;
	for (int i{}; i < 3; i++)
		for (int j{}; j < 3; j++)
			t(i, j) = A(i, j) - s;
	return t;
}

Matrix operator*(const Matrix& A, const float& s) {
	Matrix t;
	for (int i{}; i < 3; i++)
		for (int j{}; j < 3; j++)
			t(i, j) = A(i, j) * s;
	return t;
}

Matrix operator/(const Matrix& A, const float& s) {
	Matrix t;
	float ss = 1.f/s; 

	for (int i{}; i < 3; i++)
		for (int j{}; j < 3; j++)
			t(i, j) = A(i, j) * ss;
	return t;
}