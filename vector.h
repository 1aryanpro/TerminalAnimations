#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
	int x;
	int y;
} Vector;

namespace vector
{
	Vector *make(int x, int y)
	{
		Vector* out = (Vector*)malloc(sizeof(Vector));
		out->x = x;
		out->y = y;

		return out;
	}

	int cmp(Vector *a, Vector *b)
	{
		if (a->x != b->x) { return 0; }
		if (a->y != b->y) { return 0; }
		return 1;
	}
}

#endif
