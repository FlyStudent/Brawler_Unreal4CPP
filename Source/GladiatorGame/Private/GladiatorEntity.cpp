#include "GladiatorEntity.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AGladiatorEntity::AGladiatorEntity()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 60.f);

	// Meshes
	weaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	weaponMesh->AttachTo(GetMesh(), "WeaponPoint", EAttachLocation::SnapToTarget, true);

	shieldMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShieldMesh"));
	shieldMesh->AttachTo(GetMesh(), "DualWeaponPoint", EAttachLocation::SnapToTarget, true);

	GetMesh()->SetWorldLocation(FVector(0.f, 0.f, -70.f));

	// Collider
	attackCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Collider"));
	attackCollider->SetupAttachment(weaponMesh);
	attackCollider->SetWorldLocation(FVector(0.f, 60.f, 0.f));

	defenseCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Defense Collider"));
	defenseCollider->SetupAttachment(shieldMesh);
	defenseCollider->SetWorldLocation(FVector(4.f, 2.f, 14.f));
	defenseCollider->SetSphereRadius(50.f);
}

void AGladiatorEntity::BeginPlay()
{
	Super::BeginPlay();

	attackCollider->Deactivate();
	defenseCollider->Deactivate();

	attackCollider->OnComponentBeginOverlap.AddDynamic(this, &AGladiatorEntity::OnAttackBeginOverlap);

	hurtEvent.AddDynamic(this, &AGladiatorEntity::Invincibility);
}

void AGladiatorEntity::EntityDead() 
{
	GetCharacterMovement()->Deactivate();
	GetCharacterMovement()->DisableMovement();
}

void AGladiatorEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!IsAlive())
		EntityDead();
}

void AGladiatorEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGladiatorEntity::Attack()
{
	if (!attack)
	{
		attack = true;
		attackCollider->Activate();
		GetWorldTimerManager().ClearTimer(attackTimer);
		GetWorldTimerManager().SetTimer(attackTimer, this, &AGladiatorEntity::StopAttack, 1.0f, true, attackTimerTime);
	}
}

void AGladiatorEntity::StopAttack()
{
	attack = false;
	attackCollider->Deactivate();
	GetWorldTimerManager().ClearTimer(attackTimer);
}

void AGladiatorEntity::Invincibility()
{
	invincibility = true;
	GetMesh()->SetScalarParameterValueOnMaterials("Activate", 1.f);
	GetWorldTimerManager().ClearTimer(invincibilityTimer);
	GetWorldTimerManager().SetTimer(invincibilityTimer, this, &AGladiatorEntity::StopInvincibility, 1.0f, true, invincibilityTimerTime);
}

void AGladiatorEntity::StopInvincibility()
{
	invincibility = false;
	GetMesh()->SetScalarParameterValueOnMaterials("Activate", 0.f);
}

void AGladiatorEntity::Heal(int heal)
{
	Hurt(-heal);
}

void AGladiatorEntity::Hurt(int dmg)
{
	if (!invincibility) {
		life = FMath::Max(life - dmg, 0);

		BroadcastHurtEvent();
	}
}

void AGladiatorEntity::BroadcastHurtEvent()
{
	hurtEvent.Broadcast();
}

// COLLISIONS

void AGladiatorEntity::OnAttackBeginOverlap( UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
											 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
											 bool bFromSweep, const FHitResult& SweepResult)
{
	if (attackCollider->IsActive())
	{
	}
}