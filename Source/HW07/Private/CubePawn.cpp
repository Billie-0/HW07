#include "CubePawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Components/CapsuleComponent.h" // UCapsuleComponent 정의를 포함
#include "GameFramework/SpringArmComponent.h" // USpringArmComponent 정의를 포함
#include "Camera/CameraComponent.h" // UCameraComponent 정의를 포함

ACubePawn::ACubePawn()
{
	PrimaryActorTick.bCanEverTick = true;

    // Root 설정
    CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
    if (CollisionComponent)
    {
        RootComponent = Cast<USceneComponent>(CollisionComponent);
    }
    CollisionComponent->SetSimulatePhysics(false);

    // 스켈레탈 메시 
    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetSimulatePhysics(false);

    // 스프링암
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(MeshComponent);
    SpringArm->TargetArmLength = 300.f;
    SpringArm->bUsePawnControlRotation = true;

    // 카메라
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

void ACubePawn::BeginPlay()
{
	Super::BeginPlay();

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(DefaultMappingContext, 0);
        }
    }
}

void ACubePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!LookInput.IsZero())
    {
        float YawInput = LookInput.X;

        FRotator RotationDelta = FRotator(0.f, YawInput * TurnSpeed * DeltaTime, 0.f);
        AddActorLocalRotation(RotationDelta);
    }
}

void ACubePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACubePawn::Move);
        Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACubePawn::Look);
    }
}

void ACubePawn::Move(const FInputActionValue& Value)
{
    MovementInput = Value.Get<FVector2D>();

    FVector Forward = GetActorForwardVector();
    FVector Right = GetActorRightVector();

    FVector Direction = Forward * MovementInput.Y + Right * MovementInput.X;
    Direction.Z = 0.0f;

    AddActorLocalOffset(Direction * MoveSpeed * GetWorld()->GetDeltaSeconds(), true);
}

void ACubePawn::Look(const FInputActionValue& Value)
{
    LookInput = Value.Get<FVector2D>();
}
