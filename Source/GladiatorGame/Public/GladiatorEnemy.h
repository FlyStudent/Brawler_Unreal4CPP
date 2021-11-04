// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GladiatorEnemy.generated.h"

UCLASS()
class GLADIATORGAME_API AGladiatorEnemy : public ACharacter
{
	GENERATED_BODY()

private:
	void Attack();
	void StopAttack();

protected:
	virtual void BeginPlay() override;

public:	
	AGladiatorEnemy();

	FTimerHandle attackTimer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float attackTimerTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool attack;

	virtual void Tick(float DeltaTime) override;
};
