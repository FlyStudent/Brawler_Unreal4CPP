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

	// Variable init From pawn
	auto enemy = Cast<AGladiatorEnemy>(GetPawn());

	// Behavior tree
	RunBehaviorTree(bTree);
	behaviorTreeComponent->StartTree(*bTree);
	blackboard->SetValueAsVector("attackLocation", FVector::ZeroVector);
	blackboard->SetValueAsFloat("minDistanceFromPlayer", enemy->GetDistanceFromPlayer(true));
	blackboard->SetValueAsFloat("maxDistanceFromPlayer", enemy->GetDistanceFromPlayer(false));
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

	SetFocus(player);

	FVector Direction = GetPawn()->GetActorLocation() - player->GetActorLocation();
	const FVector location = GetPawn()->GetActorLocation() + Direction;
	MoveToLocation(location);
}

void AEnemyAIController::MoveOnSide() 
{
	// rescale Attack timer if under 1s
	blackboard->SetValueAsFloat("attackTimer", FMath::Max(blackboard->GetValueAsFloat("attackTimer"), 1.f));

	SetFocus(player);

	FVector Direction = GetPawn()->GetActorLocation() - player->GetActorLocation();
	FVector location = GetPawn()->GetActorLocation() + Direction.RotateAngleAxis(90.f, FVector::UpVector);

	MoveToLocation(location);
}

void AEnemyAIController::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);

	auto owner = Cast<AGladiatorEnemy>(GetPawn());
	if (owner)
	{
		blackboard->SetValueAsInt("life", owner->GetLife());
		blackboard->SetValueAsBool("alive", owner->IsAlive());
	}
}

void AEnemyAIController::OnPossess(APawn* const pawn) 
{
	Super::OnPossess(pawn);
}