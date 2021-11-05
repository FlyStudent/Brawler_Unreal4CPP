// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GladiatorEntity.h"
#include "GladiatorEnemy.generated.h"

UCLASS()
class GLADIATORGAME_API AGladiatorEnemy : public AGladiatorEntity
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:	
	AGladiatorEnemy();


	virtual void Tick(float DeltaTime) override;
};
