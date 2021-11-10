#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBTTask_ComeBack.generated.h"

UCLASS()
class GLADIATORGAME_API UMyBTTask_ComeBack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()


	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UMyBTTask_ComeBack(const FObjectInitializer& ObjectInitializer);
};
