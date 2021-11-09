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
		enemyArray.Add(Cast<AGladiatorEnemy>(actor));

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