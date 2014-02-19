#include "System.h"

int main(int argc, char** argv) {
	System sys;
	if (sys.init()) {
		sys.enterMainLoop();

		sys.exit();
	}

	return 0;
}