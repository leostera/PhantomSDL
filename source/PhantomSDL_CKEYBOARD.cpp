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

PhantomSDL_CKEYBOARD *PhantomSDL_CKEYBOARD::mInstance = 0;

PhantomSDL_CKEYBOARD::PhantomSDL_CKEYBOARD()
    {
    mPushForEvent.type = SDL_USEREVENT;
    mPushForEvent.user.code = 0;
    mPushForEvent.user.data1 = NULL;
    mPushForEvent.user.data2 = 0;
    mPumped = false;
    mLog = PhantomSDL_CLOG::getInstance();
    mLog->write(2,"[CKeyboard]-> Singleton Created.");
    }

PhantomSDL_CKEYBOARD::~PhantomSDL_CKEYBOARD()
    {
    mLog->write(2,"[CKeyboard]-> Singleton Destroyed.");
    }

PhantomSDL_CKEYBOARD* PhantomSDL_CKEYBOARD::getInstance()
    {
    if ( PhantomSDL_CKEYBOARD::mInstance == 0 )
        {
        mInstance = new PhantomSDL_CKEYBOARD;
        }
    return mInstance;
    }

void PhantomSDL_CKEYBOARD::erase()
    {
    if( PhantomSDL_CKEYBOARD::mInstance != 0)
        {
        delete mInstance;
        }
    }

void PhantomSDL_CKEYBOARD::pushEv()
    {
    SDL_PushEvent(&mPushForEvent);
    }

SDL_Event PhantomSDL_CKEYBOARD::getEv()
    {
    return mEvent;
    }

bool PhantomSDL_CKEYBOARD::pollEv()
    {
    return (SDL_PollEvent(&mEvent)) ? true : false;
    }

void PhantomSDL_CKEYBOARD::pump()
    {
    if(!mPumped)
        {
        SDL_PumpEvents();
        mPumped = true;
        }
    }

bool PhantomSDL_CKEYBOARD::getKey(SDLKey key,bool up)
    {
    if(up)
        {
        pollEv();
        if(mEvent.type==SDL_KEYUP)
            {
            return (mEvent.key.keysym.sym==key) ? true : false;
            }
        }
    pollKey();
    if(mKey[key])
        {
        pollEv();
        mLastKey = mEvent;
        return true;
        }
    return false;
    }

bool PhantomSDL_CKEYBOARD::pollKey()
    {
    return (mKey = SDL_GetKeyState(NULL)) ? true : false;
    }

SDL_Event PhantomSDL_CKEYBOARD::getLastKey()
    {
    return mLastKey;
    }
