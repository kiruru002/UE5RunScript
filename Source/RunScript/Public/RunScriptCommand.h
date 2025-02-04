// Copyright kiruru002. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "RunScriptCommand.generated.h"

// To avoid circular dependencies
class URunScriptRunner;

UCLASS(BlueprintType, Blueprintable)
class RUNSCRIPT_API URunScriptCommand : public UObject
{

    GENERATED_BODY()

public:

    UPROPERTY(EditAnyWhere, BlueprintReadWrite)
    bool ContinueTick;

public:

    URunScriptCommand();
    UWorld* GetWorld() const override;

    UFUNCTION(BlueprintPure = false, Category = "URunScriptCommand")
    void RunEvent(const FString& EventWithArguments);

    UFUNCTION(BlueprintImplementableEvent, Category = "URunScriptCommand")
    void Tick(URunScriptRunner* ScriptRunner, float DeltaSeconds);

};
