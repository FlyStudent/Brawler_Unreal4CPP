// Copyright Epic Games, Inc. All Rights Reserved.

#include "Public/GladiatorPlayer.h"
#include "GladiatorGameGameModeBase.h"

AGladiatorGameGameModeBase::AGladiatorGameGameModeBase()
{
	DefaultPawnClass = AGladiatorPlayer::StaticClass();
}