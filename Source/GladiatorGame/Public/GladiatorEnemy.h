#pragma once

#include "CoreMinimal.h"
#include "GladiatorEntity.h"
#include "GameFramework/Controller.h"

#include "GladiatorEnemy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLockEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnlockEvent);

UCLASS()
class GLADIATORGAME_API AGladiatorEnemy : public AGladiatorEntity
{
	GENERATED_BODY()

private:
	class AEnemyAIController* controller;
	class AGladiatorPlayer* player;
	void OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

protected:
	virtual void BeginPlay() override;
	virtual void EntityDead() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float minDistanceFromPlayer;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float maxDistanceFromPlayer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool locked = false;

public:	
	AGladiatorEnemy();

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FLockEvent lockEvent;

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FUnlockEvent unlockEvent;

	FORCEINLINE void BroadcastLockEvent() { lockEvent.Broadcast(); }
	FORCEINLINE void BroadcastUnlockEvent() { unlockEvent.Broadcast(); }

	void SetBlackboardAttack(bool canAttack = true);

	FORCEINLINE float GetDistanceFromPlayer(bool min) { return min ? minDistanceFromPlayer : maxDistanceFromPlayer; }
	FORCEINLINE void SetLock(bool l)
	{
		locked = l;
		locked ? BroadcastLockEvent() : BroadcastUnlockEvent();
	}
};
