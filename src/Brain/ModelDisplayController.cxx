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

#include <QStringList>

#include "ModelDisplayController.h"

#include "CaretAssert.h"
#include "CaretLogger.h"
#include "Matrix4x4.h"
#include "OverlaySet.h"
#include "UserView.h"

using namespace caret;

/**
 * Constructor.
 * @param controllerType Type of this controller.
 * @param allowsYokingStatus  This controller can be yoked.
 * @param allowsRotationStatus This controller can be rotated.
 *
 */
ModelDisplayController::ModelDisplayController(const ModelDisplayControllerTypeEnum::Enum controllerType,
                                               const YokingAllowedType allowsYokingStatus,
                                               const RotationAllowedType allowsRotationStatus,
                                               Brain* brain)
    : CaretObject()
{
    this->brain = brain;
    this->initializeMembersModelDisplayController();
    this->controllerType = controllerType;
    this->allowsYokingStatus = allowsYokingStatus;
    this->allowsRotationStatus   = allowsRotationStatus;
    
    for (int32_t i = 0; i < BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS; i++) {
        this->overlaySet[i] = NULL;  // initialized in contructors of child classes
        this->resetViewPrivate(i);
    }
    
    /*
     * Set this last in constructor or else resetViewPrivate() may
     * not function correctly.
     */
    this->isYokingController = (controllerType ==
                                ModelDisplayControllerTypeEnum::MODEL_TYPE_YOKING);
}

/**
 * Destructor
 */
ModelDisplayController::~ModelDisplayController()
{
    for (int32_t i = 0; i < BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS; i++) {
        delete this->overlaySet[i];
    }
}

/**
 * Initilize the overlays for this controller.
 */
void 
ModelDisplayController::initializeOverlays()
{
    for (int32_t i = 0; i < BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS; i++) {
        this->overlaySet[i]->initializeOverlays();
    }
}

void
ModelDisplayController::initializeMembersModelDisplayController()
{
    this->isYokingController = false;
    this->defaultModelScaling = 1.0f;
}

/**
 * @return The type of model controller.
 */
ModelDisplayControllerTypeEnum::Enum 
ModelDisplayController::getControllerType() const
{
    return this->controllerType; 
}

/**
 * See if this controller allows rotation.
 * 
 * @return true if this controller allows rotation, else false.
 *
 */
bool
ModelDisplayController::isRotationAllowed() const
{
    return (this->allowsRotationStatus == ROTATION_ALLOWED_YES);
}

/**
 * See if this controller allows yoking.
 * When Yoked, this controller will maintain the same viewpoint
 * as the user moves the mouse in any other yoked controller.
 * @return  true if this controller supports yoking, else false.
 *
 */
bool
ModelDisplayController::isYokeable() const
{
    return (this->allowsYokingStatus == YOKING_ALLOWED_YES);
}

/**
 * For a structure model, copy the transformations from one window of
 * the structure model to another window.
 *
 * @param controllerSource        Source structure model
 * @param windowTabNumberSource   windowTabNumber of source transformation.
 * @param windowTabNumberTarget   windowTabNumber of target transformation.
 *
 */
void
ModelDisplayController::copyTransformations(
                   const ModelDisplayController& controllerSource,
                   const int32_t windowTabNumberSource,
                   const int32_t windowTabNumberTarget)
{
    if (this == &controllerSource) {
        if (windowTabNumberSource == windowTabNumberTarget) {
            return;
        }
    }
    
    CaretAssertArrayIndex(this->translation,
                          BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS,
                          windowTabNumberTarget);
    CaretAssertArrayIndex(controllerSource->translation,
                          BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS,
                          windowTabNumberSource);
    
    this->translation[windowTabNumberTarget][0] = controllerSource.translation[windowTabNumberSource][0];
    this->translation[windowTabNumberTarget][1] = controllerSource.translation[windowTabNumberSource][1];
    this->translation[windowTabNumberTarget][2] = controllerSource.translation[windowTabNumberSource][2];
    this->scaling[windowTabNumberTarget] = controllerSource.scaling[windowTabNumberSource];
    
    this->viewingRotationMatrix[windowTabNumberTarget][0].setMatrix(*controllerSource.getViewingRotationMatrix(windowTabNumberSource,
                                                                                                               0));
    this->viewingRotationMatrix[windowTabNumberTarget][1].setMatrix(*controllerSource.getViewingRotationMatrix(windowTabNumberSource,
                                                                                                               1));
}

