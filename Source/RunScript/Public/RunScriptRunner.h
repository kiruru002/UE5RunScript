// Copyright kiruru002. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RunScript/Public/RunScriptText.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Tickable.h"
#include "RunScriptRunner.generated.h"

UCLASS(BlueprintType)
class RUNSCRIPT_API URunScriptRunner : public UGameInstanceSubsystem, public FTickableGameObject
{
    GENERATED_BODY()

public:

    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "URunScriptRunner")
    bool bTickEnabled;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "URunScriptRunner")
    TArray<URunScriptText*> ScriptStack;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "URunScriptRunner")
    int32 CurrentLineIndex;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "URunScriptRunner")
    URunScriptCommand* CurrentCommandObject;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "URunScriptRunner")
    float CommandSumTickSeconds;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "URunScriptRunner")
    float ScriptSumTickSeconds;

public:

    URunScriptRunner();

    virtual void Tick(float DeltaSeconds) override;
    virtual TStatId GetStatId() const override;
    virtual bool IsTickable() const override;

    void StackScript(URunScriptText* TextAsset, bool bAllowDuplicate);

    UFUNCTION(BlueprintPure = false, Category = "URunScriptRunner")
    void StartScript(URunScriptText* TextAsset, bool bAllowDuplicate);

};
