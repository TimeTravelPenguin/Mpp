// Name: Phillip Smith
// 
// Solution: Mpp
// Project: Mpp
// File Name: Input.h
// 
// Current Data:
// 2021-07-06 8:49 AM
// 
// Creation Date:
// 2021-07-05 12:47 AM

#ifndef INPUT_H
#define INPUT_H

#include <cstdint>

struct Input
{
public:
	Input() = default;
	Input(const int8_t& x, const int8_t& y, const int16_t& buttons);

	[[nodiscard]] int8_t GetX() const;
	[[nodiscard]] int8_t GetY() const;
	[[nodiscard]] int16_t GetButtons() const;
private:
	int8_t _x;
	int8_t _y;
	int16_t _buttons;
};

#endif
