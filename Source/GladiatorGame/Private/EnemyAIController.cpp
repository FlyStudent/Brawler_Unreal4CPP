
#include "EnemyAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "GladiatorEnemy.h"

AEnemyAIController::AEnemyAIController(FObjectInitializer const& ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("/Game/AI/Enemy_BehaviorTree.Enemy_BehaviorTree"));
	if (obj.Succeeded())
	{
		bTree = obj.Object;
	}

	behaviorTreeComponent = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("bTreeComponent"));
	blackboard = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));

	SetActorTickEnabled(true);
}


void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(bTree);
	behaviorTreeComponent->StartTree(*bTree);
}

void AEnemyAIController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	auto owner = Cast<AGladiatorEnemy>(GetPawn());
	if (owner)
	{
		blackboard->SetValueAsInt("life", owner->life);
	}
}

void AEnemyAIController::OnPossess(APawn* const pawn) 
{
	Super::OnPossess(pawn);
}