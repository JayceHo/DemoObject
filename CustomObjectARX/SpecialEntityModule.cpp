// SpecialEntityModule.cpp : Defines the entry point for the DLL application.
//
#include "stdafx.h"
#include "SpecialEntityModule.h"
#include "SpecialEntity.h"
#include "Ed/EdCommandStack.h"

#include <RxDynamicModule.h>

#ifdef _MANAGED
#pragma managed(push, off)
#endif

ODRX_DEFINE_DYNAMIC_MODULE(CFxSpecialEntityModule);

void CFxSpecialEntityModule::initApp()
{
    CFxSpecialEntity::rxInit();

    // Gets the stack holding all commands in the defined module. 
    OdEdCommandStackPtr pCommandsStack = odedRegCmds();

    // Checks if it contains null reference.
    if (!pCommandsStack.isNull())
    {
        // Register our SPECIAL command.
        pCommandsStack->addCommand(&m_SpecialEntityCmd);
    }
}

void CFxSpecialEntityModule::uninitApp()
{
    CFxSpecialEntity::rxUninit();

    // Gets the stack holding all commands in the defined module. 
    OdEdCommandStackPtr pCommandsStack = odedRegCmds();

    // Checks if it contains null reference.
    if (!pCommandsStack.isNull())
    {
        // Removes command from the commands stack. It is important to remove all commands,
        // when the module is unloaded, which were registered by the module.
        pCommandsStack->removeCmd(&m_SpecialEntityCmd);
    }
}
