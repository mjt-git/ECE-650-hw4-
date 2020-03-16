#include "exerciser.h"

void exercise(connection *C)
{
	query1(C, 
		1, 35, 40,
		0, 10, 20,
		0, 1, 5,
		0, 1, 10,
		0, 0.3, 1,
		0, 0.2, 1);

	query2(C, "Maroon");

	query3(C, "Duke");

	query4(C, "NC", "DarkBlue");

	query5(C, 10);

	add_player(C, 1, 330, "mjt", "jtm", 0,0,0,0,0.0,0.0);
}
