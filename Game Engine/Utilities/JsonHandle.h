#pragma once
#include <json.hpp>
#include <string>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

class JsonHandle
{
public:
	JsonHandle();
	~JsonHandle();

	static json ReadFile(std::string);
};

