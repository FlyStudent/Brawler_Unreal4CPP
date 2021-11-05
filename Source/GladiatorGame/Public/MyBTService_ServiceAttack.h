#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyBTService_ServiceAttack.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORGAME_API UMyBTService_ServiceAttack : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UMyBTService_ServiceAttack(const FObjectInitializer& ObjectInitializer);

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
