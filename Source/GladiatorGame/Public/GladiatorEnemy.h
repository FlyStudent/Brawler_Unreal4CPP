// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GladiatorEntity.h"
#include "GladiatorEnemy.generated.h"

UCLASS()
class GLADIATORGAME_API AGladiatorEnemy : public AGladiatorEntity
{
	GENERATED_BODY()

private:

	void OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:
	virtual void BeginPlay() override;
	virtual void EntityDead() override;


public:	
	AGladiatorEnemy();


	virtual void Tick(float DeltaTime) override;
};
