#include "atpch.h"
#include "Vector2.h"

namespace Aether {
	Vector2f::Vector2f()
		: x(0.0f), y(0.0f)
	{
	}

	Vector2f::Vector2f(float scalar)
		: x(scalar), y(scalar)
	{
	}

	Vector2f::Vector2f(float x, float y)
		: x(x), y(y)
	{
	}

	Vector2f::Vector2f(const Vector2f& other)
	{
		this->x = other.x;
		this->y = other.y;
	}

	Vector2f& Vector2f::Add(const Vector2f& other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	Vector2f& Vector2f::Subtract(const Vector2f& other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	Vector2f& Vector2f::Multiply(const Vector2f& other)
	{
		x *= other.x;
		y *= other.y;

		return *this;
	}

	Vector2f& Vector2f::Divide(const Vector2f& other)
	{
		x /= other.x;
		y /= other.y;

		return *this;
	}

	Vector2f& Vector2f::Add(float value)
	{
		x += value;
		y += value;

		return *this;
	}

	Vector2f& Vector2f::Subtract(float value)
	{
		x -= value;
		y -= value;

		return *this;
	}

	Vector2f& Vector2f::Multiply(float value)
	{
		x *= value;
		y *= value;

		return *this;
	}

	Vector2f& Vector2f::Divide(float value)
	{
		x /= value;
		y /= value;

		return *this;
	}

	Vector2f operator+(Vector2f left, const Vector2f& right)
	{
		return left.Add(right);
	}

	Vector2f operator-(Vector2f left, const Vector2f& right)
	{
		return left.Subtract(right);
	}

	Vector2f operator*(Vector2f left, const Vector2f& right)
	{
		return left.Multiply(right);
	}

	Vector2f operator/(Vector2f left, const Vector2f& right)
	{
		return left.Divide(right);
	}

	Vector2f operator+(Vector2f left, float value)
	{
		return left.Add(value);
	}

	Vector2f operator-(Vector2f left, float value)
	{
		return left.Subtract(value);
	}

	Vector2f operator*(Vector2f left, float value)
	{
		return left.Multiply(value);
	}

	Vector2f operator/(Vector2f left, float value)
	{
		return left.Divide(value);
	}

	Vector2f& Vector2f::operator+=(const Vector2f& other)
	{
		return Add(other);
	}

	Vector2f& Vector2f::operator-=(const Vector2f& other)
	{
		return Subtract(other);
	}

	Vector2f& Vector2f::operator*=(const Vector2f& other)
	{
		return Multiply(other);
	}

	Vector2f& Vector2f::operator/=(const Vector2f& other)
	{
		return Divide(other);
	}

	Vector2f& Vector2f::operator+=(float scalar)
	{
		return Add(scalar);
	}

	Vector2f& Vector2f::operator-=(float scalar)
	{
		return Subtract(scalar);
	}

	Vector2f& Vector2f::operator*=(float scalar)
	{
		return Multiply(scalar);
	}

	Vector2f& Vector2f::operator/=(float scalar)
	{
		return Divide(scalar);
	}

	bool Vector2f::operator==(const Vector2f& other) const
	{
		return x == other.x && y == other.y;
	}

	bool Vector2f::operator!=(const Vector2f& other) const
	{
		return !(*this == other);
	}

	bool Vector2f::operator<(const Vector2f& other) const
	{
		return x < other.x && y < other.y;
	}

	bool Vector2f::operator>(const Vector2f& other) const
	{
		return x > other.x && y > other.y;
	}

	bool Vector2f::operator<=(const Vector2f& other) const
	{
		return x <= other.x && y <= other.y;
	}

	bool Vector2f::operator>=(const Vector2f& other) const
	{
		return x >= other.x && y >= other.y;
	}

	std::string Vector2f::ToString() const
	{
		std::stringstream ss;
		ss << "Vector2f: (" << x << ", " << y << ")";
		return ss.str();
	}

	std::ostream& operator<<(std::ostream& stream, const Vector2f& vector)
	{
		stream << vector.ToString();
		return stream;
	}
}