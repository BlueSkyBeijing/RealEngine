#pragma once
#include <float.h>
#include <cmath>

class Vector3 
{
public:
	float X, Y, Z;

public:
	Vector3() {}

	Vector3(const Vector3 &Value) :X(Value.X), Y(Value.Y), Z(Value.Z) {}

	Vector3(float ValueX, float ValueY, float ValueZ) : X(ValueX), Y(ValueY), Z(ValueZ) {}


	bool operator==(const Vector3 &Value) const {
		return X == Value.X&& Y == Value.Y&&Z == Value.Z;
	}
	bool operator !=(const Vector3 &Value) const {
		return X != Value.X || Y != Value.Y || Z != Value.Z;
	}

	Vector3 operator+(const Vector3 &Value) const
	{
		return Vector3(X + Value.X, Y + Value.Y, Z + Value.Z);
	}

	Vector3 operator-() const
	{ 
		return Vector3(-X, -Y, -Z); 
	}

	Vector3 operator-(const Vector3 &Value) const 
	{
		return Vector3(X - Value.X, Y - Value.Y, Z - Value.Z);
	}

	Vector3 operator*(float Value) const
	{
		return Vector3(X*Value, Y*Value, Z*Value);
	}

	Vector3 operator/(float Value) const 
	{
		float Cosecant = 1.0f / Value;

		return Vector3(X*Cosecant, Y*Cosecant, Z*Cosecant);
	}

	Vector3 &operator+=(const Vector3 &Value) 
	{
		X += Value.X; Y += Value.Y; Z += Value.Z;

		return *this;
	}

	Vector3 &operator-=(const Vector3 &Value)
	{
		X -= Value.X; Y -= Value.Y; Z -= Value.Z;

		return *this;
	}

	Vector3 &operator*=(float Value) 
	{
		X *= Value; Y *= Value; Z *= Value;

		return *this;
	}

	Vector3 &operator/=(float Value) 
	{
		float Cosecant = 1.0f / Value;
		X *= Cosecant; Y *= Cosecant; Z *= Cosecant;

		return *this;
	}

	void Normalize() 
	{
		float SquareSum = X * X + Y * Y + Z * Z;
		if (SquareSum > 0.0f)
		{
			float Cosecant = 1.0f / sqrt(SquareSum);
			X *= Cosecant;
			Y *= Cosecant;
			Z *= Cosecant;
		}
	}

	float operator*(const Vector3 &Value) const 
	{
		return X * Value.X + Y * Value.Y + Z * Value.Z;
	}
};

inline float Length(const Vector3 &Value) 
{
	return sqrt(Value.X*Value.X + Value.Y*Value.Y + Value.Z*Value.Z);
}

inline Vector3 CrossProduct(const Vector3 &ValueA, const Vector3 &ValueB)
{
	return Vector3(ValueA.Y*ValueB.Z - ValueA.Z* ValueB.Y, ValueA.Z*ValueB.X - ValueA.X*ValueB.Z, ValueA.X*ValueB.Y - ValueA.Y*ValueB.X);
}

inline Vector3 operator*(float k, const Vector3 &v) 
{
	return Vector3(k*v.X, k*v.Y, k*v.Z);
}

inline float Distance(const Vector3 &ValueA, const Vector3 &ValueB)
{
	float dx = ValueA.X - ValueB.X;
	float dy = ValueA.Y - ValueB.Y;
	float dz = ValueA.Z - ValueB.Z;
	return sqrt(dx*dx + dy * dy + dz * dz);
}