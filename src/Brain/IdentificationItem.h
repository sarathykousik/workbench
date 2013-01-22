#ifndef __IDENTIFICATION_ITEM__H_
#define __IDENTIFICATION_ITEM__H_

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


#include "CaretObject.h"
#include "IdentificationItemDataTypeEnum.h"

namespace caret {
     
    class Brain;
    
    class IdentificationItem : public CaretObject {
        
    protected:
        IdentificationItem(const IdentificationItemDataTypeEnum::Enum itemDataType);
    
    public:
        virtual ~IdentificationItem();
        
        IdentificationItemDataTypeEnum::Enum getItemDataType() const;
        
        bool isEnabledForSelection() const;
        
        void setEnabledForSelection(const bool enabled);
        
        Brain* getBrain();
        
        void setBrain(Brain* brain);
        
        bool isOtherScreenDepthCloserToViewer(const double otherScreenDepth) const;
        
        double getScreenDepth() const;
        
        void setScreenDepth(const double screenDepth);
        
        void getScreenXYZ(double screenXYZ[3]) const;
        
        void setScreenXYZ(const double screenXYZ[3]);
        
        void getModelXYZ(double modelXYZ[3]) const;
        
        void setModelXYZ(const double modelXYZ[3]);
        
        /**
         * @return  Is the identified item valid?
         */
        virtual bool isValid() const = 0;
        
        virtual void reset();
        
    private:
        IdentificationItem(const IdentificationItem&);

        IdentificationItem& operator=(const IdentificationItem&);
        
    public:
        virtual AString toString() const;
        
    protected:
        IdentificationItemDataTypeEnum::Enum itemDataType;
        
        bool enabledForSelection;
        
        Brain* brain;
        
        double screenDepth;
        
        double screenXYZ[3];
        
        double modelXYZ[3];
    };
    
#ifdef __IDENTIFICATION_ITEM_DECLARE__
    // <PLACE DECLARATIONS OF STATIC MEMBERS HERE>
#endif // __IDENTIFICATION_ITEM_DECLARE__

} // namespace
#endif  //__IDENTIFICATION_ITEM__H_