/**
 * the viewing rotation matrix.
 *
 * @param  windowTabNumber  
      Window for which rotation is requested
 * @param  matrixIndex
 *    In almost ALL cases, this value is zero.  If the matrix requested
 *    is for a right surface that is lateral/medial yoked, this value
 *    should be one.
 * @return Pointer to the viewing rotation matrix.
 *
 */
const Matrix4x4*
ModelDisplayController::getViewingRotationMatrix(const int32_t windowTabNumberIn,
                                                 const int32_t matrixIndex) const
{
    /*
     * Yoking ALWAYS uses first window index.
     */
    int32_t windowTabNumber = windowTabNumberIn;
    if (this->isYokingController) {
        windowTabNumber = 0;
    }
    
    CaretAssertArrayIndex(this->viewingRotationMatrix,
                          BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS,
                          windowTabNumber);
    return &this->viewingRotationMatrix[windowTabNumber][matrixIndex];
}

/**
 * the viewing rotation matrix.
 *
 * @param  windowTabNumber  
 *    Window for which rotation is requested
 * @param  matrixIndex
 *    In almost ALL cases, this value is zero.  If the matrix requested
 *    is for a right surface that is lateral/medial yoked, this value
 *    should be one.
 *
 */
Matrix4x4*
ModelDisplayController::getViewingRotationMatrix(const int32_t windowTabNumberIn,
                                                 const int32_t matrixIndex)
{
    /*
     * Yoking ALWAYS uses first window index.
     */
    int32_t windowTabNumber = windowTabNumberIn;
    if (this->isYokingController) {
        windowTabNumber = 0;
    }
    
    CaretAssertArrayIndex(this->viewingRotationMatrix,
                          BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS,
                          windowTabNumber);
    return &this->viewingRotationMatrix[windowTabNumber][matrixIndex];
}

/**
 * get the translation.
 *
 * @param  windowTabNumber  Window for which translation is requested
 * @return  The translation, an array of three floats.
 *
 */
const float*
ModelDisplayController::getTranslation(const int32_t windowTabNumberIn) const
{
    /*
     * Yoking ALWAYS uses first window index.
     */
    int32_t windowTabNumber = windowTabNumberIn;
    if (this->isYokingController) {
        windowTabNumber = 0;
    }
    
    CaretAssertArrayIndex(this->translation,
                          BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS,
                          windowTabNumber);
    return &this->translation[windowTabNumber][0];
}

/**
 * set the translation.
 *
 * @param  windowTabNumber  Window for which translation is requested
 * @param  t  The translation, an array of three floats.
 *
 */
void
ModelDisplayController::setTranslation(const int32_t windowTabNumberIn,
                          const float t[3])
{
    /*
     * Yoking ALWAYS uses first window index.
     */
    int32_t windowTabNumber = windowTabNumberIn;
    if (this->isYokingController) {
        windowTabNumber = 0;
    }
    
    CaretAssertArrayIndex(this->translation,
                          BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS,
                          windowTabNumber);
    this->translation[windowTabNumber][0] = t[0];
    this->translation[windowTabNumber][1] = t[1];
    this->translation[windowTabNumber][2] = t[2];
}

/**
 * set the translation.
 *
 * @param  windowTabNumber  Window for which translation is requested
 * @param  tx - The x-coordinate of the translation.
 * @param  ty - The y-coordinate of the translation.
 * @param  tz - The z-coordinate of the translation.
 *
 */
