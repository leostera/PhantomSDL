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

PhantomSDL_CSDL *PhantomSDL_CSDL::mInstance = 0;

PhantomSDL_CSDL::PhantomSDL_CSDL()
    {
    mConfig = 0;
    mLog = PhantomSDL_CLOG::getInstance();
    mLog->write(2,"[CSDL]-> Singleton Created.");
    }

PhantomSDL_CSDL::~PhantomSDL_CSDL()
    {
    delete PhantomSDL_CSDL::mConfig;
    mLog->write(2,"[CSDL]-> Singleton Destroyed.");
    }

PhantomSDL_CSDL* PhantomSDL_CSDL::getInstance()
    {
    if ( PhantomSDL_CSDL::mInstance == 0 )
        {
        mInstance = new PhantomSDL_CSDL;
        }
    return mInstance;
    }

void PhantomSDL_CSDL::erase()
    {
    if( PhantomSDL_CSDL::mInstance != 0)
        {
        delete mInstance;
        }
    }

Uint32 PhantomSDL_CSDL::init(Uint32 SDLFlags, Uint32 SDLVideoFlags, Uint32 W, Uint32 H, Uint32 BPP)
    {
    mConfig = new PhantomSDL_SDLCONFIG;
    mConfig->Flags=SDLFlags;
    mConfig->VideoFlags=SDLVideoFlags;
    mConfig->VideoWidth=W;
    mConfig->VideoHeight=H;
    mConfig->VideoBPP=BPP;

    if(applyConfig())
        {
        return 1;
        }
    return 0;
    }

Uint32 PhantomSDL_CSDL::resetVideoMode()
    {
    mConfig = mLastConfig;

    if(applyConfig())
        {
        mLog->write(2,"[CSDL]-> ResetVideoMode Changed Succesfully: %d x %d x %d",mConfig->VideoWidth,mConfig->VideoHeight,mConfig->VideoBPP);
        return 1;
        }
    return 0;
    }

Uint32 PhantomSDL_CSDL::changeVideoMode(Uint32 SDLVideoFlags, Uint32 W, Uint32 H, Uint32 BPP)
    {
    mLastConfig = mConfig;
    mConfig->VideoFlags = SDLVideoFlags;
    mConfig->VideoWidth = W;
    mConfig->VideoHeight = H;
    mConfig->VideoBPP = BPP;

    if(applyConfig())
        {
        mLog->write(2,"[CSDL]-> VideoMode Changed Succesfully: %d x %d x %d",W,H,BPP);
        return 1;
        }
    return 0;
    }

Uint32 PhantomSDL_CSDL::switchFullscreen()
    {
    mFullscreen = !mFullscreen;
    PhantomSDL_SDLCONFIG *tmp = new PhantomSDL_SDLCONFIG;
    if(mConfig->VideoFlags&SDL_OPENGL)
        tmp->VideoFlags |= SDL_OPENGL;
    if(mConfig->VideoFlags&SDL_HWSURFACE)
        tmp->VideoFlags |= SDL_HWSURFACE;
    if(mConfig->VideoFlags&SDL_DOUBLEBUF)
        tmp->VideoFlags |= SDL_DOUBLEBUF;
    if(mConfig->VideoFlags&SDL_ANYFORMAT)
        tmp->VideoFlags |= SDL_ANYFORMAT;
    if(mConfig->VideoFlags&SDL_ASYNCBLIT)
        tmp->VideoFlags |= SDL_ASYNCBLIT;
    if(mConfig->VideoFlags&SDL_HWPALETTE)
        tmp->VideoFlags |= SDL_HWPALETTE;
    if(mConfig->VideoFlags&SDL_RESIZABLE)
        tmp->VideoFlags |= SDL_RESIZABLE;
    if(mConfig->VideoFlags&SDL_NOFRAME)
        tmp->VideoFlags |= SDL_NOFRAME;
    if(mFullscreen)
        tmp->VideoFlags |= SDL_FULLSCREEN;

    mConfig = tmp;
    if(applyConfig())
        {
        mLog->write(2,"[CSDL]-> VideoMode Changed Succesfully: %d x %d x %d",mConfig->VideoWidth,mConfig->VideoHeight,mConfig->VideoBPP);
        return 1;
        }
    return 0;
    }

PhantomSDL_SDLCONFIG* PhantomSDL_CSDL::getConfig()
    {
    if( PhantomSDL_CSDL::mConfig == 0 )
        {
        mConfig = new PhantomSDL_SDLCONFIG;
        mLog->write(2,"[CSDL]-> Blank Configuration Created - Warning: Must Set Configuration.");
        }
    else
        {
        return mConfig;
        }
    }

void PhantomSDL_CSDL::setConfig(PhantomSDL_SDLCONFIG *Config)
    {
    mConfig = Config;
    mLog->write(2,"[CSDL]-> Configuration Set.");
    }

Uint32 PhantomSDL_CSDL::applyConfig()
    {
    if( PhantomSDL_CSDL::mConfig == 0)
        {
        mLog->write(2,"[CSDL]-> Configuration Error: Configuration Struct Was Not Set.");
        return 0;
        }
    if(SDL_Init(mConfig->Flags)<0)
        {
        char *error = SDL_GetError();
        mLog->write(2,"[CSDL]-> Configuration Error: SDL Init Error: %s.", (SDL_GetError()!=NULL)?SDL_GetError():"Unable To Get SDL_GetError() Information");
        return 0;
        }
    if(mConfig->VideoFlags&SDL_OPENGL)
        {
        if(SDL_SetVideoMode(mConfig->VideoWidth, mConfig->VideoHeight, mConfig->VideoBPP, mConfig->VideoFlags)<0)
            {
            mLog->write(2,"[CSDL]-> Configuration Error: SDL SetVideoMode Error: %s.",(SDL_GetError()!=NULL)?SDL_GetError():"Unable To Get SDL_GetError() Information");
            return 0;
            }
        }
    else
        {
        if( (mScreen = SDL_SetVideoMode(mConfig->VideoWidth, mConfig->VideoHeight, mConfig->VideoBPP, mConfig->VideoFlags)) == NULL)
            {
            mLog->write(2,"[CSDL]-> Configuration Error: SDL SetVideoMode Error: %s.",(SDL_GetError()!=NULL)?SDL_GetError():"Unable To Get SDL_GetError() Information");
            return 0;
            }
        }

    if(mConfig->VideoFlags&SDL_FULLSCREEN) mFullscreen = true;
    else mFullscreen = false;

    mLog->write(2,"[CSDL]-> Configuration Applied Succesfully.");

    atexit(SDL_Quit);

    return 1;
    }

SDL_Surface* PhantomSDL_CSDL::getScreen()
    {
    return mScreen;
    }

void PhantomSDL_CSDL::setGLAttribute(SDL_GLattr attribute, Uint32 value)
    {
    if(mConfig->VideoFlags&SDL_OPENGL) SDL_GL_SetAttribute(attribute,value);
    else return;
    }

void PhantomSDL_CSDL::setCaption(const char * caption,...)
    {
    char string[1024];
    va_list ap;
    va_start(ap, caption);
    vsprintf(string, caption, ap);
    va_end(ap);
    SDL_WM_SetCaption(string,NULL);
    }

void PhantomSDL_CSDL::updateScreen()
    {
    if(mConfig->VideoFlags&SDL_OPENGL) SDL_GL_SwapBuffers();
    else SDL_Flip(mScreen);
    }
