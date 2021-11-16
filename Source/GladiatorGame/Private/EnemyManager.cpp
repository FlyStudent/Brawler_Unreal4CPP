#include "EnemyManager.h"

#include "Kismet/GameplayStatics.h"

#include "GladiatorEnemy.h"
#include "GladiatorPlayer.h"

AEnemyManager::AEnemyManager()
{
	PrimaryActorTick.bCanEverTick = false;

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

void AEnemyManager::ChooseAttackingEnemy()
{
	if (enemyArray.Num() != 0)
	{
		enemyArray[FMath::RandRange(0, enemyArray.Num() - 1)]->SetBlackboardAttack();
		ResetAttackTimer();
	}
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
		{
			enemyArray.RemoveAt(i);
			SendOrderedEnnemiesToPlayer();
		}
	}

	if (enemyArray.Num() == 0)
		BroadcastEnemyKilledEvent();
}

void AEnemyManager::BroadcastEnemyKilledEvent()
{
	enemyKilledEvent.Broadcast();
}

void AEnemyManager::SendOrderedEnnemiesToPlayer()
{
	auto player = Cast<AGladiatorPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	if (!player->IsLocking())
	{
		return;
	}
	else if (enemyArray.Num() == 0)
	{
		player->DisableLock();
		player->SwitchLockState();
		return;
	}

	FVector playerLocation = player->GetActorLocation();

	float minDistance = 10000.f;
	TArray<AGladiatorEnemy*> orderedEnemies;
	for (auto enemy : enemyArray)
	{
		float dist = FVector::Dist(playerLocation, enemy->GetActorLocation());
		if (dist < minDistance)
		{
			orderedEnemies.Insert(enemy, 0);
			minDistance = dist;
		}
		else
			orderedEnemies.Add(enemy);
	}

	orderedEnemies[0]->SetLock(true);
	player->SetEnnemiesTransform(orderedEnemies);
}