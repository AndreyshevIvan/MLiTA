#include "Structs.h"
#include "Reading.h"
#include "math.h"

namespace
{
	const double PI = 3.14159265358979323846;
}

using namespace std;

size_t Calculate(Rect rect, Circle circle);

int main()
{
	Rect rect;
	Circle circle;

	ReadInput(rect, circle);

	size_t result = Calculate(rect, circle);
	PrintResult(result);

	return 0;
}

size_t Calculate(Rect rect, Circle circle)
{
	size_t result = 0;

	for (int y = rect.y; y >= rect.y - rect.height; y--)
	{
		for (int x = rect.x; x <= rect.x + rect.width; x++)
		{
			if (x >= circle.minX && x <= circle.maxX && circle.Contain(x, y))
			{
				result++;
			}
		}
	}

	return result;
}