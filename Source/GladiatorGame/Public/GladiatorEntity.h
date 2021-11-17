#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GladiatorEntity.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHurtEvent);

UCLASS()
class GLADIATORGAME_API AGladiatorEntity : public ACharacter
{
	GENERATED_BODY()

protected:
	/// LIFE & INVINVIBILITY
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	int life;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int maxLife;

	FTimerHandle invincibilityTimer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Invincibility)
	float invincibilityTimerTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Invincibility)
	bool invincibility;

	/// ATTACK & SHIELD
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
	bool attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Attack)
	int damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
	bool attackBlocked;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool usingShield;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Attack)
	bool attackFailed;

	/// MESHES AND COLLIDERS
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* weaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* shieldMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* attackCollider;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* bloodParticleSystem;

	UFUNCTION()
	virtual void OnAttackBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void EmitBlood();

	UFUNCTION()
	void Invincibility();

	UFUNCTION()
	void StopInvincibility();
	
	UFUNCTION(BlueprintCallable)
	void BeginDamage();

	UFUNCTION(BlueprintCallable)
	void StopDamage();

	UFUNCTION(BlueprintCallable)
	virtual void StopAttack();

	UFUNCTION()
	void CheckIsAlive();

	virtual void EntityDead();
	
	virtual void BeginPlay() override;

public:	
	AGladiatorEntity();

	UPROPERTY(BlueprintAssignable, Category = "Delegate")
	FHurtEvent hurtEvent;

	UFUNCTION()
	void BroadcastHurtEvent();

	UFUNCTION(BlueprintCallable)
	virtual void Attack();

	UFUNCTION()
	void AttackBlocked();

	FVector GetShieldForward() const;

	UFUNCTION(BlueprintCallable)
	virtual void Hurt(int dmg);

	FORCEINLINE bool CanMove() const { return !attack && !usingShield; }
	FORCEINLINE bool IsAttacking() const { return attack; }
	FORCEINLINE bool IsUsingShield() const { return usingShield; }
	FORCEINLINE int GetLife() const { return life; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsBlocked() const { return attackBlocked; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsAlive() const { return life > 0; }
};
