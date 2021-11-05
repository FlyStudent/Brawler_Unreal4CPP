#include "MyBTService_ServiceAttack.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "GladiatorEnemy.h"

UMyBTService_ServiceAttack::UMyBTService_ServiceAttack(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Attack Service");
}

void UMyBTService_ServiceAttack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto controller = OwnerComp.GetAIOwner();

	auto blackboard = controller->GetBlackboardComponent();
	auto owner = Cast<AGladiatorEnemy>(controller->GetPawn());

	blackboard->SetValueAsString("Debug", "ATTACK");
	if (owner)
	{
		blackboard->SetValueAsString("Debug", "WORKING");
		blackboard->SetValueAsBool(GetSelectedBlackboardKey(), owner->IsAttacking());
	}
}