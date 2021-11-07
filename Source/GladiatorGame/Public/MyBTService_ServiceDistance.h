#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyBTService_ServiceDistance.generated.h"

UCLASS()
class GLADIATORGAME_API UMyBTService_ServiceDistance : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UMyBTService_ServiceDistance(const FObjectInitializer& ObjectInitializer);

	void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
