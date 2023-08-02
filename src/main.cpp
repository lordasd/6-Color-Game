#include "Controller.h"

int main() {
	srand(static_cast<unsigned>(time(nullptr)));
	Controller().run();
}