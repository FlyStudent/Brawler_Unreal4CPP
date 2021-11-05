#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GladiatorEntity.generated.h"

UCLASS()
class GLADIATORGAME_API AGladiatorEntity : public ACharacter
{
	GENERATED_BODY()

public:
	AGladiatorEntity();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int life;

	/// ATTACK & SHIELD
	FTimerHandle attackTimer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float attackTimerTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool attack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool usingShield;

	/// DEFAULT FUNC 
	virtual void BeginPlay() override;

	/// MESHES AND COLLIDERS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* weaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* shieldMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* attackCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class USphereComponent* defenseCollider;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Attack();
	virtual void StopAttack();

	FORCEINLINE bool CanMove() const { return !attack && !usingShield; }
	FORCEINLINE bool IsAttacking() const { return attack; }
	FORCEINLINE bool IsUsingShield() const { return usingShield; }
	FORCEINLINE int GetLife() const { return life; }
};
