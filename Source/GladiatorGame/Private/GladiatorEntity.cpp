#include "GladiatorEntity.h"

// Sets default values
AGladiatorEntity::AGladiatorEntity()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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