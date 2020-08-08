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

PhantomSDL_CSYSTEM* PhantomSDL_CSYSTEM::mInstance=0;

PhantomSDL_CSYSTEM::PhantomSDL_CSYSTEM()
    {
    mSDL = PhantomSDL_CSDL::getInstance();
    mLog = PhantomSDL_CLOG::getInstance();
    mInstHand = PhantomSDL_CINSTANCEHANDLER::getInstance();
    mKeyIn = PhantomSDL_CKEYBOARD::getInstance();
    mFps = new PhantomSDL_CFPS();
    mTimer = PhantomSDL_CTIMER::getInstance();
    mIsRunning = true;
    mLog->write(2,"CSystem Singleton Created.");
    }

PhantomSDL_CSYSTEM::~PhantomSDL_CSYSTEM()
    {
    mLog->write(2,"CSystem Singleton Destroyed.");
    mInstHand->erase();
    mKeyIn->erase();
    mSDL->erase();
    delete mFps;
    mLog->erase();
    mTimer->erase();
    }

PhantomSDL_CSYSTEM* PhantomSDL_CSYSTEM::getInstance()
    {
    if(PhantomSDL_CSYSTEM::mInstance == 0)
        {
        mInstance = new PhantomSDL_CSYSTEM();
        }
    return mInstance;
    }

void PhantomSDL_CSYSTEM::erase()
    {
    if(PhantomSDL_CSYSTEM::mInstance != 0)
        {
        delete mInstance;
        }
    }

void PhantomSDL_CSYSTEM::run()
    {
    mTimer->update();

    mKeyIn->pushEv();
    if(mKeyIn->getKey(SDLK_ESCAPE)) mIsRunning=false;
    if(mKeyIn->getEv().type == SDL_QUIT) mIsRunning = false;

    mInstHand->step();

    mSDL->updateScreen();

    mFps->step();

    mSDL->setCaption("PhantomSDL 2.0 - FPS: %d - InstanceNumber: %d",mFps->getFps(),mInstHand->getInstanceNumber());

    if(mIsRunning == false) mLog->write(2,"CSystem Exiting Main Loop.");
    }
