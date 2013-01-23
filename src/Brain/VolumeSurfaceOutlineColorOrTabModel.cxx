
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

#define __VOLUME_SURFACE_OUTLINE_COLOR_OR_TAB_MODEL_DECLARE__
#include "VolumeSurfaceOutlineColorOrTabModel.h"
#undef __VOLUME_SURFACE_OUTLINE_COLOR_OR_TAB_MODEL_DECLARE__

#include "BrainConstants.h"
#include "BrowserTabContent.h"
#include "CaretAssert.h"
#include "EventBrowserTabGet.h"
#include "EventManager.h"
#include "SceneClass.h"

using namespace caret;


    
/**
 * \class caret::VolumeSurfaceOutlineColorOrTabModel 
 * \brief Model for selection of Color or Tab for Surface Outline
 *
 * Allows selection of a color or a browser tab for volume surface
 * outline.  If a color is selected, the surface outline is drawn
 * in that color.  If a browser tab is selected, the surface outline
 * is drawn in the current coloring for the selected surface using
 * the coloring assigned to the surface in the selected browser tab.
 *
 * Note: Only valid browser tabs are available for selection.
 */

/**
 * Constructor.
 */
VolumeSurfaceOutlineColorOrTabModel::VolumeSurfaceOutlineColorOrTabModel()
: CaretObject()
{
    m_selectedItem = NULL;
    m_previousSelectedItemIndex = -1;
    
    std::vector<CaretColorEnum::Enum> allColors;
    CaretColorEnum::getAllEnums(allColors);
    for (std::vector<CaretColorEnum::Enum>::iterator iter = allColors.begin();
         iter != allColors.end();
         iter++) {
        Item* item = new Item(*iter);
        m_colorItems.push_back(item);
    }
    
    m_browserTabItems.resize(BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS, 
                                 NULL);
    for (int32_t i = 0; i < BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS; i++) {
        Item* item = new Item(i);
        m_browserTabItems[i] = item;
    }
}

/**
 * Destructor.
 */
VolumeSurfaceOutlineColorOrTabModel::~VolumeSurfaceOutlineColorOrTabModel()
{
    for (std::vector<Item*>::iterator iter = m_colorItems.begin();
         iter != m_colorItems.end();
         iter++) {
        Item* item = *iter;
        delete item;
    }
    m_colorItems.clear();
    
    for (std::vector<Item*>::iterator iter = m_browserTabItems.begin();
         iter != m_browserTabItems.end();
         iter++) {
        Item* item = *iter;
        delete item;
    }
    m_browserTabItems.clear();
}

/**
 * Copy the given volume surface outline color or tab model.
 * @param modelToCopy
 *    Model that is copied.
 */
void 
VolumeSurfaceOutlineColorOrTabModel::copyVolumeSurfaceOutlineColorOrTabModel(VolumeSurfaceOutlineColorOrTabModel* modelToCopy)
{
    switch (getSelectedItem()->getItemType()) {
        case VolumeSurfaceOutlineColorOrTabModel::Item::ITEM_TYPE_COLOR:
            setColor(modelToCopy->getSelectedItem()->getColor());
            break;
        case VolumeSurfaceOutlineColorOrTabModel::Item::ITEM_TYPE_BROWSER_TAB:
            setBrowserTabIndex(modelToCopy->getSelectedItem()->getBrowserTabIndex());
            break;
    }
}

/**
 * @return All of the valid items for this model.
 */
std::vector<VolumeSurfaceOutlineColorOrTabModel::Item*> 
VolumeSurfaceOutlineColorOrTabModel::getValidItems()
{
    std::vector<Item*> items;

    /*
     * Limit to valid tabs
     */
    for (std::vector<Item*>::iterator iter = m_browserTabItems.begin();
         iter != m_browserTabItems.end();
         iter++) {
        Item* item = *iter;
        if (item->isValid()) {
            items.push_back(item);
        }        
    }
    
    /*
     * All color items are valid
     */
    for (std::vector<Item*>::iterator iter = m_colorItems.begin();
         iter != m_colorItems.end();
         iter++) {
        Item* item = *iter;
        items.push_back(item);
    }
    
    return items;    
}

