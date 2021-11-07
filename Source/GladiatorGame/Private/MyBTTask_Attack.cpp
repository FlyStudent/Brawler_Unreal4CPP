#include "MyBTTask_Attack.h"
#include "AIController.h"
//#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GladiatorEnemy.h"

UMyBTTask_Attack::UMyBTTask_Attack(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UMyBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto controller = OwnerComp.GetAIOwner();
	
	if (auto enemy = Cast<AGladiatorEnemy>(controller->GetPawn()))
		enemy->Attack();

	return EBTNodeResult::Succeeded;
}