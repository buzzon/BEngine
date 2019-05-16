#include "Tools.h"

const char * tools::read_file(const char * path)
{
	std::ifstream file(path, std::ios::binary);
	if (file) {
		file.seekg(0, std::ios_base::end);
		const auto length = file.tellg();
		file.seekg(0);

		const auto buffer = new char[length];
		file.read(buffer, length);
		buffer[length] = '\0';

		file.close();

		return buffer;
	}
	return " ";
}