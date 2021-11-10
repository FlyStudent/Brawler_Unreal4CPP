#include "MyBTTask_ComeBack.h"

#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "GladiatorEnemy.h"
#include "GladiatorPlayer.h"

UMyBTTask_ComeBack::UMyBTTask_ComeBack(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Come back");
}

EBTNodeResult::Type UMyBTTask_ComeBack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());

	auto owner = Cast<AGladiatorEnemy>(controller->GetPawn());

	owner->SetBlackboardAttack(false);

	return EBTNodeResult::Succeeded;
}
