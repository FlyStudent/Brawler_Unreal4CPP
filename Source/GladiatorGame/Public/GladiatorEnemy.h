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
	class AEnemyAIController* controller;
	class AGladiatorPlayer* player;
	//void OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:
	virtual void BeginPlay() override;
	virtual void EntityDead() override;

	void StopAttack() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float minDistanceFromPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float maxDistanceFromPlayer;

public:	
	AGladiatorEnemy();

	virtual void Tick(float DeltaTime) override;

	void SetBlackboardAttack(bool canAttack = true);

	FORCEINLINE float GetDistanceFromPlayer(bool min) { return min ? minDistanceFromPlayer : maxDistanceFromPlayer; }
};
