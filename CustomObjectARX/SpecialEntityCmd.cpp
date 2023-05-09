#include "stdafx.h"
#include "SpecialEntityCmd.h"
#include "SpecialEntity.h"
#include "StaticRxObject.h"
#include "RxModule.h"
#include "RxDynamicModule.h"
#include "RxDynamicModule.h"
#include "FxSystemServices.h"
#include "FxDocument.h"

#include <DbDatabase.h>
#include <DbBlockTableRecord.h>
#include <DbDictionary.h>

#include "FxFdtCodes.h"

CFxSpecialEntityCommand::CFxSpecialEntityCommand()
{
    GetFxSystemServices()->WriteLine(L"The CustomEntity example. Please type SPECIAL at the command line.");
}

CFxSpecialEntityCommand::~CFxSpecialEntityCommand()
{
}

const OdString  CFxSpecialEntityCommand::globalName() const
{
    // Global command name to be called.
    return ("_SPECIAL");
}

const OdString CFxSpecialEntityCommand::localName() const
{
    // Local command name to be called.
    return ("SPECIAL");
}

int CFxSpecialEntityCommand::Execute(CFxCommandContext* pCmdCtx)
{
    // Get User IO object from command context.
    CFxUserIO* pUserIO = pCmdCtx->GetFxDocument()->GetFxUserIO();

    // Gets the current database. 
    CFxDatabasePtr pDB = pCmdCtx->GetFxDocument()->GetFxDatabase();

    // Creates an object from CFxSpecialEntity type, i.e. a circle.
    CSpecialEntityPtr pMyCirc = CFxSpecialEntity::createObject();
    // Applies database default properties to new object created.
    pMyCirc->setDatabaseDefaults(pDB);
    // Sets circle radius to 2. 
    pMyCirc->setRadius(2.);
    // 5 circles will be drawn. 
    pMyCirc->setCount(5);

    // Add the new object to the active space.
    OdDbBlockTableRecordPtr(pCmdCtx->GetFxDocument()->GetFxDatabase()->GetActiveBlockId().openObject(OdDb::kForWrite))->appendOdDbEntity(pMyCirc);

    // Describes Special command.
    pUserIO->Write(L"SPECIAL command represents a new Custom Entity.");

    // Normal termination.
    return RTNORM;
}
