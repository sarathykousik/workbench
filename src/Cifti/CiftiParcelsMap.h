#ifndef __CIFTI_PARCELS_MAP_H__
#define __CIFTI_PARCELS_MAP_H__

/*LICENSE_START*/
/*
 *  Copyright 1995-2011 Washington University School of Medicine
 *
 *  http://brainmap.wustl.edu
 *
 *  This file is part of CARET.
 *
 *  CARET is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  CARET is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with CARET; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
/*LICENSE_END*/

#include "CiftiIndexMap.h"

#include "AString.h"
#include "CaretCompact3DLookup.h"
#include "StructureEnum.h"
#include "VolumeSpace.h"
#include "VoxelIJK.h"

#include <map>
#include <set>
#include <vector>

namespace caret
{
    class CiftiParcelsMap : public CiftiIndexMap
    {
    public:
        struct Parcel
        {
            std::map<StructureEnum::Enum, std::set<int64_t> > m_surfaceNodes;
            std::set<VoxelIJK> m_voxelIndices;
            AString m_name;
            bool operator==(const Parcel& rhs) const;
            bool operator!=(const Parcel& rhs) const { return !((*this) == rhs); }
        };
        bool hasVolumeData() const;
        bool hasSurfaceData(const StructureEnum::Enum& structure) const;
        const VolumeSpace& getVolumeSpace() const;
        int64_t getParcelForNode(const int64_t& node, const StructureEnum::Enum& structure) const;
        int64_t getParcelForVoxel(const int64_t* ijk) const;
        std::vector<StructureEnum::Enum> getParcelSurfaceStructures() const;
        const std::vector<Parcel>& getParcels() const { return m_parcels; }
        
        CiftiParcelsMap() { m_haveVolumeSpace = false; m_ignoreVolSpace = false; }
        void addSurface(const int& numberOfNodes, const StructureEnum::Enum& structure);
        void setVolumeSpace(const VolumeSpace& space);
        void addParcel(const Parcel& parcel);
        void clear();
        
        CiftiIndexMap* clone() const { return new CiftiParcelsMap(*this); }
        MappingType getType() const { return PARCELS; }
        int64_t getLength() const { return m_parcels.size(); }
        bool operator==(const CiftiIndexMap& rhs) const;
        void readXML1(QXmlStreamReader& xml);
        void readXML2(QXmlStreamReader& xml);
        void writeXML1(QXmlStreamWriter& xml) const;
        void writeXML2(QXmlStreamWriter& xml) const;
    private:
        std::vector<Parcel> m_parcels;
        VolumeSpace m_volSpace;
        bool m_haveVolumeSpace, m_ignoreVolSpace;//second is needed for parsing cifti-1;
        struct SurfaceInfo
        {
            int64_t m_numNodes;
            std::vector<int64_t> m_lookup;
        };
        CaretCompact3DLookup<int64_t> m_volLookup;
        std::map<StructureEnum::Enum, SurfaceInfo> m_surfInfo;
        static Parcel readParcel1(QXmlStreamReader& xml);
        static Parcel readParcel2(QXmlStreamReader& xml);
        static std::vector<int64_t> readIndexArray(QXmlStreamReader& xml);
    };
}

#endif //__CIFTI_PARCELS_MAP_H__