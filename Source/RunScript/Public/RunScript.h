// Copyright kiruru002. All Rights Reserved.

#pragma once

#include "Modules/ModuleManager.h"

class FRunScriptModule : public IModuleInterface
{
public:

    /** IModuleInterface implementation */
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
