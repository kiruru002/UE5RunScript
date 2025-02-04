// Copyright kiruru002. All Rights Reserved.

#include "RunScriptText.h"
#include "RunScript/Public/RunScriptRunner.h"
#include "UObject/AssetRegistryTagsContext.h"

FRunScriptTextExecute::FRunScriptTextExecute()
    : RunCommandClass()
    , EventString(TEXT(""))
{
}

URunScriptText::URunScriptText()
    : Super()
    , RunCommands({})
    , SourceText(TEXT(""))
    , AssetImportData()
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

#if WITH_EDITORONLY_DATA
void URunScriptText::GetAssetRegistryTags(FAssetRegistryTagsContext Context) const
{
    if (AssetImportData)
    {
        Context.AddTag(FAssetRegistryTag(UObject::SourceFileTagName(), AssetImportData->GetSourceData().ToJson(), FAssetRegistryTag::TT_Hidden));
    }
    Super::GetAssetRegistryTags(Context);
}
#endif
