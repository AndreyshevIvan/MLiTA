#include "Structs.h"
#include "Reading.h"

using namespace std;

int main()
{
	Rect* rect = nullptr;
	Circle* circle = nullptr;

	ReadInput(rect, circle);

	delete rect;
	delete circle;

	return 0;
}