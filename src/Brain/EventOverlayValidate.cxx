
/*LICENSE_START*/
/*
 * Copyright 2013 Washington University,
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

#define __EVENT_OVERLAY_VALIDATE_DECLARE__
#include "EventOverlayValidate.h"
#undef __EVENT_OVERLAY_VALIDATE_DECLARE__

#include "EventTypeEnum.h"

using namespace caret;


    
/**
 * \class caret::EventOverlayValidate 
 * \brief Test an overlay for validity (it exists).
 * \ingroup Brain
 */

/**
 * Constructor.
 */
EventOverlayValidate::EventOverlayValidate(const Overlay* overlay)
: Event(EventTypeEnum::EVENT_OVERLAY_VALIDATE),
  m_overlay(overlay)
{
    m_valid = false;
}

/**
 * Destructor.
 */
EventOverlayValidate::~EventOverlayValidate()
{
    
}

/**
 * @return true if the overlay was found to be valid.
 */
bool
EventOverlayValidate::isValidOverlay() const
{
    return m_valid;
}

/**
 * Set the validity if the given overlay is the overlay
 * that was passed to the constructor.
 *
 * @param overlay
 *    Overlay tested for match.
 */
void
EventOverlayValidate::testValidOverlay(const Overlay* overlay)
{
    if (m_overlay == overlay) {
        m_valid = true;
    }
}
