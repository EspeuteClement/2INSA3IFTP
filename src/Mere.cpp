#include "libs/Outils.h"
#include <unistd.h>

int main()
{
	InitialiserApplication(XTERM);

	sleep(5);

	TerminerApplication(true);

	return 0;
}