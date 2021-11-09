#include "MyBTDecorator_CheckSightToPlayer.h"

#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

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

	owner->GetWorld()->LineTraceSingleByChannel(hit, FVector::ZeroVector, Cast<APawn>(blackboard->GetValueAsObject(GetSelectedBlackboardKey()))->GetActorLocation(), ECollisionChannel::ECC_EngineTraceChannel1);
	bool sightTo = Cast<AGladiatorPlayer>(hit.Actor) ? true : false;
#else //Sight to
	bool sightTo = controller->LineOfSightTo(Cast<APawn>(blackboard->GetValueAsObject(GetSelectedBlackboardKey())), (FVector)(ForceInit), true);
#endif

	return !sightTo;
}
