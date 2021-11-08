#include "MyBTDecorator_CheckDistance.h"

#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "GladiatorEnemy.h"

UMyBTDecorator_CheckDistance::UMyBTDecorator_CheckDistance(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Check Distance");
}

bool UMyBTDecorator_CheckDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const 
{
	auto controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

	auto blackboard = controller->GetBlackboardComponent();
	//auto owner = Cast<AGladiatorEnemy>(controller->GetPawn());

    float distanceFromPlayer = blackboard->GetValueAsFloat(GetSelectedBlackboardKey());
	bool attack = blackboard->GetValueAsBool("attack");

	return !attack && distanceFromPlayer > controller->GetMaxDistanceFromPlayer();
}

