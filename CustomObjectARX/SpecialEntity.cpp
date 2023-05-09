// SpecialEntity.cpp: implementation of the CFxSpecialEntity class.
//

#include "stdafx.h"
#include "SpecialEntity.h"
#include "DbFiler.h"
#include "Gi/GiWorldDraw.h"
#include "DbProxyEntity.h"
#include "DbHatch.h"
#include "Ge/GeCircArc2d.h"


ODRX_DXF_DEFINE_MEMBERS(CFxSpecialEntity,                              // class name
    OdDbCircle,                                    // parent class name
    DBOBJECT_CONSTR,                               // creation macro
    OdDb::kMReleaseCurrent,                        // DWG version
    OdDb::kMReleaseCurrent,                        // maintenance release version 
    OdDbProxyEntity::kAllAllowedBits,              // proxy flags
    CSPECIALENTITY,                                // DXF Name
    SPECIALObjs | Description: Example Purposes)  // Application Name

    const OdInt16 CFxSpecialEntity::lastKnownVersion = 1;

CFxSpecialEntity::CFxSpecialEntity()
    : m_nVersion(lastKnownVersion)
    , m_nCount(4)
{
    setRadius(1.);
}

CFxSpecialEntity::~CFxSpecialEntity()
{
}

OdInt16 CFxSpecialEntity::getVersion() const

{
    assertReadEnabled();
    return m_nVersion;
}

void CFxSpecialEntity::setCount(OdInt16 n)
{
    assertWriteEnabled();
    m_nCount = n;
}

OdInt16 CFxSpecialEntity::getCount() const
{
    assertReadEnabled();
    return m_nCount;
}

OdResult CFxSpecialEntity::dwgInFields(OdDbDwgFiler* pFiler)
{
    OdResult res = OdDbCircle::dwgInFields(pFiler);
    if (res != eOk)
    {
        return res;
    }
    m_nVersion = pFiler->rdInt16();
    if (m_nVersion > lastKnownVersion)
    {
        return eMakeMeProxy;
    }

    m_nCount = pFiler->rdInt16();
    return eOk;
}

void CFxSpecialEntity::dwgOutFields(OdDbDwgFiler* pFiler) const
{
    OdDbCircle::dwgOutFields(pFiler);
    pFiler->wrInt16(m_nVersion);
    pFiler->wrInt16(m_nCount);
}

OdResult CFxSpecialEntity::dxfInFields(OdDbDxfFiler* pFiler)
{
    OdResult res = OdDbCircle::dxfInFields(pFiler);
    if (res != eOk)
        return res;
    if (!pFiler->atSubclassData(desc()->name()))
        return eBadDxfSequence;

    while (!pFiler->atEOF())
    {
        int nCode = pFiler->nextItem();
        switch (nCode)
        {
        case 70:
            m_nVersion = pFiler->rdInt16();
            if (m_nVersion > lastKnownVersion)
            {
                return eMakeMeProxy;
            }
            break;
        case 71:
            m_nCount = pFiler->rdInt16();
            break;
        }
    }
    return eOk;
}

void CFxSpecialEntity::dxfOutFields(OdDbDxfFiler* pFiler) const
{
    OdDbCircle::dxfOutFields(pFiler);
    pFiler->wrSubclassMarker(desc()->name());
    pFiler->wrInt16(70, m_nVersion);
    pFiler->wrInt16(71, m_nCount);
}

// Changed worldDraw to subWorldDraw, because worldDraw can't be overwritten anymore. cK 100621.
bool CFxSpecialEntity::subWorldDraw(OdGiWorldDraw* pWd) const
{
    assertReadEnabled();
    OdGePoint3d ptCenter(center());
    OdGeVector3d vNormal(normal());
    double dRadius = radius();
    int nCount = m_nCount;

    OdDbHatchPtr pHatch = OdDbHatch::createObject();
    // Set the hatch properties.
    pHatch->setPropertiesFrom(this);
    pHatch->setAssociative(false);
    pHatch->setPattern(OdDbHatch::kPreDefined, "ANGLE");
    pHatch->setHatchStyle(OdDbHatch::kNormal);
    EdgeArray edgePtrs;

    if (nCount < 1)
    {
        pWd->geometry().circle(ptCenter, dRadius, vNormal);
        OdGeCircArc2d* cirArc = new OdGeCircArc2d(OdGePoint2d(ptCenter.x, ptCenter.y), dRadius);
        edgePtrs.append(cirArc);
        pHatch->appendLoop(OdDbHatch::kDefault, edgePtrs);
    }
    else
    {
        OdGeVector3d vDisp(radius(), 0., 0.);
        double step = Oda2PI / nCount;
        while (nCount--)
        {
            OdGePoint3d ptC(ptCenter + vDisp);
            pWd->geometry().circle(ptC, dRadius, vNormal);
            vDisp.rotateBy(step, vNormal);
            OdGeCircArc2d* cirArc = new OdGeCircArc2d(OdGePoint2d(ptC.x, ptC.y), dRadius);
            edgePtrs.resize(0);
            edgePtrs.append(cirArc);
            pHatch->appendLoop(OdDbHatch::kDefault, edgePtrs);
        }
    }
    pHatch->worldDraw(pWd);
    return true;
}
