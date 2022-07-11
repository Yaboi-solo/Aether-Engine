#pragma once

#include "Core/Core.h"

#include "Math.h"

namespace Aether {

	struct Matrix4f
	{
		float elements[4 * 4];

		Matrix4f();
		Matrix4f(float diagonal);
		Matrix4f(float* elements);

		static Matrix4f Identity();

		Matrix4f& Multiply(const Matrix4f& other);
		friend Matrix4f operator*(Matrix4f left, const Matrix4f& right);
		Matrix4f& operator*=(const Matrix4f& other);

		Matrix4f& Invert();

		static Matrix4f Orthographic(float left, float right, float bottom, float top, float near, float far);
		static Matrix4f Perspective(float fov, float aspectRatio, float near, float far);

		static Matrix4f Translate(const Vector3f& translation);
		static Matrix4f Rotate(float angle, const Vector3f& axis);
		static Matrix4f Scale(const Vector3f& scale);
	};

}