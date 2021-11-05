#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "MyBTDecorator_CheckAttack.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORGAME_API UMyBTDecorator_CheckAttack : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTDecorator_CheckAttack(const FObjectInitializer& ObjectInitializer);

	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
