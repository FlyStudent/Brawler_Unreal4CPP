#pragma once

#include "CoreMinimal.h"
#include "GladiatorEntity.h"
#include "GladiatorPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLockEnemyEvent);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnlockEnemyEvent);

UCLASS()
class GLADIATORGAME_API AGladiatorPlayer : public AGladiatorEntity
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

private:

	bool isChangingTarget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float changeTargetCooldown;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		bool isLocking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<class AGladiatorEnemy*> orderedEnemies;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int currentLockEnemy;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	
	void ChangeTargetRight();
	void ChangeTargetLeft();
	void FreeChangeTarget();

	void Shield();
	void StopShield();

	FORCEINLINE bool CanChangeTarget() const { return isLocking && !isChangingTarget && orderedEnemies.Num() != 0; }
	//void OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:
	virtual void BeginPlay() override;

	void EntityDead() override;

public:	
	AGladiatorPlayer();

	// Delegate
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FLockEnemyEvent lockEnemyEvent;
	UPROPERTY(BlueprintAssignable, Category = "Delegate")
		FUnlockEnemyEvent unlockEnemyEvent;

	FORCEINLINE void BroadcastLockEvent() { lockEnemyEvent.Broadcast(); }
	FORCEINLINE void BroadcastUnlockEvent() { unlockEnemyEvent.Broadcast(); }
	void Lock();

	// Turn
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	// Functions
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE void SetEnnemiesTransform(TArray<class AGladiatorEnemy*> enemies) { 
		currentLockEnemy = 0;
		orderedEnemies = enemies; 
	}
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
