// Copyright kiruru002. All Rights Reserved.

#include "RunScriptCommand.h"

URunScriptCommand::URunScriptCommand()
    : Super()
    , ContinueTick(true)
{

}

UWorld* URunScriptCommand::GetWorld() const
{
    if (!HasAllFlags(RF_ClassDefaultObject) && GetOuter())
    {
        return GetOuter()->GetWorld();
    }
    // If we are a CDO, we must return nullptr instead of calling Outer->GetWorld() to fool UObject::ImplementsGetWorld.
    return nullptr;
}

void URunScriptCommand::RunEvent(const FString& EventWithArguments)
{
    CallFunctionByNameWithArguments(*EventWithArguments, *GLog, nullptr, /*bForceCallWithNonExec=*/ true);
}
