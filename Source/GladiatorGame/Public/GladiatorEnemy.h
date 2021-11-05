#pragma once

#include "CoreMinimal.h"
#include "GladiatorEntity.h"
#include "GameFramework/Controller.h"

#include "AIController.h"
#include "GladiatorPlayer.h"

#include "GladiatorEnemy.generated.h"

UCLASS()
class GLADIATORGAME_API AGladiatorEnemy : public AGladiatorEntity
{
	GENERATED_BODY()

private:
	AAIController* controller;
	APawn* player;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float distanceFromPlayer;

public:	
	AGladiatorEnemy();

	virtual void Tick(float DeltaTime) override;
};
