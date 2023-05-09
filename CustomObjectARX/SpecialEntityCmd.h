#pragma once

#include "FxCommand.h"
#include "FxCommandContext.h"

/**
Creates new command.
*/
class CFxSpecialEntityCommand : public OdStaticRxObject < CFxCommand >
{

public:
    ~CFxSpecialEntityCommand();
    /**
    Returns non-localized version of the command name.
    */
    virtual const OdString globalName() const;

    /**
    Returns localized version of the command name.
    */
    virtual const OdString localName() const;

    /**
    Entry point for command execution.

    @return result code (\c RTNORM if command ended successfully)
    */
    virtual int Execute(CFxCommandContext* pCmdCtx);

protected:
    /**
    Protected constructor to disallow instantiation.
    */
    CFxSpecialEntityCommand();
};
