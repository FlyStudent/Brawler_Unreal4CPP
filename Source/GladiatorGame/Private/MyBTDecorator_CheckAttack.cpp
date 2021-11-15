#include "MyBTDecorator_CheckAttack.h"

#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "GladiatorEnemy.h"

UMyBTDecorator_CheckAttack::UMyBTDecorator_CheckAttack(const FObjectInitializer& ObjectInitializer)
{
	NodeName = TEXT("Check Attack");
}

bool UMyBTDecorator_CheckAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const 
{
	auto controller = Cast<AEnemyAIController>(OwnerComp.GetAIOwner());
	auto blackboard = controller->GetBlackboardComponent();
	auto owner = Cast<AGladiatorEnemy>(controller->GetPawn());

	if (blackboard->GetValueAsBool("canAttack") && !blackboard->GetValueAsBool("attack"))
	{
		// COMPUTE LOCATION
		FVector location = blackboard->GetValueAsVector("attackLocation");
		
		FVector Direction = Cast<APawn>(blackboard->GetValueAsObject("player"))->GetActorLocation() - owner->GetActorLocation();
		location = owner->GetActorLocation() + Direction;
		blackboard->SetValueAsVector("attackLocation", location);

		// SET TO PREPARE ATTACK
		return true;
	}

	return false;
}
