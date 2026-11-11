#include <iostream>
#include <string>
#include <cstring>

#define MAX_ENTRY 1

struct Entry
{
	std::string key;
	std::string val;
	Entry& next;
};

int
main(int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cerr << "RCipher2 needs an input file\n";
		return 1;
	}
	std::string filename(argv[2]);
	/*std::strung doesn't fail?*/
	if (strcmp(argv[1], "-o") == 0)
	{
		/*encrypt!*/	
	}
	return 0;
}
