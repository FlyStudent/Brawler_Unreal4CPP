#include "MyBTDecorator_Observ.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "GladiatorEnemy.h"

UMyBTDecorator_Observ::UMyBTDecorator_Observ(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Observ");
}

bool UMyBTDecorator_Observ::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto controller = OwnerComp.GetAIOwner();

	auto blackboard = controller->GetBlackboardComponent();
	//auto owner = Cast<AGladiatorEnemy>(controller->GetPawn());

	float distanceFromPlayer = controller->GetBlackboardComponent()->GetValueAsFloat(GetSelectedBlackboardKey());
	bool attack = blackboard->GetValueAsBool("attack");

	return !attack && distanceFromPlayer < 300.f;
}

