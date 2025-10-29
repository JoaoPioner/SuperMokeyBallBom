// Fill out your copyright notice in the Description page of Project Settings.


#include "MonkeyBall.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

// Sets default values
AMonkeyBall::AMonkeyBall()
{

    // Don't rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

    // Criar o componente da esfera (o nosso "root component")
    SphereComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereComponent"));
    RootComponent = SphereComponent;

    // Configurar a física (essencial para Monkey Ball)
    SphereComponent->SetSimulatePhysics(true);
    SphereComponent->SetCollisionProfileName(UCollisionProfile::PhysicsActor_ProfileName);

    // Criar o Spring Arm
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent); // Anexar ao SphereComponent
    SpringArm->bEnableCameraLag = true;
    SpringArm->CameraLagSpeed = 5.0f;
    SpringArm->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f)); // Ângulo da câmara

    // Criar a Câmara
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); // Anexar ao SpringArm
}

// Called when the game starts or when spawned
void AMonkeyBall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonkeyBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonkeyBall::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &AMonkeyBall::OnMoveForward);

}

