#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "MyBTDecorator_CheckBlackboardBool.generated.h"

UCLASS()
class GLADIATORGAME_API UMyBTDecorator_CheckBlackboardBool : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTDecorator_CheckBlackboardBool(const FObjectInitializer& ObjectInitializer);

	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
