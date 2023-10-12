#include "CScreenComponent.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/Character.h"

UCScreenComponent::UCScreenComponent()
{
	//Fade
	{
		FString path = "WidgetBlueprint'/Game/Widgets/WB_ScreenFade.WB_ScreenFade_C'";

		TSubclassOf<UUserWidget> subclass = ConstructorHelpers::FClassFinder<UUserWidget>(*path).Class;
		Effects.Add(EScreenType::Fade, subclass);
	}
	
}


void UCScreenComponent::BeginPlay()
{
	OwnerCharacter = Cast<ACharacter>(this->GetOwner());
	Super::BeginPlay();

}

void UCScreenComponent::ShowEffect(EScreenType InType)
{
	if (Effects.Contains(InType) == false)
		return;

	APlayerController* controller = Cast<APlayerController>(OwnerCharacter->GetController());
	if (controller == nullptr)
		return;

	UUserWidget* widget = (CreateWidget<UUserWidget>(controller, Effects[InType]));
	widget->AddToViewport();
}