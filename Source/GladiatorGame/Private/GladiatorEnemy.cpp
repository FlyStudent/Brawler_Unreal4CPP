#include "GladiatorEnemy.h"

#include "EnemyAIController.h"
#include "GladiatorPlayer.h"

#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Perception/PawnSensingComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

AGladiatorEnemy::AGladiatorEnemy()
{
	attackTimerTime = 0.3f;
	invincibilityTimerTime = 0.2f;

	life = 3;
	damage = 1;

	distanceFromPlayer = 300.f;

	lineOfSight = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("lineOfSight"));
	lineOfSight->HearingThreshold = 0.f;
	lineOfSight->LOSHearingThreshold = 0.f;
	lineOfSight->SightRadius = 250.f;
	lineOfSight->SetPeripheralVisionAngle(25);
	lineOfSight->bOnlySensePlayers = false;
	lineOfSight->bHearNoises = false;
}

void AGladiatorEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	player = Cast<AGladiatorPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	controller = Cast<AAIController>(GetController());
	Cast<AEnemyAIController>(controller)->SetPlayer(player);
}

void AGladiatorEnemy::EntityDead()
{
	Super::EntityDead();
	Destroy();
}

void AGladiatorEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (lineOfSight->UPawnSensingComponent::HasLineOfSightTo(player))
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("see player"));
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