void
ModelDisplayController::setTranslation(const int32_t windowTabNumberIn,
                          const float tx,
                          const float ty,
                          const float tz)
{
    /*
     * Yoking ALWAYS uses first window index.
     */
    int32_t windowTabNumber = windowTabNumberIn;
    if (this->isYokingController) {
        windowTabNumber = 0;
    }
    
    CaretAssertArrayIndex(this->translation,
                          BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS,
                          windowTabNumber);
    this->translation[windowTabNumber][0] = tx;
    this->translation[windowTabNumber][1] = ty;
    this->translation[windowTabNumber][2] = tz;
}

/**
 * get the scaling.
 *
 * @param  windowTabNumber  Window for which scaling is requested
 * @return  Scaling value.
 *
 */
float
ModelDisplayController::getScaling(const int32_t windowTabNumberIn) const
{
    /*
     * Yoking ALWAYS uses first window index.
     */
    int32_t windowTabNumber = windowTabNumberIn;
    if (this->isYokingController) {
        windowTabNumber = 0;
    }
    
    CaretAssertArrayIndex(this->scaling,
                          BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS,
                          windowTabNumber);
    return this->scaling[windowTabNumber];
}

/**
 * set the scaling.
 *
 * @param  windowTabNumber  Window for which scaling is requested
 * @param  s  The scaling value.
 *
 */
void
ModelDisplayController::setScaling(
                   const int32_t windowTabNumberIn,
                   const float s)
{
    /*
     * Yoking ALWAYS uses first window index.
     */
    int32_t windowTabNumber = windowTabNumberIn;
    if (this->isYokingController) {
        windowTabNumber = 0;
    }
    
    CaretAssertArrayIndex(this->scaling,
                          BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS,
                          windowTabNumber);
    this->scaling[windowTabNumber] = s;
}

/**
 * Resets the view to the default view.
 * 
 * Since is resetView() is virtual and overridden by subclasses,
 * resetView() cannot be called by the constructor of this class.
 * So this methed, resetViewPrivate() is used to reset the view and
 * to initialize the views inside of the constructor.
 *
 * @param  windowTabNumber  Window for which view is requested
 * reset the view.
 */
void 
ModelDisplayController::resetViewPrivate(const int windowTabNumberIn)
{
    /*
     * Yoking ALWAYS uses first window index.
     */
    int32_t windowTabNumber = windowTabNumberIn;
    if (this->isYokingController) {
        windowTabNumber = 0;
    }
    
    CaretAssertArrayIndex(this->viewingRotationMatrix,
                          BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS,
                          windowTabNumber);
    this->setTranslation(windowTabNumber, 0.0f, 0.0f, 0.0f);
    this->viewingRotationMatrix[windowTabNumber][0].identity();
    this->viewingRotationMatrix[windowTabNumber][1].identity();
    this->setScaling(windowTabNumber, this->defaultModelScaling);    
}

/**
 * Reset the view to the default view.
 *
 * @param  windowTabNumber  Window for which view is requested
 * reset the view.
 */
void
ModelDisplayController::resetView(const int32_t windowTabNumberIn)
{
    /*
     * Yoking ALWAYS uses first window index.
     */
    int32_t windowTabNumber = windowTabNumberIn;
    if (this->isYokingController) {
        windowTabNumber = 0;
    }
    
    this->resetViewPrivate(windowTabNumber);
}

/**
 * @param  windowTabNumber  Window for which view is requested
 * set to a right side view.
 *
 */
