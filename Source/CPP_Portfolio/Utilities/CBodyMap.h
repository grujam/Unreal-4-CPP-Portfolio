#pragma once

#include "CoreMinimal.h"
//
//class CPP_PORTFOLIO_API CBodyMap
//{
//public:
//	UFUNCTION(BlueprintCallable)
//		static CBodyMap* Get();
//
//private:
//	CBodyMap();
//	static TSharedPtr<CBodyMap> BodyMap;
//
//public:
//	UPROPERTY(BlueprintReadOnly)
//		TMap<FString, FString> Map;
//};

class CPP_PORTFOLIO_API CBodyMap
{
private:
	CBodyMap();

public:
	UPROPERTY(BlueprintReadOnly)
		static const TMap<FString, FString> Map;
};
