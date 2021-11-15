#include "EnemyAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "GladiatorPlayer.h"
#include "GladiatorEnemy.h"

AEnemyAIController::AEnemyAIController(FObjectInitializer const& ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("/Game/AI/Enemy_BehaviorTree.Enemy_BehaviorTree"));
	if (obj.Succeeded())
		bTree = obj.Object;

	behaviorTreeComponent = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("bTreeComponent"));
	blackboard = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));

	SetActorTickEnabled(false);
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	// Variable init From pawn
	owner = Cast<AGladiatorEnemy>(GetPawn());

	// Behavior tree
	RunBehaviorTree(bTree);
	behaviorTreeComponent->StartTree(*bTree);
	blackboard->SetValueAsVector("attackLocation", FVector::ZeroVector);
	blackboard->SetValueAsFloat("minDistanceFromPlayer", owner->GetDistanceFromPlayer(true));
	blackboard->SetValueAsFloat("maxDistanceFromPlayer", owner->GetDistanceFromPlayer(false));
	blackboard->SetValueAsFloat("distanceFromPlayerToMoveOnSide", owner->GetDistanceFromPlayer(false) + 100.f);
	blackboard->SetValueAsBool("alive", true);
}

void AEnemyAIController::SetPlayer(class AGladiatorPlayer* p)
{
	player = p;
	blackboard->SetValueAsObject("player", player);
}

void AEnemyAIController::MoveBackward()
{	
	// rescale Attack timer if under 1s
	blackboard->SetValueAsFloat("attackTimer", FMath::Max(blackboard->GetValueAsFloat("attackTimer"), 1.f));

	if (owner->IsAlive())
		SetFocus(player);

	FVector Direction = owner->GetActorLocation() - player->GetActorLocation();
	const FVector location = owner->GetActorLocation() + Direction;
	MoveToLocation(location);
}

void AEnemyAIController::MoveOnSide() 
{
	// rescale Attack timer if under 1s
	blackboard->SetValueAsFloat("attackTimer", FMath::Max(blackboard->GetValueAsFloat("attackTimer"), 1.f));

	SetFocus(player);

	FVector Direction = owner->GetActorLocation() - player->GetActorLocation();
	FVector location = owner->GetActorLocation() + Direction.RotateAngleAxis(90.f, FVector::UpVector);

	MoveToLocation(location);
}