#include "MyBTService_ServiceDistance.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "GladiatorPlayer.h"
#include "GladiatorEnemy.h"

UMyBTService_ServiceDistance::UMyBTService_ServiceDistance(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Distance Service");
}

void UMyBTService_ServiceDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	auto controller = OwnerComp.GetAIOwner();

	auto blackboard = controller->GetBlackboardComponent();
	auto owner = Cast<AGladiatorEnemy>(controller->GetPawn());

	if (owner)
	{
		float distanceFromPlayer = FVector::Dist(owner->GetActorLocation(), Cast<AGladiatorPlayer>(blackboard->GetValueAsObject("player"))->GetActorLocation());
		blackboard->SetValueAsFloat("distanceFromPlayer", distanceFromPlayer);
	}
}