/**
 * @return Pointer to selected item (NULL if selection
 * is invalid.
 */
VolumeSurfaceOutlineColorOrTabModel::Item* 
VolumeSurfaceOutlineColorOrTabModel::getSelectedItem()
{
    std::vector<Item*> allItems = getValidItems();
    const int32_t numItems = static_cast<int32_t>(allItems.size());
    bool foundSelctedItem = false;
    for (int32_t i = 0; i < numItems; i++) {
        if (allItems[i] == m_selectedItem) {
            foundSelctedItem = true;
            m_previousSelectedItemIndex = i;
            break;
        }
    }
    
    if (foundSelctedItem == false) {
        m_selectedItem = NULL;
    }
    
    if (m_selectedItem == NULL) {
        if (m_previousSelectedItemIndex >= 0) {
            if (m_previousSelectedItemIndex >= numItems) {
                m_previousSelectedItemIndex = numItems - 1;
            }
        }
        else {
            if (numItems > 0) {
                m_previousSelectedItemIndex = 0;
            }
        }

        if (m_previousSelectedItemIndex >= 0) {
            m_selectedItem = allItems[m_previousSelectedItemIndex];
        }
    }
    
    return m_selectedItem;
}

/**
 * Set the selected item.
 * @param item
 *   New selected item.
 */
void 
VolumeSurfaceOutlineColorOrTabModel::setSelectedItem(Item* item)
{
    m_selectedItem = item;
    std::vector<Item*> allItems = getValidItems();
    const int32_t numItems = static_cast<int32_t>(allItems.size());
    for (int32_t i = 0; i < numItems; i++) {
        if (allItems[i] == m_selectedItem) {
            m_previousSelectedItemIndex = i;
            break;
        }
    }
}

/**
 * Set the selection to the given color.
 * @param color
 *   Color that is to be selected.
 */
void 
VolumeSurfaceOutlineColorOrTabModel::setColor(const CaretColorEnum::Enum color)
{
    std::vector<Item*> allItems = getValidItems();
    const int32_t numItems = static_cast<int32_t>(allItems.size());
    for (int32_t i = 0; i < numItems; i++) {
        if (allItems[i]->getItemType() == Item::ITEM_TYPE_COLOR) {
            if (allItems[i]->getColor() == color) {
                setSelectedItem(allItems[i]);
                break;
            }
        }
    }
}

/**
 * Set the selection to the given browser tab.
 * @param browserTabIndex
 *    Index of browser tab for selection.
 */
void 
VolumeSurfaceOutlineColorOrTabModel::setBrowserTabIndex(const int32_t browserTabIndex)
{
    std::vector<Item*> allItems = getValidItems();
    const int32_t numItems = static_cast<int32_t>(allItems.size());
    for (int32_t i = 0; i < numItems; i++) {
        if (allItems[i]->getItemType() == Item::ITEM_TYPE_BROWSER_TAB) {
            if (allItems[i]->getBrowserTabIndex() == browserTabIndex) {
                setSelectedItem(allItems[i]);
                break;
            }
        }
    }
}

/**
 * Create a scene for an instance of a class.
 *
 * @param sceneAttributes
 *    Attributes for the scene.  Scenes may be of different types
 *    (full, generic, etc) and the attributes should be checked when
 *    saving the scene.
 *
 * @return Pointer to SceneClass object representing the state of 
 *    this object.  Under some circumstances a NULL pointer may be
 *    returned.  Caller will take ownership of returned object.
 */
SceneClass* 
VolumeSurfaceOutlineColorOrTabModel::saveToScene(const SceneAttributes* sceneAttributes,
                                                 const AString& instanceName)
{
    SceneClass* sceneClass = new SceneClass(instanceName,
                                            "VolumeSurfaceOutlineColorOrTabModel",
                                            1);
    
    sceneClass->addInteger("m_previousSelectedItemIndex", 
                           m_previousSelectedItemIndex);
    sceneClass->addChild(m_selectedItem->saveToScene(sceneAttributes, 
                                                     "m_selectedItem"));

    return sceneClass;
}

