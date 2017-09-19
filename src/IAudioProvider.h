#pragma once
#include "stdafx.h"

class IAudioProvider
{
public:
	virtual ~IAudioProvider() {}
	virtual void PlaySound(std::string filename) = 0;
	virtual bool IsSoundPlaying() = 0;
};