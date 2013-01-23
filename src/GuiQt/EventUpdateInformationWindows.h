#ifndef __EVENT_UPDATE_INFORMATION_WINDOWS_H__
#define __EVENT_UPDATE_INFORMATION_WINDOWS_H__

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

namespace caret {

    class BrainStructure;
    
    /// Request display of text in the information window(s).
    class EventUpdateInformationWindows : public Event {
        
    public:
        EventUpdateInformationWindows();
        
        virtual ~EventUpdateInformationWindows();

        EventUpdateInformationWindows* setNotImportant();
        
        bool isImportant() const;
        
    private:
        EventUpdateInformationWindows(const EventUpdateInformationWindows&);
        
        EventUpdateInformationWindows& operator=(const EventUpdateInformationWindows&);

        bool m_important;
    };

} // namespace

#endif // __EVENT_UPDATE_INFORMATION_WINDOWS_H__