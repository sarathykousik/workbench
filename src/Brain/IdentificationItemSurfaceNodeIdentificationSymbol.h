#ifndef __IDENTIFICATION_ITEM_SURFACE_NODE_IDENTIFICATION_SYMBOL__H_
#define __IDENTIFICATION_ITEM_SURFACE_NODE_IDENTIFICATION_SYMBOL__H_

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


#include "IdentificationItem.h"

namespace caret {

    class Surface;
    
    class IdentificationItemSurfaceNodeIdentificationSymbol : public IdentificationItem {
        
    public:
        IdentificationItemSurfaceNodeIdentificationSymbol();
        
        virtual ~IdentificationItemSurfaceNodeIdentificationSymbol();
        
        virtual bool isValid() const;
        
        Surface* getSurface();
        
        const Surface* getSurface() const;
        
        void setSurface(Surface* surface);
        
        int32_t getNodeNumber() const;
        
        void setNodeNumber(const int32_t nodeNumber);
        
        virtual void reset();
        
        virtual AString toString() const;
    private:
        IdentificationItemSurfaceNodeIdentificationSymbol(const IdentificationItemSurfaceNodeIdentificationSymbol&);

        IdentificationItemSurfaceNodeIdentificationSymbol& operator=(const IdentificationItemSurfaceNodeIdentificationSymbol&);
        
    public:
    private:
        Surface* surface;
        
        int32_t nodeNumber;
    };
    
#ifdef __IDENTIFICATION_ITEM_SURFACE_NODE_IDENTIFICATION_SYMBOL_DECLARE__
    // <PLACE DECLARATIONS OF STATIC MEMBERS HERE>
#endif // __IDENTIFICATION_ITEM_SURFACE_NODE_IDENTIFICATION_SYMBOL_DECLARE__

} // namespace
#endif  //__IDENTIFICATION_ITEM_SURFACE_NODE_IDENTIFICATION_SYMBOL__H_