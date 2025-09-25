#include "Vector3D.hpp"

#include <cmath>

Vector3D::Vector3D() : x(0.0), y(0.0), z(0.0)
{
}

Vector3D::Vector3D(float x, float y, float z) : x(x), y(y), z(z) 
{
}

Vector3D::Vector3D(const Vector3D& other) : x(other.x), y(other.y), z(other.z)
{
}

Vector3D 
Vector3D::operator +(const Vector3D& other) {
	return Vector3D(this->x + other.x, this->y + other.y, this->z + other.z);
}

Vector3D 
Vector3D::operator -(const Vector3D& other) {
	return Vector3D(this->x - other.x, this->y - other.y, this->z - other.z);
}

Vector3D
Vector3D::operator *(float scalar) {
	return Vector3D(this->x * scalar, this->y * scalar, this->z * scalar);
}

void
Vector3D::operator=(const Vector3D& other) {
	x = other.x;
	y = other.y;
	z = other.z;
}


Vector3D 
Vector3D::crossProduct(const Vector3D& u, const Vector3D& v) {
	return Vector3D(u.y * v.z - u.z * v.y, u.z * v.x - u.x * v.z, u.x * v.y - u.y * v.x);
}

Vector3D 
Vector3D::crossProduct(const Vector3D& other) {
	return Vector3D::crossProduct(*this, other);
}

float 
Vector3D::dotProduct(const Vector3D& u, const Vector3D& v) {
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

float 
Vector3D::dotProduct(const Vector3D& other) {
	return Vector3D::dotProduct(*this, other);
}

float 
Vector3D::operator*(const Vector3D& other) {
	return Vector3D::dotProduct(*this, other);
}

float
Vector3D::squareMagnitude() {
	return (std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2));
}

float 
Vector3D::magnitude() {
	return std::sqrt(squareMagnitude());
}

void 
Vector3D::normalize() {
	x = x / magnitude();
	y = y / magnitude();
	z = z / magnitude();
}