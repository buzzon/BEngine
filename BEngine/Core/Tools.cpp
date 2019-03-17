#include "Tools.h"

const char * Tools::ReadFile(const char * path)
{
	std::ifstream file(path, std::ios::binary);
	if (file) {
		file.seekg(0, std::ios_base::end);
		std::ifstream::pos_type length = file.tellg();
		file.seekg(0);

		char * buffer = new char[length];
		file.read(buffer, length);
		buffer[length] = '\0';

		file.close();

		return buffer;
	}
	return " ";
}