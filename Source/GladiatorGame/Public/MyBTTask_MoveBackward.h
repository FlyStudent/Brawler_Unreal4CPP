#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_MoveBackward.generated.h"

UCLASS()
class GLADIATORGAME_API UMyBTTask_MoveBackward : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UMyBTTask_MoveBackward(const FObjectInitializer& ObjectInitializer);
};
