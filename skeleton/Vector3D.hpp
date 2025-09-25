#pragma once

class Vector3D {
private:
	float x, y, z;
public:
	Vector3D();
	Vector3D(float x, float y, float z);
	Vector3D(const Vector3D& other);

	float getX() const { return x; }
	float getY() const { return y; }
	float getZ() const { return z; }

	Vector3D operator +(const Vector3D& u);
	Vector3D operator -(const Vector3D& u);
	Vector3D operator *(float scalar);

	float operator *(const Vector3D& other);
	void operator =(const Vector3D& other);

	static Vector3D crossProduct(const Vector3D& u, const Vector3D& v);
	Vector3D crossProduct(const Vector3D& other);

	static float dotProduct(const Vector3D& u, const Vector3D& v);
	float dotProduct(const Vector3D& other);

	float squareMagnitude();
	float magnitude();
	
	void normalize();
};