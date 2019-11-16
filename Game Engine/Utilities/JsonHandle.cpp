#include "JsonHandle.h"



JsonHandle::JsonHandle()
{
}


JsonHandle::~JsonHandle()
{
}

json JsonHandle::ReadFile(std::string file_path)
{
	std::ifstream file;
	file.open(file_path);

	json file_data;
	file >> file_data;

	file.close();
	return file_data;
}

