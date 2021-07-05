// Name: Phillip Smith
// 
// Solution: Mpp
// Project: Mpp
// File Name: Button.hpp
// 
// Current Data:
// 2021-07-06 12:26 AM
// 
// Creation Date:
// 2021-07-05 12:29 AM

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <map>
#include <vector>
#include <string>

namespace Mpp
{
	enum Button : unsigned short
	{
		CRight = 0x0001,
		CLeft = 0x0002,
		CDown = 0x0004,
		CUp = 0x0008,
		R = 0x0010,
		L = 0x0020,
		Reserved1 = 0x0040,
		Reserved2 = 0x0080,
		DPadRight = 0x0100,
		DPadLeft = 0x0200,
		DPadDown = 0x0400,
		DPadUp = 0x0800,
		Start = 0x1000,
		Z = 0x2000,
		B = 0x4000,
		A = 0x8000
	};

	static const std::map<Button, std::string> AllButtons{
		{CRight, "CRight"},
		{CLeft, "CLeft"},
		{CDown, "CDown"},
		{CUp, "CUp"},
		{R, "R"}, {L, "L"},
		{Reserved1, "Reserved1"},
		{Reserved2, "Reserved2"},
		{DPadRight, "DPadRight"},
		{DPadLeft, "DPadLeft"},
		{DPadDown, "DPadDown"},
		{DPadUp, "DPadUp"},
		{Start, "Start"},
		{Z, "Z"},
		{B, "B"},
		{A, "A"}
	};

	inline Button operator |(const Button a, const Button b)
	{
		return static_cast<Button>(static_cast<unsigned short>(a) | static_cast<unsigned short>(b));
	}

	static std::vector<std::string> ExtractButtons(const Button& button)
	{
		std::vector<std::string> vector;

		for (const auto& [btnVal, btnStr] : AllButtons)
		{
			if (button & btnVal)
			{
				vector.push_back(btnStr);
			}
		}

		return vector;
	}
}

#endif
