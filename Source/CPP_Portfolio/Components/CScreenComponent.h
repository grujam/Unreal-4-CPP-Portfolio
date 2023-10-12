#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CScreenComponent.generated.h"


UENUM(BlueprintType)
enum class EScreenType : uint8
{
	Fade, Max
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_PORTFOLIO_API UCScreenComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCScreenComponent();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
		TMap<EScreenType, TSubclassOf<UUserWidget>> Effects;

public:
	UFUNCTION(BlueprintCallable)
		void ShowEffect(EScreenType InType);

private:
	UPROPERTY()
		class ACharacter* OwnerCharacter;
};