void
ModelDisplayController::rightView(const int32_t windowTabNumberIn)
{
    /*
     * Yoking ALWAYS uses first window index.
     */
    int32_t windowTabNumber = windowTabNumberIn;
    if (this->isYokingController) {
        windowTabNumber = 0;
    }
    
    CaretAssertArrayIndex(this->viewingRotationMatrix,
                          BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS,
                          windowTabNumber);
    viewingRotationMatrix[windowTabNumber][0].identity();
    viewingRotationMatrix[windowTabNumber][0].rotateY(-90.0);
    viewingRotationMatrix[windowTabNumber][0].rotateZ(-90.0);
    viewingRotationMatrix[windowTabNumber][1].identity();
    viewingRotationMatrix[windowTabNumber][1].rotateY(-90.0);
    viewingRotationMatrix[windowTabNumber][1].rotateZ(-90.0);
}

/**
 * set to a left side view.
 * @param  windowTabNumber  Window for which view is requested
 *
 */
void
ModelDisplayController::leftView(const int32_t windowTabNumberIn)
{
    /*
     * Yoking ALWAYS uses first window index.
     */
    int32_t windowTabNumber = windowTabNumberIn;
    if (this->isYokingController) {
        windowTabNumber = 0;
    }
    
    CaretAssertArrayIndex(this->viewingRotationMatrix,
                          BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS,
                          windowTabNumber);
    viewingRotationMatrix[windowTabNumber][0].identity();
    viewingRotationMatrix[windowTabNumber][0].rotateY(90.0);
    viewingRotationMatrix[windowTabNumber][0].rotateZ(90.0);
    viewingRotationMatrix[windowTabNumber][1].identity();
    viewingRotationMatrix[windowTabNumber][1].rotateY(90.0);
    viewingRotationMatrix[windowTabNumber][1].rotateZ(90.0);
}

/**
 * set to a anterior view.
 * @param  windowTabNumber  Window for which view is requested
 *
 */
void
ModelDisplayController::anteriorView(const int32_t windowTabNumberIn)
{
    /*
     * Yoking ALWAYS uses first window index.
     */
    int32_t windowTabNumber = windowTabNumberIn;
    if (this->isYokingController) {
        windowTabNumber = 0;
    }
    
    CaretAssertArrayIndex(this->viewingRotationMatrix,
                          BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS,
                          windowTabNumber);
    viewingRotationMatrix[windowTabNumber][0].identity();
    viewingRotationMatrix[windowTabNumber][0].rotateX(-90.0);
    viewingRotationMatrix[windowTabNumber][0].rotateY(180.0);
    viewingRotationMatrix[windowTabNumber][1].identity();
    viewingRotationMatrix[windowTabNumber][1].rotateX(-90.0);
}

/**
 * set to a posterior view.
 * @param  windowTabNumber  Window for which view is requested
 *
 */
void
ModelDisplayController::posteriorView(const int32_t windowTabNumberIn)
{
    /*
     * Yoking ALWAYS uses first window index.
     */
    int32_t windowTabNumber = windowTabNumberIn;
    if (this->isYokingController) {
        windowTabNumber = 0;
    }
    
    CaretAssertArrayIndex(this->viewingRotationMatrix,
                          BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS,
                          windowTabNumber);
    viewingRotationMatrix[windowTabNumber][0].identity();
    viewingRotationMatrix[windowTabNumber][0].rotateX(-90.0);
    viewingRotationMatrix[windowTabNumber][1].identity();
    viewingRotationMatrix[windowTabNumber][1].rotateX(-90.0);
    viewingRotationMatrix[windowTabNumber][1].rotateY(180.0);
}

/**
 * set to a dorsal view.
 * @param  windowTabNumber  Window for which view is requested
 *
 */
void
ModelDisplayController::dorsalView(const int32_t windowTabNumberIn)
{
    /*
     * Yoking ALWAYS uses first window index.
     */
    int32_t windowTabNumber = windowTabNumberIn;
    if (this->isYokingController) {
        windowTabNumber = 0;
    }
    
    CaretAssertArrayIndex(this->viewingRotationMatrix,
                          BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS,
                          windowTabNumber);
    viewingRotationMatrix[windowTabNumber][0].identity();
    viewingRotationMatrix[windowTabNumber][1].identity();
    viewingRotationMatrix[windowTabNumber][1].rotateY(-180.0);
}

