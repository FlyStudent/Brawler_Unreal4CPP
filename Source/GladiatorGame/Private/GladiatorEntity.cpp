
#include "GladiatorEntity.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

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
	attackCollider->Deactivate();

	defenseCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Defense Collider"));
	defenseCollider->SetupAttachment(shieldMesh);
	defenseCollider->Deactivate();
	defenseCollider->SetWorldLocation(FVector(4.f, 2.f, 14.f));
	defenseCollider->SetSphereRadius(50.f);

}

// Called when the game starts or when spawned
void AGladiatorEntity::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGladiatorEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGladiatorEntity::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AGladiatorEntity::Attack()
{
	if (!attack)
	{
		attack = true;
		GetWorldTimerManager().ClearTimer(attackTimer);
		GetWorldTimerManager().SetTimer(attackTimer, this, &AGladiatorEntity::StopAttack, 1.0f, true, attackTimerTime);
	}
}

void AGladiatorEntity::StopAttack()
{
	attack = false;
}