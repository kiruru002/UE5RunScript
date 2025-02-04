// Copyright kiruru002. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RunScriptCompiler.generated.h"

UCLASS()
class RUNSCRIPTEDITOR_API URunScriptCompiler : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintPure = false, Category = "URunScriptCompiler")
    static UClass* FindClassByAssetName(FString AssetName, UClass* ParentClass);

    UFUNCTION(BlueprintPure = false, Category = "URunScriptCompiler")
    static void MapBlueprintAssetsByClass(UClass* ParentClass, TMap<FString, UClass*>& OutClasses);

};
