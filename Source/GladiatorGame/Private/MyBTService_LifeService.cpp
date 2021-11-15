#include "MyBTService_LifeService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "GladiatorPlayer.h"
#include "GladiatorEnemy.h"

UMyBTService_LifeService::UMyBTService_LifeService(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Life Service");
}

void UMyBTService_LifeService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto controller = OwnerComp.GetAIOwner();
	auto blackboard = controller->GetBlackboardComponent();
	auto owner = Cast<AGladiatorEnemy>(controller->GetPawn());

	blackboard->SetValueAsBool("alive", owner->IsAlive());
}
