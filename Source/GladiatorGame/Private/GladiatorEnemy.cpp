#include "GladiatorEnemy.h"

#include "AIController.h"
#include "GladiatorPlayer.h"

#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

AGladiatorEnemy::AGladiatorEnemy()
{
	attackTimerTime = 0.3f;
	invincibilityTimerTime = 0.2f;

	life = 3;
	damage = 1;

	distanceFromPlayer = 300.f;
}

void AGladiatorEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	controller = Cast<AAIController>(GetController());
	player = Cast<AGladiatorPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void AGladiatorEnemy::EntityDead()
{
	Super::EntityDead();
	Destroy();
}

void AGladiatorEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (controller && player)
		controller->MoveToActor(player, distanceFromPlayer);
}

// Collisions

void AGladiatorEnemy::OnAttackBeginOverlap( UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
											UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
											bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnAttackBeginOverlap(OverlappedComp,	OtherActor,	OtherComp,	OtherBodyIndex,	bFromSweep,	SweepResult);

	if (attackCollider->IsActive())
	{
		player = Cast<AGladiatorPlayer>(OtherActor);

		if (player)
			player->Hurt(damage);
	}
	
}
