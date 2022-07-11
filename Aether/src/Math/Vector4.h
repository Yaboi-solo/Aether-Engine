#pragma once

#pragma once

#include "Core/Core.h"

namespace Aether {

	struct Vector4f
	{
		float x, y, z, w;

		Vector4f();
		Vector4f(float scalar);

		Vector4f(float x, float y, float z, float w);
		Vector4f(const Vector4f& other);

		Vector4f& Add(const Vector4f& other);
		Vector4f& Subtract(const Vector4f& other);
		Vector4f& Multiply(const Vector4f& other);
		Vector4f& Divide(const Vector4f& other);

		Vector4f& Add(float value);
		Vector4f& Subtract(float value);
		Vector4f& Multiply(float value);
		Vector4f& Divide(float value);

		friend Vector4f operator+(Vector4f left, const Vector4f& right);
		friend Vector4f operator-(Vector4f left, const Vector4f& right);
		friend Vector4f operator*(Vector4f left, const Vector4f& right);
		friend Vector4f operator/(Vector4f left, const Vector4f& right);

		friend Vector4f operator+(Vector4f left, float value);
		friend Vector4f operator-(Vector4f left, float value);
		friend Vector4f operator*(Vector4f left, float value);
		friend Vector4f operator/(Vector4f left, float value);

		Vector4f& operator+=(const Vector4f& other);
		Vector4f& operator-=(const Vector4f& other);
		Vector4f& operator*=(const Vector4f& other);
		Vector4f& operator/=(const Vector4f& other);

		Vector4f& operator+=(float scalar);
		Vector4f& operator-=(float scalar);
		Vector4f& operator*=(float scalar);
		Vector4f& operator/=(float scalar);

		bool operator==(const Vector4f& other) const;
		bool operator!=(const Vector4f& other) const;

		bool operator<(const Vector4f& other) const;
		bool operator>(const Vector4f& other) const;
		bool operator<=(const Vector4f& other) const;
		bool operator>=(const Vector4f& other) const;

		std::string ToString() const;

		friend std::ostream& operator<<(std::ostream& stream, const Vector4f& vector);
	};

}