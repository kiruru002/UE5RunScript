// Copyright kiruru002. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RunScript/Public/RunScriptCommand.h"
#include "UObject/Object.h"
#include "EditorFramework/AssetImportData.h"
#include "RunScriptText.generated.h"

// To avoid circular dependencies
class URunScriptRunner;

USTRUCT(Blueprintable, BlueprintType)
struct RUNSCRIPT_API FRunScriptTextExecute
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FRunScriptTextExecute")
    TSubclassOf<URunScriptCommand> RunCommandClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FRunScriptTextExecute")
    FString EventString;

public:

    FRunScriptTextExecute();
};

UCLASS(Blueprintable, BlueprintType)
class RUNSCRIPT_API URunScriptText : public UObject
{

    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "URunScriptText")
    TArray<FRunScriptTextExecute> RunCommands;

#if WITH_EDITORONLY_DATA
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "URunScriptText|Editor")
    FString SourceText;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Instanced, Category = "URunScriptText|Editor")
    UAssetImportData* AssetImportData;
#endif

public:

    URunScriptText();

    URunScriptCommand* ExecuteLine(URunScriptRunner* ScriptRunner, int32 LineIndex, bool& bOutOfRange);

#if WITH_EDITORONLY_DATA
    // for reimport
    // UAssetDefinition::GetSourceFiles
    virtual void GetAssetRegistryTags(FAssetRegistryTagsContext Context) const override;
#endif

};
