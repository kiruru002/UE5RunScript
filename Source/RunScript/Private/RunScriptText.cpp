// Copyright kiruru002. All Rights Reserved.

#include "RunScriptText.h"
#include "RunScript/Public/RunScriptRunner.h"

FRunScriptTextExecute::FRunScriptTextExecute()
    : RunCommandClass()
    , EventString(TEXT(""))
{
}

URunScriptText::URunScriptText()
    : Super()
    , RunCommands({})
    , SourceText(TEXT(""))
{

}

URunScriptCommand* URunScriptText::ExecuteLine(URunScriptRunner* ScriptRunner, int32 LineIndex, bool& bOutOfRange)
{
    if (RunCommands.IsValidIndex(LineIndex))
    {
        bOutOfRange = false;
        const FRunScriptTextExecute& Command = RunCommands[LineIndex];
        if (Command.RunCommandClass == URunScriptCommand::StaticClass() || !Command.RunCommandClass->IsChildOf(URunScriptCommand::StaticClass()))
        {
            return nullptr;
        }
        URunScriptCommand* CommandObject = NewObject<URunScriptCommand>(ScriptRunner, Command.RunCommandClass, NAME_None, RF_NoFlags, nullptr);
        CommandObject->RunEvent(Command.EventString);
        return CommandObject;
    }
    bOutOfRange = true;
    return nullptr;
}
