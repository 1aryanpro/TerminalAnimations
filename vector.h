#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
	float x;
	float y;
} Vector;

namespace vector
{
	Vector make(float x, float y)
	{
		Vector out;
		out.x = x;
		out.y = y;

		return out;
	}

	int cmp(Vector a, Vector b)
	{
		if (a.x != b.x) { return 0; }
		if (a.y != b.y) { return 0; }
		return 1;
	}

	Vector add(Vector a, Vector b)
	{
		Vector out;
		out.x = a.x + b.x;
		out.y = a.y + b.y;
		return out;
	}

	Vector mul(Vector a, Vector b)
	{
		Vector out;
		out.x = a.x * b.x;
		out.y = a.y * b.y;
		return out;
	}

	Vector mul(Vector a, float s)
	{
		Vector out;
		out.x = a.x * s;
		out.y = a.y * s;
		return out;
	}

}

#endif
