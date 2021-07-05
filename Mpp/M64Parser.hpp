// Name: Phillip Smith
// 
// Solution: Mpp
// Project: Mpp
// File Name: M64Parser.hpp
// 
// Current Data:
// 2021-07-06 8:46 AM
// 
// Creation Date:
// 2021-07-05 1:32 AM

#ifndef M64_PARSER_HPP
#define M64_PARSER_HPP

#include <vector>
#include <algorithm>
#include <string>
#include "Constants.hpp"
#include "FileIO.hpp"
#include "M64.h"
#include "M64HeaderOffsets.hpp"

namespace Mpp
{
	namespace Ranges = std::ranges;

	class M64Parser
	{
	public:
		static bool ValidateM64FileContents(const std::string& fileContentStream)
		{
			// M64 header has 1024 bytes, and is then followed by input data
			if (fileContentStream.length() <= InputsOffset)
			{
				return false;
			}

			const auto headerSignature = ReadBytesString(fileContentStream, ValidSignatureOffset, 4, Encoding::Ascii);
			const auto signatureCStr = headerSignature.c_str();
			const auto validSignature = strncmp(signatureCStr, Constants::ValidM64Signature, 4) == 0;
			const auto version = ReadBytes<uint32_t>(fileContentStream, VersionNumberOffset);

			const auto reserved01 = ReadBytes<uint8_t>(fileContentStream, Reserved01Offset);
			const auto reserved02 = ReadBytes<uint8_t>(fileContentStream, Reserved02Offset);
			const auto reserved03 = ReadBytes<char>(fileContentStream, Reserved03Offset, 160);
			const auto reserved04 = ReadBytes<char>(fileContentStream, Reserved04Offset, 56);

			const auto valid03 = Ranges::all_of(reserved03, [](const auto& i) { return i == 0; });
			const auto valid04 = Ranges::all_of(reserved04, [](const auto& i) { return i == 0; });

			const auto validReserved = reserved01 == 0 && reserved02 == 0 && valid03 && valid04;

			return validSignature && version == 3 && validReserved;
		}

		static M64 ParseFromFile(const std::string& filePath)
		{
			const auto fileContentStream = ReadBinary(filePath);

			if (!ValidateM64FileContents(fileContentStream))
			{
				throw FileIOException("Invalid Mupen64 file.", filePath);
			}

			M64 m64;
			m64._signature = ReadBytes<int32_t>(fileContentStream, ValidSignatureOffset);
			m64._version = ReadBytes<uint32_t>(fileContentStream, VersionNumberOffset);
			m64._movieUid = ReadBytes<int32_t>(fileContentStream, MovieUidOffset);
			m64._viCount = ReadBytes<uint32_t>(fileContentStream, ViCountOffset);
			m64._rerecordCount = ReadBytes<uint32_t>(fileContentStream, RerecordCountOffset);
			m64._viPerSecond = ReadBytes<uint8_t>(fileContentStream, ViPerSecondOffset);
			m64._controllerCount = ReadBytes<uint8_t>(fileContentStream, ControllerCountOffset);
			m64._totalInputs = ReadBytes<int32_t>(fileContentStream, TotalInputFramesOffset);
			m64._movieStartType = ReadBytes<uint16_t>(fileContentStream, MovieStartTypeOffset);
			m64._controllerFlags = ReadBytes<uint32_t>(fileContentStream, ControllerFlagsOffset);
			m64._Crc32 = ReadBytes<uint32_t>(fileContentStream, Crc32Offset);
			m64._regionCode = ReadBytes<uint16_t>(fileContentStream, RegionCodeOffset);
			m64._RomName = ReadBytesString(fileContentStream, RomNameOffset, 32, Encoding::Ascii);
			m64._videoPluginName = ReadBytesString(fileContentStream, VideoPluginNameOffset, 64, Encoding::Ascii);
			m64._audioPluginName = ReadBytesString(fileContentStream, AudioPlugin162NameOffset, 64, Encoding::Ascii);
			m64._inputPluginName = ReadBytesString(fileContentStream, InputPluginNameOffset, 64, Encoding::Ascii);
			m64._rspPluginName = ReadBytesString(fileContentStream, RspPluginNameOffset, 64, Encoding::Ascii);
			m64._authorName = ReadBytesString(fileContentStream, MovieAuthorNameOffset, 222, Encoding::Utf8);
			m64._authorMovieDescription = ReadBytesString(fileContentStream, MovieDescriptionOffset, 256,
			                                              Encoding::Utf8);
			m64._inputs = ParseInputFromFile(fileContentStream);

			return m64;
		}

		static std::vector<Input> ParseInputFromFile(const std::string& fileContentStream)
		{
			auto fileInputs = std::string(fileContentStream.begin() + InputsOffset, fileContentStream.end());

			const auto inputLen = fileInputs.length();
			if (inputLen % 4 != 0)
			{
				throw std::exception("File inputs are malformed.");
			}

			std::vector<Input> inputs;
			inputs.reserve(inputLen / 4);

			auto iter = fileInputs.begin();
			while (iter != fileInputs.end())
			{
				int16_t buttons;
				int8_t x;
				int8_t y;

				memcpy(&buttons, &*iter, sizeof(int16_t));
				memcpy(&x, &*iter + 4, sizeof(int8_t));
				memcpy(&y, &*iter + 8, sizeof(int8_t));


				const auto swapped = ByteSwap(buttons);

				Input input(x, y, swapped);
				inputs.push_back(input);

				iter += 4;
			}

			return inputs;
		}

		static int16_t ByteSwap(int16_t& value)
		{
			// buttons is short = AB
			// swap bytes = BA
			// see: https://stackoverflow.com/questions/3916097/integer-byte-swapping-in-c
			
			return ((value & 0xff) << 8) | ((value & 0xff00) >> 8);
		}
	};
}

#endif
