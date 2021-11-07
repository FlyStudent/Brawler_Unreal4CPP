
#include "GladiatorEnemy.h"

#include "AIController.h"
#include "GladiatorPlayer.h"

#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"


AGladiatorEnemy::AGladiatorEnemy()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 60.f);

	// Attack
	attackTimerTime = 0.3f;

	// Life
	life = 3;
}

void AGladiatorEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	AAIController* controller = Cast<AAIController>(GetController());
	APawn* player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (controller && player)
	{
		controller->MoveToActor(player);
	}
}

void AGladiatorEnemy::EntityDead()
{
	Super::EntityDead();
	Destroy();
}

void AGladiatorEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Collisions

void AGladiatorEnemy::OnAttackBeginOverlap(
	UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	Super::OnAttackBeginOverlap(OverlappedComp,	OtherActor,	OtherComp,	OtherBodyIndex,	bFromSweep,	SweepResult);

	if (attackCollider->IsActive())
	{
		auto player = Cast<AGladiatorPlayer>(OtherActor);

		if (player)
		{
			player->Hurt(1);
		}
	}
}