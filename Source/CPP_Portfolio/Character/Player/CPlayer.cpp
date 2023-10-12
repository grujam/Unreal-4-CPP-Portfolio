#include "Character/Player/CPlayer.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Character/Player/CAnimInstance.h"
#include "Components/CMovementComponent.h"
#include "Components/CEquipmentComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CHitComponent_Player.h"
#include "Components/CResourceComponent.h"
#include "Components/CScreenComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CDodgeComponent.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	//Camera
	{
		SpringArm = this->CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
		SpringArm->SetupAttachment(GetMesh());

		Camera = this->CreateDefaultSubobject<UCameraComponent>("Camera");
		Camera->SetupAttachment(SpringArm);

		SpringArm->SetRelativeLocation(FVector(0, 0, 140));
		SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
		SpringArm->TargetArmLength = 350;
		SpringArm->bDoCollisionTest = true;
		SpringArm->bUsePawnControlRotation = false;
		SpringArm->bEnableCameraLag = true;
	}

	//Actor Component
	{
		MovementComponent = this->CreateDefaultSubobject<UCMovementComponent>("Movement Component");
		MovementComponent->DisableControlRotation();

		EquipmentComponent = this->CreateDefaultSubobject<UCEquipmentComponent>("Equipment Component");

		StateComponent = this->CreateDefaultSubobject<UCStateComponent>("State Component");

		HitComponent = this->CreateDefaultSubobject<UCHitComponent_Player>("Hit Component");

		ResourceComponent = this->CreateDefaultSubobject<UCResourceComponent>("Resource Component");

		DodgeComponent = this->CreateDefaultSubobject<UCDodgeComponent>("Dodge Component");

		ScreenComponent = this->CreateDefaultSubobject<UCScreenComponent>("Screen Component");

	}

	//Skeletal Mesh
	{
		FString path = "SkeletalMesh'/Game/Player/Meshes/BP_Player_Mesh.BP_Player_Mesh'";
		ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMesh(*path);

		GetMesh()->SetSkeletalMesh(skeletalMesh.Object);
		GetMesh()->SetRelativeLocation(FVector(0,0,-90));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}

	// Anim BluePrint
	{
		TSubclassOf<UCAnimInstance> animInstance;
		FString path = "AnimBlueprint'/Game/Player/ABP_CPlayer.ABP_CPlayer_C'";
		animInstance = ConstructorHelpers::FClassFinder<UCAnimInstance>(*path).Class;
		GetMesh()->SetAnimClass(animInstance);
	}

	//Character Movement
	{
		GetCharacterMovement()->MaxWalkSpeed = 400;
	}

	//Widget Class
	{
		FString path = "WidgetBlueprint'/Game/Widgets/WB_Player.WB_Player_C'";
		WidgetClass = ConstructorHelpers::FClassFinder<UUserWidget>(*path).Class;
	}
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	if(!!WidgetClass)
	{
		widget = Cast<UUserWidget>(CreateWidget(GetWorld(), WidgetClass));
		widget->AddToViewport();
	}
}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", MovementComponent, &UCMovementComponent::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveSideways", MovementComponent, &UCMovementComponent::OnMoveSideWays);
	PlayerInputComponent->BindAxis("HorizontalLook", MovementComponent, &UCMovementComponent::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", MovementComponent, &UCMovementComponent::OnVerticalLook);

	PlayerInputComponent->BindAxis("ActionLeftAxis");
	PlayerInputComponent->BindAxis("ActionRightAxis");
	PlayerInputComponent->BindAxis("ActionExtraAxis");
	
	PlayerInputComponent->BindAction("Dash", EInputEvent::IE_Pressed, MovementComponent, &UCMovementComponent::OnDash);
	PlayerInputComponent->BindAction("Dash", EInputEvent::IE_Pressed, ResourceComponent, &UCResourceComponent::Run);
	PlayerInputComponent->BindAction("Dash", EInputEvent::IE_Released, MovementComponent, &UCMovementComponent::OffDash);
	PlayerInputComponent->BindAction("Dash", EInputEvent::IE_Released, ResourceComponent, &UCResourceComponent::Walk);

	PlayerInputComponent->BindAction("LongSword", EInputEvent::IE_Pressed, EquipmentComponent, &UCEquipmentComponent::SetLongSwordMode);

	PlayerInputComponent->BindAction("ActionLeft", EInputEvent::IE_Pressed, EquipmentComponent, &UCEquipmentComponent::LeftPressed);
	PlayerInputComponent->BindAction("ActionRight", EInputEvent::IE_Pressed, EquipmentComponent, &UCEquipmentComponent::RightPressed);
	PlayerInputComponent->BindAction("ActionExtra", EInputEvent::IE_Pressed, EquipmentComponent, &UCEquipmentComponent::ExtraPressed);

	PlayerInputComponent->BindAction("ActionLeft", EInputEvent::IE_Pressed, EquipmentComponent, &UCEquipmentComponent::WaitAction);
	PlayerInputComponent->BindAction("ActionRight", EInputEvent::IE_Pressed, EquipmentComponent, &UCEquipmentComponent::WaitAction);
	PlayerInputComponent->BindAction("ActionExtra", EInputEvent::IE_Pressed, EquipmentComponent, &UCEquipmentComponent::WaitAction);

	PlayerInputComponent->BindAction("Dodge", EInputEvent::IE_Pressed, DodgeComponent, &UCDodgeComponent::Dodge);

	//PlayerInputComponent->BindAction("ActionLeft", EInputEvent::IE_Pressed, EquipmentComponent, &UCEquipmentComponent::DoActionLeft);
	//PlayerInputComponent->BindAction("ActionRight", EInputEvent::IE_Pressed, EquipmentComponent, &UCEquipmentComponent::DoActionRight);
	//PlayerInputComponent->BindAction("ActionExtra", EInputEvent::IE_Pressed, EquipmentComponent, &UCEquipmentComponent::DoActionExtra);

}

void ACPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	UProgressBar* health = Cast<UProgressBar>(widget->GetWidgetFromName("Health"));
	if(!!health)
		health->SetPercent(HitComponent->GetHPPercent());

	UProgressBar* Stamina = Cast<UProgressBar>(widget->GetWidgetFromName("Stamina"));
	if (!!Stamina)
		Stamina->SetPercent(ResourceComponent->GetStaminaPercent());
}

void ACPlayer::TakeDamage(const FPlayerHitData& InHitData, const FVector InAttackerLocation)
{
	HitComponent->Hit(InHitData, InAttackerLocation);
}
