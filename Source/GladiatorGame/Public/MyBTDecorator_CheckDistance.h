#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "MyBTDecorator_CheckDistance.generated.h"

UCLASS()
class GLADIATORGAME_API UMyBTDecorator_CheckDistance : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UMyBTDecorator_CheckDistance(const FObjectInitializer& ObjectInitializer);

	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
