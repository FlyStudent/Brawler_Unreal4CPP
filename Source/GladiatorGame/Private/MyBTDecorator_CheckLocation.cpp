#include "MyBTDecorator_CheckLocation.h"

#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "GladiatorEnemy.h"

UMyBTDecorator_CheckLocation::UMyBTDecorator_CheckLocation(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Check Location");
}

bool UMyBTDecorator_CheckLocation::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	auto blackboard = controller->GetBlackboardComponent();
	auto owner = Cast<AGladiatorEnemy>(controller->GetPawn());

	FVector location = owner->GetActorLocation();

	return location.Equals(blackboard->GetValueAsVector(GetSelectedBlackboardKey()), 100.f);
}
