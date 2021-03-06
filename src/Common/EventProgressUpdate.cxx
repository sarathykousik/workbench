/*LICENSE_START*/
/*
 *  Copyright (C) 2014  Washington University School of Medicine
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
/*LICENSE_END*/

#include "EventProgressUpdate.h"

using namespace caret;

/**
 * \class caret::EventProgressUpdate
 * \brief Event for updating progress of a task in a progress dialog.
 */

EventProgressUpdate::EventProgressUpdate(ProgressObject* myObject): Event(EventTypeEnum::EVENT_PROGRESS_UPDATE),
m_minimumProgressValue(0),
m_maximumProgressValue(100),
m_progressValue(0),
m_progressMessage(""),
m_cancelled(false)
{
   m_amountUpdate = false;
   m_finished = false;
   m_textUpdate = false;
   m_starting = false;
   m_whichObject = myObject;
    
    
}

/**
 * Default constructor.
 *
 * If this instance is not modified and sent to a progress dialog
 * no updates will be made to the progress dialog.  However, if the
 * user has cancelled the task, the cancel status will be set in
 * this instance after returning from the dialog.
 */
EventProgressUpdate::EventProgressUpdate()
: Event(EventTypeEnum::EVENT_PROGRESS_UPDATE),
m_minimumProgressValue(-1),
m_maximumProgressValue(-1),
m_progressValue(-1),
m_progressMessage(""),
m_cancelled(false)
{
    /* nothing */
}

/*
 * Constructor for display of progress in a progress dialog.
 *
 * @param minimumProgressValue
 *    Minimum Progress.
 * @param maximumProgressValue
 *    Maximum progress.
 * @param progressValue
 *    Current progress (min <= current <= maximum)
 * @param progressMessage
 *    Message for display in progress dialog.
 *
 */
EventProgressUpdate::EventProgressUpdate(const int minimumProgressValue,
                                         const int maximumProgressValue,
                                         const int progressValue,
                                         const QString& progressMessage)
: Event(EventTypeEnum::EVENT_PROGRESS_UPDATE),
m_minimumProgressValue(minimumProgressValue),
m_maximumProgressValue(maximumProgressValue),
m_progressValue(progressValue),
m_progressMessage(progressMessage),
m_cancelled(false)
{
    
}

EventProgressUpdate::EventProgressUpdate(const QString& progressMessage)
: Event(EventTypeEnum::EVENT_PROGRESS_UPDATE),
m_minimumProgressValue(-1),
m_maximumProgressValue(-1),
m_progressValue(-1),
m_progressMessage(progressMessage),
m_cancelled(false)
{
    
}

/**
 * Destructor.
 */
EventProgressUpdate::~EventProgressUpdate()
{
}

/*
 * Set values for display of progress in a progress dialog.  This method
 * allows a progress event to be reused and avoid reallocation, particularly
 * when updates are frequent.
 *
 * @param progressValue
 *    Current progress (min <= current <= maximum)
 * @param progressMessage
 *    Message for display in progress dialog.
 *
 */
void
EventProgressUpdate::setProgress(const int progressValue,
                                 const QString& progressMessage)
{
    m_progressValue = progressValue;
    m_progressMessage = progressMessage;
}

/*
 * Update only the progress message in the progress dialog.
 *
 * @param progressMessage
 *    Message for display in progress dialog.
 *
 */
void
EventProgressUpdate::setProgressMessage(const QString& progressMessage)
{
    m_progressMessage = progressMessage;
}



