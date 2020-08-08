/*
Copyright (C) 2006 Caelis Estudios

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "PhantomSDL.h"

PhantomSDL_CALARM::PhantomSDL_CALARM( void (*callback)(void), Uint32 delay, bool isFrame)
    {
    mTimer = PhantomSDL_CTIMER::getInstance();
    setCallBack(callback);
    if(isFrame) setDelayInMiliseconds(delay);
    else setDelayInFrames(delay);
    mIsFrame=isFrame;
    mTime = 0;
    mTimer->update();
    }

PhantomSDL_CALARM::~PhantomSDL_CALARM()
    {

    }

void PhantomSDL_CALARM::setCallBack( void(*callback)(void) )
    {
    if(callback != NULL)CallBack = callback;
    }

void PhantomSDL_CALARM::setDelayInMiliseconds(Uint32 miliseconds)
    {
    mDelay = miliseconds;
    }

void PhantomSDL_CALARM::setDelayInFrames(Uint32 frames)
    {
    mDelay = frames;
    }

bool PhantomSDL_CALARM::step()
    {
    if(!mIsFrame) mTimer->update();
    if(mIsFrame) mFrames += 1;
    else mTime += mTimer->getTimeSinceLastMeasure();
    if( (mIsFrame)?mFrames:mTime > mDelay)
        {
        if(CallBack != NULL) CallBack();
        if(mIsFrame) mFrames = 0;
        else mTime = 0;
        return true;
        }
    return false;
    }
