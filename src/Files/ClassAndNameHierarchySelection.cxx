
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

#define __CLASS_AND_NAME_HIERARCHY_SELECTION_DECLARE__
#include "ClassAndNameHierarchySelection.h"
#undef __CLASS_AND_NAME_HIERARCHY_SELECTION_DECLARE__

#include "Border.h"
#include "BorderFile.h"
#include "CaretAssert.h"
#include "GiftiLabel.h"
#include "GiftiLabelTable.h"

using namespace caret;


    
/**
 * \class caret::ClassAndNameHierarchySelection 
 * \brief Maintains a class and name hierarchy for selection.
 *
 * Some types of data elements have a name that is associated
 * with a class.  Thus 1..N names are mapped 1 class.  For a
 * data type element to be displayed, both its name and its
 * class must be enabled for display.
 */

/**
 * Constructor.
 */
ClassAndNameHierarchySelection::ClassAndNameHierarchySelection()
: CaretObject()
{
    this->classLabelTable = new GiftiLabelTable();
    this->nameLabelTable  = new GiftiLabelTable();
}

/**
 * Destructor.
 */
ClassAndNameHierarchySelection::~ClassAndNameHierarchySelection()
{
    delete this->classLabelTable;
    delete this->nameLabelTable;
}

/**
 * Clear the class/name hierarchy.
 */
void 
ClassAndNameHierarchySelection::clear()
{
    this->classLabelTable->clear();
    this->nameLabelTable->clear();
}

/**
 * @return The class table.
 */
GiftiLabelTable* 
ClassAndNameHierarchySelection::getClassLabelTable()
{
    return this->classLabelTable;
}

/**
 * @return The class table.
 */
const GiftiLabelTable* 
ClassAndNameHierarchySelection::getClassLabelTable() const
{
    return this->classLabelTable;
}

/**
 * @return The name table.
 */
GiftiLabelTable* 
ClassAndNameHierarchySelection::getNameLabelTable()
{
    return this->nameLabelTable;
}

/**
 * @return The name table.
 */
const GiftiLabelTable* 
ClassAndNameHierarchySelection::getNameLabelTable() const
{
    return this->nameLabelTable;
}

/**
 * Set the selected status for EVERYTHING.
 */
void 
ClassAndNameHierarchySelection::setAllSelected(const bool status)
{
    this->nameLabelTable->setSelectionStatusForAllLabels(status);
    this->classLabelTable->setSelectionStatusForAllLabels(status);
}

/**
 * Update this class hierarchy with the border names
 * and classes.
 */
void 
ClassAndNameHierarchySelection::update(BorderFile* borderFile)
{
    bool needToGenerateKeys = false;
    
    const int32_t numBorders = borderFile->getNumberOfBorders();
    for (int32_t i = 0; i < numBorders; i++) {
        const Border* border = borderFile->getBorder(i);
        if (border->isNameOrClassModified()) {
            needToGenerateKeys = true;
        }
    }
    
    if (needToGenerateKeys) {
        this->clear();
        
        for (int32_t i = 0; i < numBorders; i++) {
            Border* border = borderFile->getBorder(i);
            
            /*
             * If the name already exists, addLabel will return the name's key.
             * Otherwise, it will return the key of the existing label with the name.
             */
            const int32_t nameKey = this->nameLabelTable->addLabel(border->getName(),
                                                                   0.0f, 0.0f, 0.0f);
            AString className = border->getClassName();
            if (className.isEmpty()) {
                className = "???";
            }

            /*
             * If the name already exists, addLabel will return the name's key.
             * Otherwise, it will return the key of the existing label with the name.
             */
            const int32_t classKey = this->nameLabelTable->addLabel(className,
                                                                   0.0f, 0.0f, 0.0f);
            
            CaretAssert(nameKey >= 0);
            CaretAssert(classKey >= 0);
            
            border->setNameAndClassKeys(nameKey,
                                        classKey);
        }
    }
}
