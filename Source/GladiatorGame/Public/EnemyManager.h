#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnemyKilledEvent);

UCLASS()
class GLADIATORGAME_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
private:
	TArray<class AGladiatorEnemy*> enemyArray;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float maxTime;

	FTimerHandle attackTimer;


	virtual void BeginPlay() override;
	void ChooseAttackingEnemy();
	void ResetAttackTimer();

	UFUNCTION()
	void CheckEnemyState();

	UFUNCTION(BlueprintCallable)
	void SendEnnemiesTransformToPlayer();

public:	
	AEnemyManager();

	// Delegate
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FEnemyKilledEvent enemyKilledEvent;
	UFUNCTION()
	void BroadcastEnemyKilledEvent();

	virtual void Tick(float DeltaTime) override;
};
