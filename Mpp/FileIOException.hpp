// Name: Phillip Smith
// 
// Solution: Mpp
// Project: Mpp
// File Name: FileIOException.hpp
// 
// Current Data:
// 2021-07-05 1:46 PM
// 
// Creation Date:
// 2021-07-05 1:55 AM

#ifndef FILEIOEXCEPTION_HPP
#define FILEIOEXCEPTION_HPP

#include <string>
#include <exception>

namespace Mpp
{
	class FileIOException final : public std::exception
	{
	public:
		FileIOException(const char* msg, const char* filePath) : exception(msg), _filePath(filePath)
		{
		}

		FileIOException(const std::string& msg, const std::string& filePath)
			: exception(msg.c_str()), _filePath(filePath)
		{
		}

		std::string& GetFilePath()
		{
			return _filePath;
		}

	private:
		std::string _filePath;
	};
}

#endif
