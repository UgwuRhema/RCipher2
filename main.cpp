#include <iostream>
#include <string>
#include <cstring>

#define MAX_ENTRY 1
namespace rcr {
	struct Entry
	{
		std::string key;
		std::string val;
		Entry *next;/*since references can't be NULL*/
	};
	class HashMap 
	{
		public:
			Entry **hashtab;
			std::size_t tabnum;
			std::size_t len;
			/*constructor*/
		explicit HashMap(std::size_t tnum)
		: hashtab{new rcr::Entry*[tnum]()}, tabnum{tnum}, len{0}{}
	};
};

int
main(int argc, char *argv[])
{
	if (argc < 3)
	{
		std::cerr << "RCipher2 needs an input file\n";
		return 1;
	}
	rcr::HashMap newMap(MAX_ENTRY);
	return 0;
}
