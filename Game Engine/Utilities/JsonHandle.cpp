/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: JsonHandle.cpp
Purpose: Read json format
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/

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

