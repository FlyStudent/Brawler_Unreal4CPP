#include "GladiatorPlayer.h"
#include "GladiatorEnemy.h"


#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AGladiatorPlayer::AGladiatorPlayer()
{
#pragma region Set Camera and Controller
	//PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = TEnumAsByte<EAutoReceiveInput::Type>(EAutoReceiveInput::Player0);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
#pragma endregion


///// ADDITIONAL VARIABLE

	// Attack
	invincibilityTimerTime = 2.f;
	changeTargetCooldown = 0.25f;

	// Life
	maxLife = 5;
	damage = 1;
}

void AGladiatorPlayer::BeginPlay()
{
	Super::BeginPlay();

	lockEnemyEvent.AddDynamic(this, &AGladiatorPlayer::DebugPrint);
}

void AGladiatorPlayer::EntityDead()
{
	Super::EntityDead();

	DisableInput(Cast<APlayerController>(GetController()));
}

// Called every frame
void AGladiatorPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (isLocking && orderedEnemies.Num() > 0)
	{
		FVector direction =  orderedEnemies[currentLockEnemy]->GetActorLocation() - GetActorLocation();
		direction = direction.GetSafeNormal();
		direction.Z = -0.5f;
		FRotator rotation = direction.Rotation();
		FRotator curRotation = GetController()->GetControlRotation();

		GetController()->SetControlRotation(FMath::Lerp(curRotation, rotation, 0.05f));
		FRotator viewRotation(0.f, direction.ToOrientationRotator().Yaw, direction.ToOrientationRotator().Roll);
		SetActorRotation(viewRotation);
	}
}

void AGladiatorPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGladiatorPlayer::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGladiatorPlayer::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AGladiatorPlayer::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AGladiatorPlayer::LookUpAtRate);
	
	PlayerInputComponent->BindAction("Attack", EInputEvent::IE_Pressed, this, &AGladiatorPlayer::Attack);
	PlayerInputComponent->BindAction("Shield", EInputEvent::IE_Pressed, this, &AGladiatorPlayer::Shield);
	PlayerInputComponent->BindAction("Shield", EInputEvent::IE_Released, this, &AGladiatorPlayer::StopShield);
	PlayerInputComponent->BindAction("Lock", EInputEvent::IE_Pressed, this, &AGladiatorPlayer::Lock);

	PlayerInputComponent->BindAction("ChangeTargetRight", EInputEvent::IE_Pressed, this, &AGladiatorPlayer::ChangeTargetRight);
	PlayerInputComponent->BindAction("ChangeTargetLeft", EInputEvent::IE_Pressed, this, &AGladiatorPlayer::ChangeTargetLeft);
}

void AGladiatorPlayer::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AGladiatorPlayer::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AGladiatorPlayer::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f) && CanMove())
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AGladiatorPlayer::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f) && CanMove())
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AGladiatorPlayer::Lock()
{
	if (!isLocking) // Locking
	{
		currentLockEnemy = 0;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		BroadcastLockEvent();
	}
	else // Unlocking
	{
		if (orderedEnemies.Num() != 0)
			orderedEnemies[currentLockEnemy]->SetLock(false);

		GetCharacterMovement()->bOrientRotationToMovement = true;
		//CameraBoom->bUsePawnControlRotation = true;
		BroadcastUnlockEvent();
	}

	isLocking = isLocking ? false : true;
}

void AGladiatorPlayer::ChangeTargetRight()
{
	if (!CanChangeTarget())
		return;

	isChangingTarget = true;
	orderedEnemies[currentLockEnemy]->SetLock(false);

	currentLockEnemy = currentLockEnemy == orderedEnemies.Num() -1 ? 0 : currentLockEnemy + 1;
	
	orderedEnemies[currentLockEnemy]->SetLock(true);

	FTimerHandle timer;
	GetWorldTimerManager().SetTimer(timer, this, &AGladiatorPlayer::FreeChangeTarget, 1.f, false, changeTargetCooldown);
}

void AGladiatorPlayer::ChangeTargetLeft()
{
	if (!CanChangeTarget())
		return;

	isChangingTarget = true;
	orderedEnemies[currentLockEnemy]->SetLock(false);

	currentLockEnemy = currentLockEnemy == 0 ? orderedEnemies.Num() - 1 : currentLockEnemy - 1;

	orderedEnemies[currentLockEnemy]->SetLock(true);

	FTimerHandle timer;
	GetWorldTimerManager().SetTimer(timer, this, &AGladiatorPlayer::FreeChangeTarget, 1.f, false, changeTargetCooldown);
}

void AGladiatorPlayer::FreeChangeTarget()
{
	isChangingTarget = false;
}

void AGladiatorPlayer::Shield()
{
	if (!attack)
	{
		usingShield = true;
		defenseCollider->Activate();
	}
}

void AGladiatorPlayer::StopShield()
{
	usingShield = false;
	defenseCollider->Deactivate();
}
