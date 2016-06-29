#include <iostream>

#include "E2E/e2edata.h"

int main(int argc, char **argv)
{
	if(argc != 2)
		return 1;

	E2E::E2EData data;

	std::cout << "lese: " << argv[1] << std::endl;
	data.readE2EFile(argv[1]);

	return 0;
}
