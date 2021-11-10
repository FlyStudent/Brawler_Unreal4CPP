#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

UCLASS()
class GLADIATORGAME_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

private:

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* behaviorTreeComponent;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* bTree;

	class UBlackboardComponent* blackboard;
	class AGladiatorPlayer* player;
	class AGladiatorEnemy* owner;

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
		bool prepareAttack;

	AEnemyAIController(FObjectInitializer const& ObjectInitializer = FObjectInitializer::Get());

	void BeginPlay() override;
	
	void SetPlayer(class AGladiatorPlayer* player);

	void MoveBackward();
	void MoveOnSide();

	virtual void OnPossess(APawn* const pawn) override;

	FORCEINLINE class UBlackboardComponent* GetBlackboard() const { return blackboard; };
};
