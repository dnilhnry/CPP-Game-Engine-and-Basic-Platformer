// Chris Rook. Northumbria University
// 24/04/2012	Added magnitudeSquared.
// Modified 04/11/2018
// Changed rotatedBy to use angles clockwise
// Modified 06/09/2019
//	Added type double use of *, / , *= and /=
//   Also int for division

#ifndef VECTOR_H
#define VECTOR_H

class Vector2D
{
public:
	float XValue;
	float YValue;

	Vector2D();

	Vector2D(float x, float y);

	Vector2D(const Vector2D &copyVector);

	float GetX();

	float GetY();

	// Returns a unit vector in the direction of the current vector
	Vector2D unitVector() const;

	// Vector addition
	Vector2D operator+(const Vector2D &addVector) const;

	// Vector subtraction
	Vector2D operator-(const Vector2D &minusVector) const;

	// Scalar multiplication
	Vector2D operator*(float multiplier) const;

	// Scalar multiplication
	Vector2D operator*(double multiplier) const;

	// Scalar multiplication
	Vector2D operator*(int multiplier) const;

	// Scalar division (same effect as multiplying by 1/divisor)
	Vector2D operator/(float divisor) const;

	// Scalar division (same effect as multiplying by 1/divisor)
	Vector2D operator/(double divisor) const;

	// Scalar division (same effect as multiplying by 1/divisor)
	Vector2D operator/(int divisor) const;

	// Vector addition
	void operator+=(const Vector2D &addVector);

	// Vector subtraction
	void operator-=(const Vector2D &addVector);

	// Scalar multiplication
	void operator*=(float multiplier);

	// Scalar multiplication
	void operator*=(double multiplier);

	// Scalar multiplication
	void operator*=(int multiplier);

	// Scalar division
	void operator/=(float divisor);

	// Scalar division
	void operator/=(double divisor);

	// Scalar division
	void operator/=(int divisor);

	// Dot operator
	float operator*(const Vector2D &otherVector) const;

	// Negative of a vector - same as vector, but in opposite direction
	Vector2D operator-() const;

	// Comparison of vectors
	bool operator==(const Vector2D &otherVector) const;

	// Returns the angle of the vector from the (0,1) direction
	float angle() const;

	// Sets the components of the vector
	void set(float x, float y);

	// Copies from another vector. Effectively identical to the = operator
	void set(const Vector2D &copyVector);

	// Returns the magnitude of the vector
	float magnitude() const;

	// Returns the square of the magnitude of the vector
	// (hence avoiding a square root.)
	float magnitudeSquared() const;

	// Sets the vector, using the angle (in radians) from the (0,1) direction and the magnitude
	void setBearing(float angle, float magnitude);

	// Returns a vector perpendicular to the current vector
	Vector2D perpendicularVector() const;

	// Returns true if the two vectors are parallel
	bool isParallelTo(const Vector2D &otherVector) const;

	// Returns true if the two vectors are perpendicular
	bool isPerpendicularTo(const Vector2D &otherVector) const;

	// Returns a vector of identical magnitude, but rotated by the specified angle (in radians)
	Vector2D rotatedBy(float angle) const;
};

Vector2D operator*(float multiplier, Vector2D v);
Vector2D operator*(int multiplier, Vector2D v);
Vector2D operator*(double multiplier, Vector2D v);

#endif
