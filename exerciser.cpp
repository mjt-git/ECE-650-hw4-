#include "exerciser.h"

void exercise(connection *C)
{
	query1(C, 
		1, 10, 20,
		1, 10, 20,
		1, 1, 5,
		0, 1, 10,
		0, 0.3, 1,
		0, 0.2, 1);

	query2(C, "Maroon");

	query3(C, "Duke");

	query4(C, "NC", "DarkBlue");

	query5(C, 10);
}
