/*-------------------------------------------------------

Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: SlideControl.cpp
Purpose: Control slides
Language: C++
Platform: VS2017, Windows
Project: CS529_shaoyanghuang_Final
Author: Shao-Yang Huang, shaoyang.huang, 60000619
Creation date: 12/1/2019

---------------------------------------------------------*/


#include "SlideControl.h"



SlideControl::SlideControl(TYPE control): Event(EVENT_TYPE::SLIDE_CONTROL), _control(control)
{
}


SlideControl::~SlideControl()
{
}
