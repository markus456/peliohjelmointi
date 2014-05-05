#include "System.h"

int wmain(void) {
	System sys;
	if (sys.init()) {
		sys.enterMainLoop();
	}
	return 0;
}