#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyBTService_LifeService.generated.h"

UCLASS()
class GLADIATORGAME_API UMyBTService_LifeService : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTService_LifeService(const FObjectInitializer& ObjectInitializer);

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