/**
 * Restore the state of an instance of a class.
 * 
 * @param sceneAttributes
 *    Attributes for the scene.  Scenes may be of different types
 *    (full, generic, etc) and the attributes should be checked when
 *    restoring the scene.
 *
 * @param sceneClass
 *     SceneClass containing the state that was previously 
 *     saved and should be restored.
 */
void 
VolumeSurfaceOutlineColorOrTabModel::restoreFromScene(const SceneAttributes* sceneAttributes,
                                                      const SceneClass* sceneClass)
{
    if (sceneClass == NULL) {
        return;
    }
    
    m_previousSelectedItemIndex = sceneClass->getIntegerValue("m_previousSelectedItemIndex",
                                                              -1);
    m_selectedItem->restoreFromScene(sceneAttributes, 
                                     sceneClass->getClass("m_selectedItem"));
}



//======================================================================

/**
 * \class caret::VolumeSurfaceOutlineColorOrTabModel::Item 
 * \brief An item in VolumeSurfaceOutlineColorOrTabModel.
 *
 * At this time, item is either a color or a browser
 * tab index.
 */

/**
 * Constructor for a Caret Color.
 * @param color
 *   The caret color.
 */
VolumeSurfaceOutlineColorOrTabModel::Item::Item(const CaretColorEnum::Enum color)
{
    m_color = color;
    m_browserTabIndex = 0;
    m_itemType = ITEM_TYPE_COLOR;
}

/**
 * Constructor for a browser tab.
 * @param browserTabIndex
 *   Index of browser tab.
 */
VolumeSurfaceOutlineColorOrTabModel::Item::Item(const int32_t browserTabIndex)
{
    m_color = CaretColorEnum::BLACK;
    m_browserTabIndex = browserTabIndex;
    m_itemType = ITEM_TYPE_BROWSER_TAB;
}

/**
 * Destructor.
 */
VolumeSurfaceOutlineColorOrTabModel::Item::~Item()
{
    
}

/**
 * @return Is this item valid?
 */
bool 
VolumeSurfaceOutlineColorOrTabModel::Item::isValid() const
{
    bool valid = false;
    
    switch (m_itemType) {
        case ITEM_TYPE_BROWSER_TAB:
            if (getBrowserTabContent() != NULL) {
                valid = true;
            }
            break;
        case ITEM_TYPE_COLOR:
            valid = true;
            break;
    }
    
    return valid;
}

/**
 * @return  Name of this item.
 */
AString
VolumeSurfaceOutlineColorOrTabModel::Item::getName()
{
    AString name = "PROGRAM ERROR";
    
    switch(m_itemType) {
        case ITEM_TYPE_BROWSER_TAB:
        {
            BrowserTabContent* btc = getBrowserTabContent();
            if (btc != NULL) {
                name = ("Tab "
                        + AString::number(btc->getTabNumber() + 1));
            }
        }
            break;
        case ITEM_TYPE_COLOR:
            name = CaretColorEnum::toGuiName(m_color);
            break;
    }
    
    return name;
}

/**
 * @return Type of item.
 */
VolumeSurfaceOutlineColorOrTabModel::Item::ItemType 
VolumeSurfaceOutlineColorOrTabModel::Item::getItemType() const
{
    return m_itemType;
    
}

/**
 * @return Pointer to browser tab in this item or NULL
 * if this item does NOT contain a browser tab.
 */
BrowserTabContent* 
VolumeSurfaceOutlineColorOrTabModel::Item::getBrowserTabContent()
{
    EventBrowserTabGet getTabEvent(m_browserTabIndex);
    EventManager::get()->sendEvent(getTabEvent.getPointer());
    
    BrowserTabContent* tabContent = getTabEvent.getBrowserTab();
    
    return tabContent;
}

