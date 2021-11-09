#include "MyBTTask_MoveOnSide.h"

#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "GladiatorEnemy.h"
#include "GladiatorPlayer.h"

UMyBTTask_MoveOnSide::UMyBTTask_MoveOnSide(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Move on side");
}

EBTNodeResult::Type UMyBTTask_MoveOnSide::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AEnemyAIController* controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

	controller->MoveOnSide();

	return EBTNodeResult::Succeeded;
}
