#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORGAME_API UMyBTTask_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:

	UMyBTTask_Attack(const FObjectInitializer& ObjectInitializer);
};
