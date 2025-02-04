// Copyright kiruru002. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RunScript/Public/RunScriptCommand.h"
#include "UObject/Object.h"
#include "RunScriptText.generated.h"

// To avoid circular dependencies
class URunScriptRunner;

USTRUCT(Blueprintable, BlueprintType)
struct RUNSCRIPT_API FRunScriptTextExecute
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
    TSubclassOf<URunScriptCommand> RunCommandClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
    FString ArgumentText;

public:

    FRunScriptTextExecute();
};

UCLASS(Blueprintable, BlueprintType)
class RUNSCRIPT_API URunScriptText : public UObject
{

    GENERATED_BODY()

public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
    URunScriptRunner* ScriptRunner;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
    TArray<FRunScriptTextExecute> RunCommands;

#if WITH_EDITORONLY_DATA
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Default")
    FString SourceText;
#endif

public:

    URunScriptText();

    URunScriptCommand* ExecuteLine(int32 LineIndex);

};
