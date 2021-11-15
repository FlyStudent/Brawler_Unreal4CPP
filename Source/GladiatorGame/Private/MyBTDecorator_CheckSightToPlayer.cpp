#include "MyBTDecorator_CheckSightToPlayer.h"

#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

#include "GladiatorEnemy.h"
#include "GladiatorPlayer.h"

UMyBTDecorator_CheckSightToPlayer::UMyBTDecorator_CheckSightToPlayer(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Check Sight");
}

bool UMyBTDecorator_CheckSightToPlayer::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	auto blackboard = controller->GetBlackboardComponent();
	auto owner = Cast<AGladiatorEnemy>(controller->GetPawn());

	// Compute sight line
	FVector start, end;
	start = owner->GetActorLocation() + owner->GetActorForwardVector().GetClampedToSize(75.f, 75.f);
	end = Cast<AGladiatorPlayer>(blackboard->GetValueAsObject(GetSelectedBlackboardKey()))->GetActorLocation();

	// Trace line
	FHitResult hit;
	owner->GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_Pawn);

	AGladiatorPlayer* entity = Cast<AGladiatorPlayer>(hit.GetActor());
	bool sightTo = false;
	if (entity)
		sightTo = true;

	return !sightTo;
}
