#include "MyBTTask_Attack.h"

#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "GladiatorEnemy.h"
#include "GladiatorPlayer.h"

UMyBTTask_Attack::UMyBTTask_Attack(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UMyBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	auto blackboard = controller->GetBlackboardComponent();
	auto owner = Cast<AGladiatorEnemy>(controller->GetPawn());

	controller->SetFocus(nullptr);
	owner->Attack();

	return EBTNodeResult::Succeeded;
}