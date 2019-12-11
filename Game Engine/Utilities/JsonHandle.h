/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: JsonHandle.h
Purpose: Read json format
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

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

