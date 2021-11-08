#include "MyBTService_ServiceAttack.h"

#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "GladiatorEnemy.h"

UMyBTService_ServiceAttack::UMyBTService_ServiceAttack(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Attack Service");
}

void UMyBTService_ServiceAttack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

	auto blackboard = controller->GetBlackboardComponent();
	auto owner = Cast<AGladiatorEnemy>(controller->GetPawn());

	if (owner)
	{
		blackboard->SetValueAsBool(GetSelectedBlackboardKey(), owner->IsAttacking());
		blackboard->SetValueAsBool("prepareAttack", controller->prepareAttack);
	}
}