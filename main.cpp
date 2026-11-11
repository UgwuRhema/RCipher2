#include <iostream>
#include <string>
#include <cstring>
#include <format>

#define MAX_ENTRY 1
namespace rcr {
	unsigned int
	hash(const std::string& s, std::size_t n)
	{
		unsigned int hashval = 0;
		for (std::size_t i = 0; i < s.length(); ++i)
				hashval = static_cast<unsigned int>(s[i]) * 31 + hashval;
		return hashval % n;
	}
	/*encrypt function*/
	void encrypt(std::string& text, std::string& cipher)
	{
		cipher.clear();
		cipher.reserve(text.length());
		for (char c: text)
		{
			unsigned char safeC = static_cast<unsigned char>(c);
			unsigned char res = (safeC >= 2) ? (safeC - 2) : (safeC + 254);
			cipher.push_back(static_cast<char>(res));
		}
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
		void add()
		{
			//todo: Implement add function
		}
		std::string get(const std::string& s) const noexcept
		{
			rcr::Entry *found = this->lookup(s);
			if (found != nullptr)
				return found->val;
			std::cerr << std::format("\"{}\" not found\n", s);
			return "";
		}
	};
};

int
main([[maybe_unused]]int argc, [[maybe_unused]]char *argv[])
{
	rcr::HashMap newMap(MAX_ENTRY);
	std::string a, b;
	std::cin >> a;
	rcr::encrypt(a, b);
	std::cout << std::format("Cipher Text: {}\n", b);
	return 0;
}
