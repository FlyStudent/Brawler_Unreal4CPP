#include "GladiatorEnemy.h"

#include "EnemyAIController.h"
#include "GladiatorPlayer.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

AGladiatorEnemy::AGladiatorEnemy()
{
	invincibilityTimerTime = 0.2f;

	maxLife = 3;
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

	controller->SetFocus(nullptr);
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SetLock(false);
}

void AGladiatorEnemy::SetBlackboardAttack(bool canAttack)
{
	controller->GetBlackboard()->SetValueAsBool("canAttack", canAttack);
}

void AGladiatorEnemy::OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	if (attackCollider->IsActive())
	{
		if (auto entity = Cast<AGladiatorPlayer>(OtherActor))
		{
			float angle = entity->GetShieldForward().CosineAngle2D(GetActorForwardVector());
			if (!entity->IsUsingShield() || angle > -0.2f)
				entity->Hurt(damage);
			else
				AttackBlocked();
		}
	}
}

