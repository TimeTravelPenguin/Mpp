// Name: Phillip Smith
// 
// Solution: Mpp
// Project: Mpp
// File Name: M64HeaderOffsets.hpp
// 
// Current Data:
// 2021-07-05 3:26 PM
// 
// Creation Date:
// 2021-07-05 3:51 AM

#ifndef M64_HEADER_OFFSETS_HPP
#define M64_HEADER_OFFSETS_HPP

namespace Mpp
{
	enum M64HeaderOffset
	{
		ValidSignatureOffset = 0x000,
		VersionNumberOffset = 0x004,
		MovieUidOffset = 0x008,
		ViCountOffset = 0x00C,
		RerecordCountOffset = 0x010,
		ViPerSecondOffset = 0x014,
		ControllerCountOffset = 0x015,
		Reserved01Offset = 0x016,
		TotalInputFramesOffset = 0x018,
		MovieStartTypeOffset = 0x01C,
		Reserved02Offset = 0x01E,
		ControllerFlagsOffset = 0x020,
		Reserved03Offset = 0x024,
		RomNameOffset = 0x0C4,
		Crc32Offset = 0x0E4,
		RegionCodeOffset = 0x0E8,
		Reserved04Offset = 0x0EA,
		VideoPluginNameOffset = 0x122,
		AudioPlugin162NameOffset = 0x162,
		InputPluginNameOffset = 0x1A2,
		RspPluginNameOffset = 0x1E2,
		MovieAuthorNameOffset = 0x222,
		MovieDescriptionOffset = 0x300,
		InputsOffset = 0x400
	};
}

#endif
