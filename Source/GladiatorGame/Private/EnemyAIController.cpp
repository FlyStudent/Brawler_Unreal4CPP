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

	SetActorTickEnabled(true);
}

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(bTree);
	behaviorTreeComponent->StartTree(*bTree);
}

void AEnemyAIController::SetPlayer(class AGladiatorPlayer* p)
{
	player = p;
	blackboard->SetValueAsObject("player", player);
}

void AEnemyAIController::MoveBackward()
{	
	Cast<AGladiatorEnemy>(GetPawn())->bUseControllerRotationYaw = false;
	FVector Direction = GetPawn()->GetActorLocation() - player->GetActorLocation();
	const FVector location = GetPawn()->GetActorLocation() + Direction.Normalize();
	MoveToLocation(location);
}

void AEnemyAIController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	auto owner = Cast<AGladiatorEnemy>(GetPawn());
	if (owner)
		blackboard->SetValueAsInt("life", owner->GetLife());
}

void AEnemyAIController::OnPossess(APawn* const pawn) 
{
	Super::OnPossess(pawn);
}