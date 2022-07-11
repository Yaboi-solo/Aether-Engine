#pragma once

#pragma once

#include "Core/Core.h"

namespace Aether {

	struct Vector3f
	{
		float x, y, z;

		Vector3f();
		Vector3f(float scalar);

		Vector3f(float x, float y, float z);
		Vector3f(const Vector3f& other);

		Vector3f& Add(const Vector3f& other);
		Vector3f& Subtract(const Vector3f& other);
		Vector3f& Multiply(const Vector3f& other);
		Vector3f& Divide(const Vector3f& other);

		Vector3f& Add(float value);
		Vector3f& Subtract(float value);
		Vector3f& Multiply(float value);
		Vector3f& Divide(float value);

		friend Vector3f operator+(Vector3f left, const Vector3f& right);
		friend Vector3f operator-(Vector3f left, const Vector3f& right);
		friend Vector3f operator*(Vector3f left, const Vector3f& right);
		friend Vector3f operator/(Vector3f left, const Vector3f& right);

		friend Vector3f operator+(Vector3f left, float value);
		friend Vector3f operator-(Vector3f left, float value);
		friend Vector3f operator*(Vector3f left, float value);
		friend Vector3f operator/(Vector3f left, float value);

		Vector3f& operator+=(const Vector3f& other);
		Vector3f& operator-=(const Vector3f& other);
		Vector3f& operator*=(const Vector3f& other);
		Vector3f& operator/=(const Vector3f& other);

		Vector3f& operator+=(float scalar);
		Vector3f& operator-=(float scalar);
		Vector3f& operator*=(float scalar);
		Vector3f& operator/=(float scalar);

		bool operator==(const Vector3f& other) const;
		bool operator!=(const Vector3f& other) const;

		bool operator<(const Vector3f& other) const;
		bool operator>(const Vector3f& other) const;
		bool operator<=(const Vector3f& other) const;
		bool operator>=(const Vector3f& other) const;

		std::string ToString() const;

		friend std::ostream& operator<<(std::ostream& stream, const Vector3f& vector);
	};

}