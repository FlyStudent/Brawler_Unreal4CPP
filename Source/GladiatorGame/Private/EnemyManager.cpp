#include "EnemyManager.h"

#include "GladiatorEnemy.h"
#include "Kismet/GameplayStatics.h"

AEnemyManager::AEnemyManager()
{
	PrimaryActorTick.bCanEverTick = true;
	maxTime = 6.f;
}

void AEnemyManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actorArray;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGladiatorEnemy::StaticClass(), actorArray);

	for (AActor* actor : actorArray)
	{
		auto enemy = Cast<AGladiatorEnemy>(actor);
		enemyArray.Add(enemy);
		enemy->hurtEvent.AddDynamic(this, &AEnemyManager::CheckEnemyState);
	}

	ResetAttackTimer();
}

void AEnemyManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyManager::ChooseAttackingEnemy()
{
	enemyArray[FMath::RandRange(0, enemyArray.Num() - 1)]->SetBlackboardAttack();
	ResetAttackTimer();
}

void AEnemyManager::ResetAttackTimer()
{
	GetWorldTimerManager().ClearTimer(attackTimer);
	GetWorldTimerManager().SetTimer(attackTimer, this, &AEnemyManager::ChooseAttackingEnemy, 1.0f, true, FMath::RandRange(1.f, maxTime));
}

void AEnemyManager::CheckEnemyState()
{
	bool alive = false;
	for (int i = enemyArray.Num() - 1; i >= 0; i--)
	{
		if (!enemyArray[i]->IsAlive())
			enemyArray.RemoveAt(i);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("pingas"));
	if (enemyArray.Num() == 0)
		BroadcastEnemyKilledEvent();
}

void AEnemyManager::BroadcastEnemyKilledEvent()
{
	enemyKilledEvent.Broadcast();
}