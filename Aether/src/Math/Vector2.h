#pragma once

#include "Core/Core.h"

namespace Aether {

	struct Vector2f
	{
		float x, y;

		Vector2f();
		Vector2f(float scalar);

		Vector2f(float x, float y);
		Vector2f(const Vector2f& other);

		Vector2f& Add(const Vector2f& other);
		Vector2f& Subtract(const Vector2f& other);
		Vector2f& Multiply(const Vector2f& other);
		Vector2f& Divide(const Vector2f& other);

		Vector2f& Add(float value);
		Vector2f& Subtract(float value);
		Vector2f& Multiply(float value);
		Vector2f& Divide(float value);

		friend Vector2f operator+(Vector2f left, const Vector2f& right);
		friend Vector2f operator-(Vector2f left, const Vector2f& right);
		friend Vector2f operator*(Vector2f left, const Vector2f& right);
		friend Vector2f operator/(Vector2f left, const Vector2f& right);

		friend Vector2f operator+(Vector2f left, float value);
		friend Vector2f operator-(Vector2f left, float value);
		friend Vector2f operator*(Vector2f left, float value);
		friend Vector2f operator/(Vector2f left, float value);

		Vector2f& operator+=(const Vector2f& other);
		Vector2f& operator-=(const Vector2f& other);
		Vector2f& operator*=(const Vector2f& other);
		Vector2f& operator/=(const Vector2f& other);

		Vector2f& operator+=(float scalar);
		Vector2f& operator-=(float scalar);
		Vector2f& operator*=(float scalar);
		Vector2f& operator/=(float scalar);

		bool operator==(const Vector2f& other) const;
		bool operator!=(const Vector2f& other) const;

		bool operator<(const Vector2f& other) const;
		bool operator>(const Vector2f& other) const;
		bool operator<=(const Vector2f& other) const;
		bool operator>=(const Vector2f& other) const;

		std::string ToString() const;

		friend std::ostream& operator<<(std::ostream& stream, const Vector2f& vector);
	};

}