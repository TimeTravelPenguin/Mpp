// Name: Phillip Smith
// 
// Solution: Mpp
// Project: Testing
// File Name: Testing.cpp
// 
// Current Data:
// 2021-07-06 8:29 AM
// 
// Creation Date:
// 2021-07-05 2:33 AM

#include <iostream>

#include "Button.hpp"
#include "FileIO.hpp"
#include "M64Parser.hpp"

int main()
{
	const auto m64File = R"(D:\ForkRepos\Mpp\Testing\M64Files\SMOv5_TAS.m64)";
	auto m64 = Mpp::M64::CreateFromFile(m64File);

	const Mpp::Button btn = Mpp::CUp | Mpp::R | Mpp::A | Mpp::CLeft;

	int i = 1;
	for (auto& value : m64)
	{
		std::cout << "Frame: " << i++ << " ";
		for (const auto& b : Mpp::ExtractButtons(static_cast<Mpp::Button>(value.GetButtons())))
		{
			std::cout << b << " ";
		}
		
		std::cout << std::endl;
	}
}
