#pragma once

#include "CoreMinimal.h"
#include "GladiatorEntity.h"
#include "GameFramework/Controller.h"

#include "GladiatorEnemy.generated.h"

UCLASS()
class GLADIATORGAME_API AGladiatorEnemy : public AGladiatorEntity
{
	GENERATED_BODY()

private:
	class AAIController* controller;
	class AGladiatorPlayer* player;
	void OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:
	virtual void BeginPlay() override;
	virtual void EntityDead() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float distanceFromPlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UPawnSensingComponent* lineOfSight;

public:	
	AGladiatorEnemy();

	virtual void Tick(float DeltaTime) override;
};
