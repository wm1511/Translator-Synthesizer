#include "Dictionary.h"

void translator::Dictionary::loadDict(const std::filesystem::path& path)
{
	std::ifstream file(path, std::ios::in | std::ios::binary);
    const size_t size = std::filesystem::file_size(path);
    std::string input(size, '\0');
    file.read(input.data(), size);
	file.close();

	const char* delim = "\r\n\t";
	char* nextToken = NULL;
	char* token = strtok_s(input.data(), delim, &nextToken);

	while (token)
	{
		char* s1 = token;
		token = strtok_s(NULL, delim, &nextToken);
		char* s2 = token;
		token = strtok_s(NULL, delim, &nextToken);
		this->_dict.insert_or_assign(s1, s2);
	}
}

const std::string translator::Dictionary::getEquivalent(const std::string& word)
{
	auto pos = this->_dict.find(word);
	if (pos != this->_dict.end())
		return pos->second;
	else 
		return word;
}

size_t translator::Dictionary::getSize()
{
	return this->_dict.size();
}
