#include "MyBTDecorator_CheckDistance.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "GladiatorEnemy.h"

UMyBTDecorator_CheckDistance::UMyBTDecorator_CheckDistance(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Check Distance");
}

bool UMyBTDecorator_CheckDistance::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const 
{
	const auto controller = OwnerComp.GetAIOwner();

    float distanceFromPlayer = controller->GetBlackboardComponent()->GetValueAsFloat(GetSelectedBlackboardKey());

	return distanceFromPlayer > 300.f;
}

