// Name: Phillip Smith
// 
// Solution: Mpp
// Project: Mpp
// File Name: Input.cpp
// 
// Current Data:
// 2021-07-06 8:33 AM
// 
// Creation Date:
// 2021-07-05 12:47 AM

#include "Input.h"

Input::Input(const int8_t& x, const int8_t& y, const int16_t& buttons)
{
	_x = x;
	_y = y;
	_buttons = buttons;
}

int8_t Input::GetX() const
{
	return _x;
}

int8_t Input::GetY() const
{
	return _y;
}

int16_t Input::GetButtons() const
{
	return _buttons;
}
