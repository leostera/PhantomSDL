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

PhantomSDL_CTIMER* PhantomSDL_CTIMER::mInstance=0;

PhantomSDL_CTIMER::PhantomSDL_CTIMER()
    {
    mCurrentTime = 0;
    mAppTime = 0;
    mFirstMeasure = 0;
    mSecondMeasure = 0;
    }

PhantomSDL_CTIMER::~PhantomSDL_CTIMER()
    {

    }

PhantomSDL_CTIMER* PhantomSDL_CTIMER::getInstance()
    {
    if(mInstance == 0)
        {
        mInstance = new PhantomSDL_CTIMER();
        }
    return mInstance;
    }

void PhantomSDL_CTIMER::erase()
    {
    if(mInstance != 0)
        {
        delete mInstance;
        }
    }

void PhantomSDL_CTIMER::applyDelay()
    {
    SDL_Delay(mDelay);
    }

Uint32 PhantomSDL_CTIMER::getAppTime()
    {
    return mAppTime;
    }

Uint32 PhantomSDL_CTIMER::getTime()
    {
    return mCurrentTime;
    }

const char* PhantomSDL_CTIMER::getAppTimeString()
    {
    return itoa(mCurrentTime,NULL,2);
    }

const char* PhantomSDL_CTIMER::getTimeString()
    {
    time(&mRawtime);
    mTimeinfo = localtime(&mRawtime);
    char * hour, * min, *sec;
    itoa(mTimeinfo->tm_hour,hour,2);
    itoa(mTimeinfo->tm_min,min,2);
    itoa(mTimeinfo->tm_sec,sec,2);
    std::string tmp = hour;
    tmp += ":";
    tmp += min;
    tmp += ":";
    tmp += sec;
    return tmp.c_str();
    }

void PhantomSDL_CTIMER::setDelayTime(Uint32 delay)
    {
    mDelay = delay;
    }

void PhantomSDL_CTIMER::update()
    {
    mAppTime = SDL_GetTicks();
    mFirstMeasure = mSecondMeasure;
	mSecondMeasure = SDL_GetTicks();
    }

Uint32 PhantomSDL_CTIMER::getTimeSinceLastMeasure()
    {
    return (mSecondMeasure - mFirstMeasure);
    }

bool PhantomSDL_CTIMER::checkTime(Uint32 miliseconds)
    {
    return ((mSecondMeasure - mFirstMeasure)==miliseconds) ? true : false;
    }
