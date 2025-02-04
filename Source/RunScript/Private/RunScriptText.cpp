// Copyright kiruru002. All Rights Reserved.

#include "RunScriptText.h"

FRunScriptTextExecute::FRunScriptTextExecute()
    : RunCommandClass()
    , ArgumentText(TEXT(""))
{
}

URunScriptText::URunScriptText()
    : Super()
    , ScriptRunner(nullptr)
    , RunCommands({})
    , SourceText(TEXT(""))
{

}

URunScriptCommand* URunScriptText::ExecuteLine(int32 LineIndex)
{
    if (RunCommands.IsValidIndex(LineIndex))
    {
        const FRunScriptTextExecute& Command = RunCommands[LineIndex];
        URunScriptCommand* CommandObject = NewObject<URunScriptCommand>(this, Command.RunCommandClass, NAME_None, RF_NoFlags, nullptr);
        CommandObject->ScriptRunner = ScriptRunner;
        CommandObject->RunEvent(*Command.ArgumentText);
        return CommandObject;
    }
    return nullptr;
}
