#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>
#include <crtdbg.h>

using namespace std;

int main() {
	testAll();
	testAllExtended();

	cout << "Test end" << endl;

	if (_CrtDumpMemoryLeaks())
		cout << "MEMORY LEAKS DETECTED!!!!!!!!!" << endl;
	else cout << "Memory correctly deallocated." << endl;

	system("pause");
}