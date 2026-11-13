#include <iostream>
#include <string>
#include <cstring>
#include <format>
#include <fstream>

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
	void decrypt(std::string& cipher, std::string& text)
	{
		text.clear();
		text.reserve(cipher.length());
		for (char c: cipher)
		{
			unsigned char safeC = static_cast<unsigned char>(c);
			/*let's perfoem the operation on it*/
			unsigned char res = safeC + 2;
			text.push_back(static_cast<char>(res));
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
	if (argv[1] != NULL && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
		/*help function just like rcipher*/
		std::cout << std::format("RCipher2\n");
		std::cout << std::format("Usage: rcipher2 [options] <file>\n");
		std::cout << std::format("Options:\n");
		std::cout << std::format("\t-o <filename>: To Create a new Cipher\n");
		std::cout << std::format("\t-d <filename>: To Decrypt a Cipher found inside a file\n");
		std::cout << std::format("\t--help or -h: Display this message\n");
		return 0;
	}
	if (argc < 3)
	{
		std::cerr << "RCipher2 needs a filename\n";
		return 1;
	}
	std::string filename(static_cast<std::string>(argv[2]));
	rcr::HashMap newMap(MAX_ENTRY); /*new HashMap*/
	if (strcmp(argv[1], "-o") == 0)
	{
		std::ofstream file(filename);
		std::string plainText, cipherText;
		std::cout << std::format("Text: ");
		std::getline(std::cin, plainText);
		rcr::encrypt(plainText, cipherText);
		file << cipherText;
		file.close();
	} else if (strcmp(argv[1], "-d") == 0) {
		std::ifstream file(filename);
		std::string cipherText, plainText;
		while (std::getline(file, cipherText));
		std::cout << std::format("Cipher Text: {}\n", cipherText);
		rcr::decrypt(cipherText, plainText);
		std::cout << std::format("Decryption Successful!\n{}\n", plainText);
		file.close();
	} else {
		std::cerr << std::format("Unknown Command: '{}'\n", argv[1]);
		return 1;
	}
	return 0;
	
}
