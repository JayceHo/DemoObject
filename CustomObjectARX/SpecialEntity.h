#pragma once

#include "stdafx.h"
#include "DbCircle.h"

class CFxSpecialEntity : public OdDbCircle
{
    static const OdInt16 lastKnownVersion;
    OdInt16 m_nVersion;
    OdInt16 m_nCount;

public:
    ODDB_DECLARE_MEMBERS(CFxSpecialEntity);

    CFxSpecialEntity();
    virtual ~CFxSpecialEntity();

    /**
    Function is called to get the version.

    @return \c m_nVersion.
    */
    OdInt16 getVersion() const;

    /**
    Function is called to set the number of circles to be drawn.

    @param [in] integer value to set the count of circles to be drawn.
    */
    void setCount(OdInt16 n);

    /**
    Function is called to get the number of circles to be drawn.

    @return \c m_nVersion.
    */
    OdInt16 getCount() const;

    /**
    Reads the DWG data of this object.

    @param [in] Pointer to the OdDbDwgFiler object.

    @return \c eOk if successful.
    */
    OdResult dwgInFields(OdDbDwgFiler* pFiler);

    /**
    Writes the DWG data for our new entity.

    @param [in] Pointer to the OdDbDwgFiler object.
    */
    void dwgOutFields(OdDbDwgFiler* pFiler) const;

    /**
    Reads the DXF data for our new entity.

    @param [in] Pointer to the OdDbDxfFiler object.

    @return \c eOk if successful.
    */
    OdResult dxfInFields(OdDbDxfFiler* pFiler);

    /**
    Writes the DXF data for our new entity.

    @param [in] Pointer to the OdDbDxfFiler object.
    */
    void dxfOutFields(OdDbDxfFiler* pFiler) const;

    /**
     Function is called to draw the Special object.

     @param [in] Pointer to the OdGiWorldDraw object.

     @return \c true if the entity has no view-dependent graphics. In other case returns \c false.
     */
    bool subWorldDraw(OdGiWorldDraw* pWd) const;

};
/** \typedef OdSmartPtr<CFxPIEntity> CFxPIEntityPtr
    CFxSpecialEntity smart pointer, used later to create the object
*/
typedef OdSmartPtr<CFxSpecialEntity> CSpecialEntityPtr;
