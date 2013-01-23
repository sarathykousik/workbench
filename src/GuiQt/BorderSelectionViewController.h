#ifndef __BORDER_SELECTION_VIEW_CONTROLLER__H_
#define __BORDER_SELECTION_VIEW_CONTROLLER__H_

/*LICENSE_START*/
/*
 * Copyright 2012 Washington University,
 * All rights reserved.
 *
 * Connectome DB and Connectome Workbench are part of the integrated Connectome 
 * Informatics Platform.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the names of Washington University nor the
 *      names of its contributors may be used to endorse or promote products
 *      derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR  
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
 * SUBSTITUTE GOODS OR  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE.
 */
/*LICENSE_END*/

#include <stdint.h>
#include <set>

#include <QWidget>

#include "DisplayGroupEnum.h"
#include "EventListenerInterface.h"
#include "SceneableInterface.h"

class QCheckBox;
class QComboBox;
class QDoubleSpinBox;


namespace caret {

    class GroupAndNameHierarchyViewController;
    class DisplayGroupEnumComboBox;
    class EnumComboBoxTemplate;
    class WuQTabWidget;
    
    class BorderSelectionViewController : public QWidget, public EventListenerInterface, public SceneableInterface {
        
        Q_OBJECT

    public:
        BorderSelectionViewController(const int32_t browserWindowIndex,
                              QWidget* parent = 0);
        
        virtual ~BorderSelectionViewController();
        
        void receiveEvent(Event* event);
        
        virtual SceneClass* saveToScene(const SceneAttributes* sceneAttributes,
                                        const AString& instanceName);
        
        virtual void restoreFromScene(const SceneAttributes* sceneAttributes,
                                      const SceneClass* sceneClass);
        
    private slots:
        void processBorderSelectionChanges();
        
        void processSelectionChanges();
        
        void borderDisplayGroupSelected(const DisplayGroupEnum::Enum);
        
        void processAttributesChanges();
        
    private:
        BorderSelectionViewController(const BorderSelectionViewController&);

        BorderSelectionViewController& operator=(const BorderSelectionViewController&);

        void updateBorderViewController();
        
        void updateOtherBorderViewControllers();
        
        QWidget* createSelectionWidget();
        
        QWidget* createAttributesWidget();
        
        int32_t m_browserWindowIndex;
        
        GroupAndNameHierarchyViewController* m_borderClassNameHierarchyViewController;
        
        QCheckBox* m_bordersDisplayCheckBox;
        
        QCheckBox* m_bordersContralateralCheckBox;
        
        DisplayGroupEnumComboBox* m_bordersDisplayGroupComboBox;

        QComboBox* m_drawTypeComboBox;
        
        EnumComboBoxTemplate* m_coloringTypeComboBox;
        
        QDoubleSpinBox* m_lineWidthSpinBox;
        
        QDoubleSpinBox* m_pointSizeSpinBox;
        
        WuQTabWidget* m_tabWidget;
        
        static std::set<BorderSelectionViewController*> allBorderSelectionViewControllers;
    };
    
#ifdef __BORDER_SELECTION_VIEW_CONTROLLER_DECLARE__
    std::set<BorderSelectionViewController*> BorderSelectionViewController::allBorderSelectionViewControllers;
#endif // __BORDER_SELECTION_VIEW_CONTROLLER_DECLARE__

} // namespace
#endif  //__BORDER_SELECTION_VIEW_CONTROLLER__H_