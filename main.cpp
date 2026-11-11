#include <iostream>
#include <string>
#include <cstring>

#define MAX_ENTRY 1
namespace rcr {
	unsigned int
	hash(const std::string& s, std::size_t n)
	{
		unsigned int hashval = 0;
		for (std::size_t i = 0; i < s.length(); ++i)
			if (s[i] != '\0')
				hashval = static_cast<unsigned int>(s[i]) * 31 + hashval;
		return hashval % n;
	}
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
		~HashMap (){
			rcr::Entry *curr = this->hashtab[0];
			while (curr){
				rcr::Entry *next = curr->next;
				delete curr;
				curr = next;
			}
			delete[] this->hashtab;
		}
		rcr::Entry* lookup(const std::string& s) const noexcept
		{
			unsigned int hval = hash(s, this->tabnum);
			rcr::Entry *curr = nullptr;
			for (curr = this->hashtab[hval]; curr; curr = curr->next)
				if (curr->key == s)
					return curr;
			return nullptr;	
		}
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
