#include "atpch.h"
#include "Vector4.h"

namespace Aether {
	Vector4f::Vector4f()
		: x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{
	}

	Vector4f::Vector4f(float scalar)
		: x(scalar), y(scalar), z(scalar), w(scalar)
	{
	}

	Vector4f::Vector4f(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{
	}

	Vector4f::Vector4f(const Vector4f& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		this->w = other.w;
	}

	Vector4f& Vector4f::Add(const Vector4f& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;

		return *this;
	}

	Vector4f& Vector4f::Subtract(const Vector4f& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;

		return *this;
	}

	Vector4f& Vector4f::Multiply(const Vector4f& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;

		return *this;
	}

	Vector4f& Vector4f::Divide(const Vector4f& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;

		return *this;
	}

	Vector4f& Vector4f::Add(float value)
	{
		x += value;
		y += value;
		z += value;
		w += value;

		return *this;
	}

	Vector4f& Vector4f::Subtract(float value)
	{
		x -= value;
		y -= value;
		z -= value;
		w -= value;

		return *this;
	}

	Vector4f& Vector4f::Multiply(float value)
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;

		return *this;
	}

	Vector4f& Vector4f::Divide(float value)
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;

		return *this;
	}

	Vector4f operator+(Vector4f left, const Vector4f& right)
	{
		return left.Add(right);
	}

	Vector4f operator-(Vector4f left, const Vector4f& right)
	{
		return left.Subtract(right);
	}

	Vector4f operator*(Vector4f left, const Vector4f& right)
	{
		return left.Multiply(right);
	}

	Vector4f operator/(Vector4f left, const Vector4f& right)
	{
		return left.Divide(right);
	}

	Vector4f operator+(Vector4f left, float value)
	{
		return left.Add(value);
	}

	Vector4f operator-(Vector4f left, float value)
	{
		return left.Subtract(value);
	}

	Vector4f operator*(Vector4f left, float value)
	{
		return left.Multiply(value);
	}

	Vector4f operator/(Vector4f left, float value)
	{
		return left.Divide(value);
	}

	Vector4f& Vector4f::operator+=(const Vector4f& other)
	{
		return Add(other);
	}

	Vector4f& Vector4f::operator-=(const Vector4f& other)
	{
		return Subtract(other);
	}

	Vector4f& Vector4f::operator*=(const Vector4f& other)
	{
		return Multiply(other);
	}

	Vector4f& Vector4f::operator/=(const Vector4f& other)
	{
		return Divide(other);
	}

	Vector4f& Vector4f::operator+=(float scalar)
	{
		return Add(scalar);
	}

	Vector4f& Vector4f::operator-=(float scalar)
	{
		return Subtract(scalar);
	}

	Vector4f& Vector4f::operator*=(float scalar)
	{
		return Multiply(scalar);
	}

	Vector4f& Vector4f::operator/=(float scalar)
	{
		return Divide(scalar);
	}

	bool Vector4f::operator==(const Vector4f& other) const
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}

	bool Vector4f::operator!=(const Vector4f& other) const
	{
		return !(*this == other);
	}

	bool Vector4f::operator<(const Vector4f& other) const
	{
		return x < other.x&& y < other.y&& z < other.z && w < other.w;
	}

	bool Vector4f::operator>(const Vector4f& other) const
	{
		return x > other.x && y > other.y && z > other.z && w > other.w;
	}

	bool Vector4f::operator<=(const Vector4f& other) const
	{
		return x <= other.x && y <= other.y && z <= other.z && w <= other.w;
	}

	bool Vector4f::operator>=(const Vector4f& other) const
	{
		return x >= other.x && y >= other.y && z >= other.z && w >= other.w;
	}

	std::string Vector4f::ToString() const
	{
		std::stringstream ss;
		ss << "Vector4f: (" << x << ", " << y << ", " << z << ", " << w << ")";
		return ss.str();
	}

	std::ostream& operator<<(std::ostream& stream, const Vector4f& vector)
	{
		stream << vector.ToString();
		return stream;
	}
}