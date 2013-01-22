#ifndef __EVENT_IDENTIFICATION_SYMBOL_REMOVAL_H__
#define __EVENT_IDENTIFICATION_SYMBOL_REMOVAL_H__

/*LICENSE_START*/ 
/* 
 *  Copyright 1995-2002 Washington University School of Medicine 
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

#include "Event.h"
#include "StructureEnum.h"

namespace caret {

    class BrainStructure;

    /// Remove all identification symbols
    class EventIdentificationSymbolRemoval : public Event {
        
    public:
        EventIdentificationSymbolRemoval();
        
        EventIdentificationSymbolRemoval(const StructureEnum::Enum structure,
                                         const int32_t nodeNumber);
        
        virtual ~EventIdentificationSymbolRemoval();
        
        bool isRemoveAllSurfaceSymbols() const;
        
        bool isRemoveSurfaceNodeSymbol() const;
        
        StructureEnum::Enum getSurfaceStructure() const;
        
        int32_t getSurfaceNodeNumber() const;
        
    private:
        EventIdentificationSymbolRemoval(const EventIdentificationSymbolRemoval&);
        
        EventIdentificationSymbolRemoval& operator=(const EventIdentificationSymbolRemoval&);
        
        StructureEnum::Enum structure;
        
        int32_t nodeNumber;
    };

} // namespace

#endif // __EVENT_IDENTIFICATION_SYMBOL_REMOVAL_H__