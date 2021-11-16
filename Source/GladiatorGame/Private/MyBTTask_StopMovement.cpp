#include "MyBTTask_StopMovement.h"

#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UMyBTTask_StopMovement::UMyBTTask_StopMovement(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Stop Movement");
}

EBTNodeResult::Type UMyBTTask_StopMovement::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	auto blackboard = controller->GetBlackboardComponent();

	controller->StopMovement();
	blackboard->SetValueAsBool("endMove", true);

	return EBTNodeResult::Succeeded;
}
