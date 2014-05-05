#include "System.h"

int main(void) {
	System sys;
	if (sys.init()) {
		sys.enterMainLoop();
	}
	return 0;
}
