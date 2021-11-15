#include "MyBTDecorator_CheckBlackboardBool.h"

#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "GladiatorEnemy.h"

UMyBTDecorator_CheckBlackboardBool::UMyBTDecorator_CheckBlackboardBool(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Check Blackboard bool");
}

bool UMyBTDecorator_CheckBlackboardBool::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	auto controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	auto blackboard = controller->GetBlackboardComponent();

	return blackboard->GetValueAsBool(GetSelectedBlackboardKey());
}