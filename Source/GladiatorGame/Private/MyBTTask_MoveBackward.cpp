
#include "MyBTTask_MoveBackward.h"
#include "EnemyAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "GladiatorEnemy.h"

UMyBTTask_MoveBackward::UMyBTTask_MoveBackward(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Move Backward");
}

EBTNodeResult::Type UMyBTTask_MoveBackward::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	
	controller->MoveBackward();

	return EBTNodeResult::Succeeded;
}
