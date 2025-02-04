// Copyright kiruru002. All Rights Reserved.


#include "RunScriptRunner.h"
#include "RunScript/Public/RunScriptCommand.h"
#include "Engine/World.h"

URunScriptRunner::URunScriptRunner()
    : Super()
    , bTickEnabled(true)
    , ScriptStack({})
    , CurrentLineIndex(0)
    , CommandSumTickSeconds(0.0f)
    , ScriptSumTickSeconds(0.0f)
{
}

void URunScriptRunner::Tick(float DeltaSeconds)
{
    if (!ScriptStack.IsEmpty())
    {
        ScriptSumTickSeconds += DeltaSeconds;
        URunScriptText* CurrentScript = ScriptStack[0];
        bool bOutOfRange = false;
        if (CurrentCommandObject && CurrentCommandObject->ContinueTick)
        {
            CommandSumTickSeconds += DeltaSeconds;
            CurrentCommandObject->Tick(this, DeltaSeconds);
        }
        else
        {
            CommandSumTickSeconds = 0.0f;
            CurrentCommandObject = CurrentScript->ExecuteLine(this, CurrentLineIndex, bOutOfRange);
        }
        // loop until next tick command
        while (!bOutOfRange && (!CurrentCommandObject || !CurrentCommandObject->ContinueTick))
        {
            CurrentLineIndex++;
            CommandSumTickSeconds = 0.0f;
            CurrentCommandObject = CurrentScript->ExecuteLine(this, CurrentLineIndex, bOutOfRange);
        }
        // finish
        if (bOutOfRange && (!CurrentCommandObject || !CurrentCommandObject->ContinueTick))
        {
            ScriptStack.RemoveAt(0);
            CurrentLineIndex = 0;
            ScriptSumTickSeconds = 0.0f;
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
    if (TextAsset && (bAllowDuplicate || ScriptStack.Find(TextAsset) == INDEX_NONE))
    {
        ScriptStack.Add(TextAsset);
    }
}

void URunScriptRunner::StartScript(URunScriptText* TextAsset, bool bAllowDuplicate)
{
    StackScript(TextAsset, bAllowDuplicate);
}
