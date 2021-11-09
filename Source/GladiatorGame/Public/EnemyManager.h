#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyManager.generated.h"

UCLASS()
class GLADIATORGAME_API AEnemyManager : public AActor
{
	GENERATED_BODY()
	
private:
	TArray<class AGladiatorEnemy*> enemyArray;

	virtual void BeginPlay() override;
	void ChooseAttackingEnemy();
	void ResetAttackTimer();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float maxTime;

	FTimerHandle attackTimer;

public:	
	AEnemyManager();

	virtual void Tick(float DeltaTime) override;
};
