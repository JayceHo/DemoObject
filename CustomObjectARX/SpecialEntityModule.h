#pragma once

#include <RxModule.h>
#include <StaticRxObject.h>
#include "SpecialEntityCmd.h"

/**
Creates a new module for  SPECIAL command.
*/
class CFxSpecialEntityModule : public OdRxModule
{
public:
    ~CFxSpecialEntityModule() {}

protected:
    CFxSpecialEntityModule() {}

    /**
    Called when the module is loaded to perform all required initialization steps.
    */
    virtual void initApp();
    /**
    Called when the module is unloaded to perform all required uninitialization steps.
    */
    virtual void uninitApp();

private:
    /**
    Object from type CFxSpecialEntityCommand is created. It represents the new command.
    */
    OdStaticRxObject<CFxSpecialEntityCommand> m_SpecialEntityCmd;
};
