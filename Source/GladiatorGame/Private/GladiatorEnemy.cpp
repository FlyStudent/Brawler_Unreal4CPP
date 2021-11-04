
#include "GladiatorEnemy.h"

#include "AIController.h"
#include "GladiatorPlayer.h"

#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"


AGladiatorEnemy::AGladiatorEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 60.f);

}

void AGladiatorEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	AAIController* controller = Cast<AAIController>(GetController());
	APawn* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GO !"));
	if (controller && player)
	{
		controller->MoveToActor(player);
	}
}

void AGladiatorEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGladiatorEnemy::Attack()
{
	if (!attack)
	{
		attack = true;
		GetWorldTimerManager().ClearTimer(attackTimer);
		GetWorldTimerManager().SetTimer(attackTimer, this, &AGladiatorEnemy::StopAttack, 1.0f, true, attackTimerTime);
	}
}

void AGladiatorEnemy::StopAttack()
{
	attack = false;
}

