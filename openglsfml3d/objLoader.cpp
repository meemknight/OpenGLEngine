//I do not own this code

#include "objLoader.h"

namespace objl
{
	Vector3 objl::math::CrossV3(const Vector3 a, const Vector3 b)
	{
		return Vector3(a.Y * b.Z - a.Z * b.Y,
			a.Z * b.X - a.X * b.Z,
			a.X * b.Y - a.Y * b.X);
	}

	float math::MagnitudeV3(const Vector3 in)
	{

		return (sqrtf(powf(in.X, 2) + powf(in.Y, 2) + powf(in.Z, 2)));

	}

	float math::DotV3(const Vector3 a, const Vector3 b)
	{
		return (a.X * b.X) + (a.Y * b.Y) + (a.Z * b.Z);
	}

	float math::AngleBetweenV3(const Vector3 a, const Vector3 b)
	{
		float angle = DotV3(a, b);
		angle /= (MagnitudeV3(a) * MagnitudeV3(b));
		return angle = acosf(angle);
	}

	Vector3 math::ProjV3(const Vector3 a, const Vector3 b)
	{
		Vector3 bn = b / MagnitudeV3(b);
		return bn * DotV3(a, bn);
	}

	Vector3 objl::algorithm::operator*(const float & left, const Vector3 & right)
	{
		return Vector3(right.X * left, right.Y * left, right.Z * left);
	}

	bool algorithm::SameSide(Vector3 p1, Vector3 p2, Vector3 a, Vector3 b)
	{
		Vector3 cp1 = math::CrossV3(b - a, p1 - a);
		Vector3 cp2 = math::CrossV3(b - a, p2 - a);

		if (math::DotV3(cp1, cp2) >= 0)
			return true;
		else
			return false;
	}

	Vector3 algorithm::GenTriNormal(Vector3 t1, Vector3 t2, Vector3 t3)
	{
		Vector3 u = t2 - t1;
		Vector3 v = t3 - t1;

		Vector3 normal = math::CrossV3(u, v);

		return normal;
	}

	bool algorithm::inTriangle(Vector3 point, Vector3 tri1, Vector3 tri2, Vector3 tri3)
	{
		// Test to see if it is within an infinite prism that the triangle outlines.
		bool within_tri_prisim = SameSide(point, tri1, tri2, tri3) && SameSide(point, tri2, tri1, tri3)
			&& SameSide(point, tri3, tri1, tri2);

		// If it isn't it will never be on the triangle
		if (!within_tri_prisim)
			return false;

		// Calulate Triangle's Normal
		Vector3 n = GenTriNormal(tri1, tri2, tri3);

		// Project the point onto this normal
		Vector3 proj = math::ProjV3(point, n);

		// If the distance from the triangle to the point is 0
		//	it lies on the triangle
		if (math::MagnitudeV3(proj) == 0)
			return true;
		else
			return false;
	}

}

