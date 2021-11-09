#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "MyBTDecorator_CheckSightToPlayer.generated.h"

UCLASS()
class GLADIATORGAME_API UMyBTDecorator_CheckSightToPlayer : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTDecorator_CheckSightToPlayer(const FObjectInitializer& ObjectInitializer);

	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
