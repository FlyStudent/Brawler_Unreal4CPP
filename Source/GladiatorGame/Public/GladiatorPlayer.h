#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GladiatorPlayer.generated.h"

UCLASS()
class GLADIATORGAME_API AGladiatorPlayer : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		class USkeletalMeshComponent* weaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
		USkeletalMeshComponent* shieldMesh;

private:
	FVector CurrentVelocity;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void Attack();
	void StopAttack();

	void Shield();
	void StopShield();

public:	
	AGladiatorPlayer();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		float BaseLookUpRate;

	/// ATTACK & SHIELD

	FTimerHandle attackTimer;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float attackTimerTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool attack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool usingShield;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE bool CanMove() const { return !attack && !usingShield; }

};
