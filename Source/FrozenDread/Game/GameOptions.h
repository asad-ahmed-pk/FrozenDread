//
// GameOptions.h
// Definition of structs for simplified game options
//

#pragma once

namespace GameSettings
{
	enum class EScale
	{
		SCALE_LOW = 0,
		SCALE_MEDIUM = 1,
		SCALE_HIGH = 2,
		SCALE_EPIC = 3,
		SCALE_CINEMATIC = 4
	};

	/**
	 * Represents simplified graphics options for the game
	 */
	struct FGraphicsOptions
	{
		bool EnableLumen { false };
		EScale GraphicsQuality { EScale::SCALE_HIGH };
		FIntPoint ScreenResolution { 1920, 1080 };
	};
}
