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

    float distanceFromPlayer = blackboard->GetValueAsFloat("distanceFromPlayer");

	return distanceFromPlayer > blackboard->GetValueAsFloat(GetSelectedBlackboardKey());
}