/**
 * @return Pointer to browser tab in this item or NULL
 * if this item does NOT contain a browser tab.
 */
const BrowserTabContent* 
VolumeSurfaceOutlineColorOrTabModel::Item::getBrowserTabContent() const
{
    EventBrowserTabGet getTabEvent(m_browserTabIndex);
    EventManager::get()->sendEvent(getTabEvent.getPointer());
    
    BrowserTabContent* tabContent = getTabEvent.getBrowserTab();
    
    return tabContent;
}

/**
 * @return Index of browser tab in this item.  This will always
 * return an integer greater than or equal to zero.  Use isItemValid()
 * to ensure this item is valid.
 */
int32_t 
VolumeSurfaceOutlineColorOrTabModel::Item::getBrowserTabIndex() const
{
    return m_browserTabIndex;
}

/**
 * @return Enumerated type for color in this item.  Returned
 * value is undefined if a color is NOT in this item.
 */
CaretColorEnum::Enum 
VolumeSurfaceOutlineColorOrTabModel::Item::getColor()
{
    return m_color;    
}

/**
 * Create a scene for an instance of a class.
 *
 * @param sceneAttributes
 *    Attributes for the scene.  Scenes may be of different types
 *    (full, generic, etc) and the attributes should be checked when
 *    saving the scene.
 *
 * @return Pointer to SceneClass object representing the state of 
 *    this object.  Under some circumstances a NULL pointer may be
 *    returned.  Caller will take ownership of returned object.
 */
SceneClass* 
VolumeSurfaceOutlineColorOrTabModel::Item::saveToScene(const SceneAttributes* /*sceneAttributes*/,
                                       const AString& instanceName)
{
    SceneClass* sceneClass = new SceneClass(instanceName,
                                            "VolumeSurfaceOutlineColorOrTabModel::Item",
                                            1);
    
    sceneClass->addInteger("m_browserTabIndex", 
                           m_browserTabIndex);
    sceneClass->addEnumeratedType<CaretColorEnum, CaretColorEnum::Enum>("m_color", 
                                                                        m_color);
    switch (m_itemType) {
        case ITEM_TYPE_COLOR:
            sceneClass->addString("m_itemType",
                                  "ITEM_TYPE_COLOR");
            break;
        case ITEM_TYPE_BROWSER_TAB:
            sceneClass->addString("m_itemType",
                                  "ITEM_TYPE_BROWSER_TAB");
            break;
    }    
    
    sceneClass->addInteger("m_browserTabIndex", 
                           m_browserTabIndex);

    return sceneClass;
}

/**
 * Restore the state of an instance of a class.
 * 
 * @param sceneAttributes
 *    Attributes for the scene.  Scenes may be of different types
 *    (full, generic, etc) and the attributes should be checked when
 *    restoring the scene.
 *
 * @param sceneClass
 *     SceneClass containing the state that was previously 
 *     saved and should be restored.
 */
void 
VolumeSurfaceOutlineColorOrTabModel::Item::restoreFromScene(const SceneAttributes* /*sceneAttributes*/,
                                            const SceneClass* sceneClass)
{
    if (sceneClass == NULL) {
        return;
    }
    
    m_browserTabIndex = sceneClass->getIntegerValue("m_browserTabIndex");
    m_color = sceneClass->getEnumeratedTypeValue<CaretColorEnum, CaretColorEnum::Enum>("m_color", CaretColorEnum::BLUE);
    const AString itemTypeName = sceneClass->getStringValue("m_itemType",
                                                            "ITEM_TYPE_COLOR");
    if (itemTypeName == "ITEM_TYPE_BROWSER_TAB") {
        m_itemType = ITEM_TYPE_BROWSER_TAB;
    }
    else if (itemTypeName == "ITEM_TYPE_COLOR") {
        m_itemType = ITEM_TYPE_COLOR;
    }
    else {
        CaretAssert(0);
    }
}
