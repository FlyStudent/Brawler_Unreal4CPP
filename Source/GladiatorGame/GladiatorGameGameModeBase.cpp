// Copyright Epic Games, Inc. All Rights Reserved.

#include "GladiatorGameGameModeBase.h"
#include "Public/GladiatorPlayer.h"

AGladiatorGameGameModeBase::AGladiatorGameGameModeBase()
{
	DefaultPawnClass = AGladiatorPlayer::StaticClass();
}