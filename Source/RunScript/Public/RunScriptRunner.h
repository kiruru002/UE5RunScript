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

    UPROPERTY(EditAnyWhere, BlueprintReadWrite)
    bool bTickEnabled;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite)
    TArray<URunScriptText*> ScriptStack;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite)
    int32 CurrentLineIndex;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite)
    URunScriptCommand* CurrentCommandObject;

    UPROPERTY(EditAnyWhere, BlueprintReadWrite)
    float CommandAccumulatedTickSeconds;

public:

    URunScriptRunner();

    virtual void Tick(float DeltaSeconds) override;
    virtual TStatId GetStatId() const override;
    virtual bool IsTickable() const override;

    void StackScript(URunScriptText* TextAsset, bool bAllowDuplicate);

    UFUNCTION(BlueprintPure = false, Category = "")
    void StartScript(URunScriptText* TextAsset, bool bAllowDuplicate);

};