/**
 * set to a ventral view.
 * @param  windowTabNumber  Window for which view is requested
 *
 */
void
ModelDisplayController::ventralView(const int32_t windowTabNumberIn)
{
    /*
     * Yoking ALWAYS uses first window index.
     */
    int32_t windowTabNumber = windowTabNumberIn;
    if (this->isYokingController) {
        windowTabNumber = 0;
    }
    
    CaretAssertArrayIndex(this->viewingRotationMatrix,
                          BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS,
                          windowTabNumber);
    viewingRotationMatrix[windowTabNumber][0].identity();
    viewingRotationMatrix[windowTabNumber][0].rotateY(-180.0);
    viewingRotationMatrix[windowTabNumber][1].identity();
}

/**
 * Place the transformations for the given window tab into
 * the userView.
 * @param windowTabNumber
 *    Tab number for transformations.
 * @param userView
 *    View into which transformations are loaded.
 */
void 
ModelDisplayController::getTransformationsInUserView(const int32_t windowTabNumber,
                                                     UserView& userView) const
{
    CaretAssertArrayIndex(this->scaling, 
                          BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS, 
                          windowTabNumber);
    
    userView.setTranslation(this->translation[windowTabNumber]);
    float m[4][4];
    this->viewingRotationMatrix[windowTabNumber][0].getMatrix(m);
    userView.setRotation(m);
    userView.setScaling(this->scaling[windowTabNumber]);
}

/**
 * Apply the transformations to the given window tab from
 * the userView.
 * @param windowTabNumber
 *    Tab number whose transformations are updated.
 * @param userView
 *    View into which transformations are retrieved.
 */
void 
ModelDisplayController::setTransformationsFromUserView(const int32_t windowTabNumber,
                                                       const UserView& userView)
{
    CaretAssertArrayIndex(this->scaling, 
                          BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS, 
                          windowTabNumber);
    

    userView.getTranslation(this->translation[windowTabNumber]);
    float m[4][4];
    userView.getRotation(m);
    this->viewingRotationMatrix[windowTabNumber][0].setMatrix(m);
    this->setScaling(windowTabNumber, userView.getScaling());
}

/**
 * Get a String for use in the GUI.  Use toDescriptiveString() for
 * information about this controller's content.
 *
 * @return String for use in the GUI.
 *
 */
AString
ModelDisplayController::toString() const
{
       return this->getNameForGUI(true);
}

/**
 * Returns a descriptive string containing info about this instance.
 *
 * @return  String describing contents of this instance.
 *
 */
AString
ModelDisplayController::toDescriptiveString() const
{
    AString s = CaretObject::toString();
    
    return s;
}

/**
 * Get the brain that created this controller.
 * @return The brain.
 */
Brain*
ModelDisplayController::getBrain()
{
    return this->brain;
}

/**
 * Get the overlay set for the given tab.
 * @param tabIndex
 *   Index of tab.
 * @return
 *   Overlay set at the given tab index.
 */
OverlaySet* 
ModelDisplayController::getOverlaySet(const int tabIndex)
{
    CaretAssertArrayIndex(this->overlaySet, 
                          BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS, 
                          tabIndex);
    return this->overlaySet[tabIndex];
}

/**
 * Get the overlay set for the given tab.
 * @param tabIndex
 *   Index of tab.
 * @return
 *   Overlay set at the given tab index.
 */
const OverlaySet* 
ModelDisplayController::getOverlaySet(const int tabIndex) const
{
    CaretAssertArrayIndex(this->overlaySet, 
                          BrainConstants::MAXIMUM_NUMBER_OF_BROWSER_TABS, 
                          tabIndex);
    return this->overlaySet[tabIndex];
}

