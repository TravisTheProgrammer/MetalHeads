// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "PaperFlipbookComponent.h"
#include "Enums.h"

#include "GameFramework/GameMode.h"
#include "MetalHeadsGameMode.generated.h"

/**
 *  
 */


UCLASS(minimalapi)
class AMetalHeadsGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AMetalHeadsGameMode();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Returns the main camera (first spawned spec pawn)
	static UCameraComponent* GetMainCamera();

	// Rotates a paper2D component to face the camera
	static void RotateOrtho(USceneComponent* object, FRotator camRot);

	// Convienience method to load objects
	template <typename ObjClass>
	static ObjClass* LoadObjFromPath(const FName& Path) {
		if (Path == NAME_None) return NULL;

		return Cast<ObjClass>(StaticLoadObject(ObjClass::StaticClass(), NULL, *Path.ToString()));
	}

	// Turn enums values into strings (from https://wiki.unrealengine.com/Enums_For_Both_C%2B%2B_and_BP )
	template<typename TEnum>
	static FORCEINLINE FString GetEnumValueToString(const FString& Name, TEnum Value)
	{
		const UEnum* enumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
		if (!enumPtr)
		{
			return FString("Invalid");
		}

		return enumPtr->GetEnumName((int32)Value);
	}

	// Turn strings into enum values (again, from the link above. Super useful!)
	template <typename EnumType>
	static FORCEINLINE EnumType GetEnumValueFromString(const FString& EnumName, const FString& String)
	{
		UEnum* Enum = FindObject<UEnum>(ANY_PACKAGE, *EnumName, true);
		if (!Enum)
		{
			return EnumType(0);
		}
		return (EnumType)Enum->FindEnumIndex(FName(*String));
	}
};



