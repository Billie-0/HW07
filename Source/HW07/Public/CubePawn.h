#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CubePawn.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class HW07_API ACubePawn : public APawn
{
	GENERATED_BODY()

public:
	ACubePawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    UPROPERTY(VisibleAnywhere)
    class UCapsuleComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere)
    class USkeletalMeshComponent* MeshComponent;

    UPROPERTY(VisibleAnywhere)
    class USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere)
    class UCameraComponent* Camera;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* LookAction;

    FVector2D MovementInput;
    FVector2D LookInput;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float MoveSpeed = 500.0f;

    UPROPERTY(EditAnywhere, Category = "Movement")
    float TurnSpeed = 60.0f;

    void Move(const struct FInputActionValue& Value);
    void Look(const struct FInputActionValue& Value);
};
