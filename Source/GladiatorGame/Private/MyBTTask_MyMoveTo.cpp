#include "MyBTTask_MyMoveTo.h"

#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "GladiatorEnemy.h"

UMyBTTask_MyMoveTo::UMyBTTask_MyMoveTo(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("My move to");
}

EBTNodeResult::Type UMyBTTask_MyMoveTo::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

	auto blackboard = controller->GetBlackboardComponent();
	//auto owner = Cast<AGladiatorEnemy>(controller->GetPawn());

	controller->MoveToActor(Cast<AActor>(blackboard->GetValueAsObject(GetSelectedBlackboardKey())), AcceptableRadius);

	return EBTNodeResult::Succeeded;
}
