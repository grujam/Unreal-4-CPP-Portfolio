#include "CGameModeBase.h"
#include "Character/Player/CPlayableCharacter.h"


ACGameModeBase::ACGameModeBase()
{
	FString path = "Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'";
	DefaultPawnClass = ConstructorHelpers::FClassFinder<APawn>(*path).Class;
}
