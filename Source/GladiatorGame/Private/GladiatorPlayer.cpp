#include "GladiatorPlayer.h"

#include "HeadMountedDisplayFunctionLibrary.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SphereComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AGladiatorPlayer::AGladiatorPlayer()
{
	//PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = TEnumAsByte<EAutoReceiveInput::Type>(EAutoReceiveInput::Player0);
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 60.f);

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
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


///// ADDITIONAL VARIABLE

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

	// Attack

	attackTimerTime = 0.3f;

	// Life
	life = 5;
}

// Called every frame
void AGladiatorPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
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
}

void AGladiatorPlayer::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AGladiatorPlayer::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
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

void AGladiatorPlayer::Attack()
{
	if (CanMove())
	{
		attack = true;

		attackCollider->Activate();

		GetWorldTimerManager().ClearTimer(attackTimer);
		GetWorldTimerManager().SetTimer(attackTimer, this, &AGladiatorPlayer::StopAttack, 1.0f, true, attackTimerTime);
	}	
}

void AGladiatorPlayer::StopAttack()
{
	attackCollider->Deactivate();
	attack = false;
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
