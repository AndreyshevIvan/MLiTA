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

	int largeY = (rect.y > circle.maxY) ? circle.maxY: rect.y;
	int smallY = (rect.y - rect.height > circle.minY) ? rect.y - rect.height : circle.minY;

	int largeX = (rect.x + rect.width < circle.maxX) ? rect.x + rect.width : circle.maxX;
	int smallX = (rect.x > circle.minX) ? rect.x : circle.minX;

	for (int y = largeY; y >= smallY; y--)
	{
		for (int x = smallX; x <= largeX; x++)
		{
			if (circle.Contain(x, y))
			{
				result++;
			}
		}
	}

	return result;
}