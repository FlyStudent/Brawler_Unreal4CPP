#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_MyMoveTo.generated.h"

UCLASS()
class GLADIATORGAME_API UMyBTTask_MyMoveTo : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UPROPERTY(category = Node, EditAnywhere)
	float AcceptableRadius;

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UMyBTTask_MyMoveTo(const FObjectInitializer& ObjectInitializer);
};
