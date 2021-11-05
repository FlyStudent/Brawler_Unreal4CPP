
#include "MyBTDecorator_CheckAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "GladiatorEnemy.h"

UMyBTDecorator_CheckAttack::UMyBTDecorator_CheckAttack(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Check Attack");
}

bool UMyBTDecorator_CheckAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const 
{
	const auto controller = OwnerComp.GetAIOwner();

	return controller->GetBlackboardComponent()->GetValueAsBool(GetSelectedBlackboardKey());
}
