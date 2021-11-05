#include "GladiatorEnemy.h"

#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AGladiatorEnemy::AGladiatorEnemy()
{
	attackTimerTime = 0.3f;

	life = 3;

	distanceFromPlayer = 300.f;
}

void AGladiatorEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	controller = Cast<AAIController>(GetController());
	player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AGladiatorEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (controller && player)
		controller->MoveToActor(player, distanceFromPlayer);
}