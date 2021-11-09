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

	bool attack = blackboard->GetValueAsBool("attack");
	if (attack)
		return false;

#if 1 //Line trace
	FCollisionQueryParams traceParams = FCollisionQueryParams(FName("RV_Trace"));
	traceParams.bTraceComplex = true;
	traceParams.bReturnPhysicalMaterial = false;
	FHitResult hit;

	// Compute sight line
	FVector start, end;
	start = owner->GetActorLocation();
	end = Cast<AGladiatorPlayer>(blackboard->GetValueAsObject(GetSelectedBlackboardKey()))->GetActorLocation();
	start = start + (end - start).GetClampedToSize(75.f, 75.f);
	// Trace line
	owner->GetWorld()->LineTraceSingleByChannel(hit, start, end, ECollisionChannel::ECC_Pawn);

	//DrawDebugLine(owner->GetWorld(), start, end, FColor::Red, true, -1.f, 1, 5.f);

	AGladiatorPlayer* entity = Cast<AGladiatorPlayer>(hit.GetActor());
	bool sightTo = false;
	if (entity)
		sightTo = true;
#else //Sight to
	bool sightTo = controller->LineOfSightTo(Cast<APawn>(blackboard->GetValueAsObject(GetSelectedBlackboardKey())), (FVector)(ForceInit), true);
#endif

	return !sightTo;
}
