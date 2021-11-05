#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GladiatorEntity.generated.h"

UCLASS()
class GLADIATORGAME_API AGladiatorEntity : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* weaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* shieldMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* attackCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* defenseCollider;

	virtual void BeginPlay() override;

public:		
	AGladiatorEntity();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int life;

	FTimerHandle attackTimer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float attackTimerTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool attack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool usingShield;

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Attack();
	virtual void StopAttack();

	FORCEINLINE bool CanMove() const { return !attack && !usingShield; }
};
