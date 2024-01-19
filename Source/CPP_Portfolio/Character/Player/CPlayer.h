#pragma once

#include "CoreMinimal.h"
#include "CPlayableCharacter.h"
#include "Character/Interface/IDamageable.h"
#include "Monster/Actions/CMonsterActionStructures.h"
#include "CPlayer.generated.h"

UCLASS()
class CPP_PORTFOLIO_API ACPlayer
	: public ACPlayableCharacter,
	  public IIDamageable
{
	GENERATED_BODY()

public:
	ACPlayer();

public:
	UPROPERTY(VisibleAnywhere)
		class UCEquipmentComponent* EquipmentComponent;

	UPROPERTY(VisibleAnywhere)
		class UCStateComponent* StateComponent;

	UPROPERTY(VisibleAnywhere)
		class UCHitComponent_Player* HitComponent;

	UPROPERTY(VisibleAnywhere)
		class UCResourceComponent* ResourceComponent;

	UPROPERTY(VisibleAnywhere)
		class UCDodgeComponent* DodgeComponent;

	UPROPERTY(VisibleAnywhere)
		class UCScreenComponent* ScreenComponent;

	UPROPERTY(VisibleAnywhere)
		class UCIKComponent_Human* IKComponent;

	UPROPERTY(VisibleAnywhere)
		TSubclassOf<class UUserWidget> WidgetClass;

private:
	class UUserWidget* widget;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaSeconds) override;


public:
	void TakeDamage(const FPlayerHitData& InHitData, const FVector InAttackerLocation) override;
};
