// Copyright kiruru002. All Rights Reserved.


#include "RunScriptRunner.h"
#include "RunScript/Public/RunScriptCommand.h"
#include "Engine/World.h"

URunScriptRunner::URunScriptRunner()
    : Super()
    , bTickEnabled(true)
    , ScriptStack({})
    , CurrentLineIndex(0)
    , CommandAccumulatedTickSeconds(0.0f)
{
}

void URunScriptRunner::Tick(float DeltaSeconds)
{
    if (!ScriptStack.IsEmpty())
    {
        URunScriptText* CurrentScript = ScriptStack[0];
        if (IsValid(CurrentCommandObject))
        {
            CommandAccumulatedTickSeconds += DeltaSeconds;
            CurrentCommandObject->Tick(DeltaSeconds);
        }
        else
        {
            CommandAccumulatedTickSeconds = 0.0f;
            CurrentCommandObject = CurrentScript->ExecuteLine(CurrentLineIndex);
        }
        // loop until next tick command
        while (CurrentCommandObject && !CurrentCommandObject->ContinueTick)
        {
            CurrentLineIndex++;
            CommandAccumulatedTickSeconds = 0.0f;
            CurrentCommandObject = CurrentScript->ExecuteLine(CurrentLineIndex);
        }
        // finish
        if (!IsValid(CurrentCommandObject))
        {
            ScriptStack.RemoveAt(0);
            CurrentLineIndex = 0;
        }
    }
}

TStatId URunScriptRunner::GetStatId() const
{
    RETURN_QUICK_DECLARE_CYCLE_STAT(URunScriptRunner, STATGROUP_Tickables);
}

bool URunScriptRunner::IsTickable() const
{
    return bTickEnabled;
}

void URunScriptRunner::StackScript(URunScriptText* TextAsset, bool bAllowDuplicate)
{
    if (bAllowDuplicate || ScriptStack.Find(TextAsset) == INDEX_NONE)
    {
        TextAsset->ScriptRunner = this;
        ScriptStack.Add(TextAsset);
    }
}

void URunScriptRunner::StartScript(URunScriptText* TextAsset, bool bAllowDuplicate)
{
    StackScript(TextAsset, bAllowDuplicate);
}
