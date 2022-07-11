#include "atpch.h"
#include "Vector3.h"

namespace Aether {
	Vector3f::Vector3f()
		: x(0.0f), y(0.0f), z(0.0f)
	{
	}

	Vector3f::Vector3f(float scalar)
		: x(scalar), y(scalar), z(scalar)
	{
	}

	Vector3f::Vector3f(float x, float y, float z)
		: x(x), y(y), z(z)
	{
	}

	Vector3f::Vector3f(const Vector3f& other)
	{
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
	}

	Vector3f& Vector3f::Add(const Vector3f& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	Vector3f& Vector3f::Subtract(const Vector3f& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	Vector3f& Vector3f::Multiply(const Vector3f& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	Vector3f& Vector3f::Divide(const Vector3f& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	Vector3f& Vector3f::Add(float value)
	{
		x += value;
		y += value;
		z += value;

		return *this;
	}

	Vector3f& Vector3f::Subtract(float value)
	{
		x -= value;
		y -= value;
		z -= value;

		return *this;
	}

	Vector3f& Vector3f::Multiply(float value)
	{
		x *= value;
		y *= value;
		z *= value;

		return *this;
	}

	Vector3f& Vector3f::Divide(float value)
	{
		x /= value;
		y /= value;
		z /= value;

		return *this;
	}

	Vector3f operator+(Vector3f left, const Vector3f& right)
	{
		return left.Add(right);
	}

	Vector3f operator-(Vector3f left, const Vector3f& right)
	{
		return left.Subtract(right);
	}

	Vector3f operator*(Vector3f left, const Vector3f& right)
	{
		return left.Multiply(right);
	}

	Vector3f operator/(Vector3f left, const Vector3f& right)
	{
		return left.Divide(right);
	}

	Vector3f operator+(Vector3f left, float value)
	{
		return left.Add(value);
	}

	Vector3f operator-(Vector3f left, float value)
	{
		return left.Subtract(value);
	}

	Vector3f operator*(Vector3f left, float value)
	{
		return left.Multiply(value);
	}

	Vector3f operator/(Vector3f left, float value)
	{
		return left.Divide(value);
	}

	Vector3f& Vector3f::operator+=(const Vector3f& other)
	{
		return Add(other);
	}

	Vector3f& Vector3f::operator-=(const Vector3f& other)
	{
		return Subtract(other);
	}

	Vector3f& Vector3f::operator*=(const Vector3f& other)
	{
		return Multiply(other);
	}

	Vector3f& Vector3f::operator/=(const Vector3f& other)
	{
		return Divide(other);
	}

	Vector3f& Vector3f::operator+=(float scalar)
	{
		return Add(scalar);
	}

	Vector3f& Vector3f::operator-=(float scalar)
	{
		return Subtract(scalar);
	}

	Vector3f& Vector3f::operator*=(float scalar)
	{
		return Multiply(scalar);
	}

	Vector3f& Vector3f::operator/=(float scalar)
	{
		return Divide(scalar);
	}

	bool Vector3f::operator==(const Vector3f& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}

	bool Vector3f::operator!=(const Vector3f& other) const
	{
		return !(*this == other);
	}

	bool Vector3f::operator<(const Vector3f& other) const
	{
		return x < other.x&& y < other.y && z < other.z;
	}

	bool Vector3f::operator>(const Vector3f& other) const
	{
		return x > other.x && y > other.y && z > other.z;
	}

	bool Vector3f::operator<=(const Vector3f& other) const
	{
		return x <= other.x && y <= other.y && z <= other.z;
	}

	bool Vector3f::operator>=(const Vector3f& other) const
	{
		return x >= other.x && y >= other.y && z >= other.z;
	}

	std::string Vector3f::ToString() const
	{
		std::stringstream ss;
		ss << "Vector3f: (" << x << ", " << y << ", " << z << ")";
		return ss.str();
	}

	std::ostream& operator<<(std::ostream& stream, const Vector3f& vector)
	{
		stream << vector.ToString();
		return stream;
	}
}