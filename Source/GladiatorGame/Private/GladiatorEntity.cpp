#include "GladiatorEntity.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
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
	weaponMesh->SetupAttachment(GetMesh(), "WeaponPoint");

	shieldMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShieldMesh"));
	shieldMesh->SetupAttachment(GetMesh(), "DualWeaponPoint");

	GetMesh()->SetWorldLocation(FVector(0.f, 0.f, -70.f));

	// Collider
	attackCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Attack Collider"));
	attackCollider->SetupAttachment(weaponMesh);
	attackCollider->SetWorldLocation(FVector(0.f, 60.f, 0.f));

	// ParticleSystem
	bloodParticleSystem = CreateDefaultSubobject<UParticleSystem>(TEXT("Blood Particle System"));
}

void AGladiatorEntity::BeginPlay()
{
	Super::BeginPlay();

	life = maxLife;

	attackCollider->Deactivate();

	attackCollider->OnComponentBeginOverlap.AddDynamic(this, &AGladiatorEntity::OnAttackBeginOverlap);

	hurtEvent.AddDynamic(this, &AGladiatorEntity::Invincibility);
	hurtEvent.AddDynamic(this, &AGladiatorEntity::CheckIsAlive);
	hurtEvent.AddDynamic(this, &AGladiatorEntity::EmitBlood);
}

void AGladiatorEntity::CheckIsAlive()
{
	if (!IsAlive())
		EntityDead();
}

void AGladiatorEntity::EntityDead() 
{
	GetCharacterMovement()->Deactivate();
	GetCharacterMovement()->DisableMovement();
}

void AGladiatorEntity::Attack()
{
	GetController()->StopMovement();
	attack = true;
}

void AGladiatorEntity::StopAttack()
{
	attack = attackBlocked = false;
}

void AGladiatorEntity::AttackBlocked()
{
	attackBlocked = true;
}

void AGladiatorEntity::BeginDamage()
{
	attackCollider->Activate();
}

void AGladiatorEntity::StopDamage()
{
	attackCollider->Deactivate();
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

FVector AGladiatorEntity::GetShieldForward() const
{ 
	return shieldMesh->GetRightVector(); 
}

void AGladiatorEntity::Hurt(int dmg)
{
	if (!invincibility) 
	{
		life = FMath::Max(life - dmg, 0);

		BroadcastHurtEvent();
	}
}

void AGladiatorEntity::EmitBlood()
{
	UGameplayStatics::SpawnEmitterAttached(bloodParticleSystem, GetMesh(), "b_Beard");
}

void AGladiatorEntity::BroadcastHurtEvent()
{
	hurtEvent.Broadcast();
}

void AGladiatorEntity::OnAttackBeginOverlap( UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
											 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
											 bool bFromSweep, const FHitResult& SweepResult)
{

	if (attackCollider->IsActive())
	{
		auto entity = Cast<AGladiatorEntity>(OtherActor);

		if (entity && entity->IsAlive() && entity != this)
		{
			entity->Hurt(damage);
		}
	}
}