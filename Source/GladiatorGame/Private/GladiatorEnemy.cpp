#include "GladiatorEnemy.h"

#include "EnemyAIController.h"
#include "GladiatorPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Perception/PawnSensingComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

AGladiatorEnemy::AGladiatorEnemy()
{
	attackTimerTime = 0.5f;
	invincibilityTimerTime = 0.2f;

	life = 3;
	damage = 1;

	minDistanceFromPlayer = 300.f;
	maxDistanceFromPlayer = 400.f;
}

void AGladiatorEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	player = Cast<AGladiatorPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	controller = Cast<AEnemyAIController>(GetController());
	Cast<AEnemyAIController>(controller)->SetPlayer(player);
}

void AGladiatorEnemy::EntityDead()
{
	Super::EntityDead();

	controller->SetFocus(this);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AGladiatorEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGladiatorEnemy::StopAttack()
{
	Super::StopAttack();
}

void AGladiatorEnemy::SetBlackboardAttack(bool canAttack)
{
	controller->GetBlackboard()->SetValueAsBool("canAttack", canAttack);
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
