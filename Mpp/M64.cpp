// Name: Phillip Smith
// 
// Solution: Mpp
// Project: Mpp
// File Name: M64.cpp
// 
// Current Data:
// 2021-07-06 8:21 AM
// 
// Creation Date:
// 2021-07-05 12:19 AM

#include "M64.h"

#include "FileIO.hpp"
#include "M64Parser.hpp"

using namespace Mpp;

M64 M64::CreateFromFile(const std::string& filePath)
{
	const auto contents = M64Parser::ParseFromFile(filePath);
	return M64(contents);
}

Input const& M64::operator[](const size_t index)
{
	return _inputs[index];
}

const Input& M64::operator[](const size_t index) const
{
	return _inputs[index];
}
