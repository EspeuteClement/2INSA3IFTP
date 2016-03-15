#include "libs/Outils.h"
#include <unistd.h>

int main()
{
	InitialiserApplication(XTERM);

	pause();

	TerminerApplication(true);

	return 0;
}