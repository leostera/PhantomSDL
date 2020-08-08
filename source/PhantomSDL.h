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
#ifndef _PHANTOMSDL_DEPENDENCIES_
#define _PHANTOMSDL_DEPENDENCIES_

//External APIs Header Files
    #include "SDL/SDL.h"
    #include "OpenGL/gl.h"
    #include "OpenAL/al.h"
    #include "OpenAL/alut.h"

//Standart C/C++ Header Files
    #include <fstream>
    #include <stdarg.h>
    #include <time.h>
    #include <string>
    #include <vector>
    #include <list>

#endif

#ifdef _WIN32
    #include <windows.h>
#endif

#ifndef _PHANTOMSDL_H_
#define _PHANTOMSDL_H_

    #ifndef _PHANTOMSDL_TIMER_
    #define _PHANTOMSDL_TIMER_
        class PhantomSDL_CTIMER
            {
            private:
                //Private Properties And Methods For Singleton Pattern
                PhantomSDL_CTIMER();
                static PhantomSDL_CTIMER* mInstance;

                //Private Propierties And Methods For Timer Functions
                time_t mRawtime;
                struct tm * mTimeinfo;
                Uint32 mFirstMeasure;
                Uint32 mSecondMeasure;
                Uint32 mCurrentTime;
                Uint32 mAppTime;
                Uint32 mDelay;

            public:
                //Public Properties And Methods For Singleton Pattern
                static PhantomSDL_CTIMER* getInstance();
                ~PhantomSDL_CTIMER();
                static void erase();

                //Public Propierties And Methods For Timer Functions
                bool checkTime(Uint32 miliseconds);
                Uint32 getTimeSinceLastMeasure();
                Uint32 getTime();
                const char* getTimeString();
                Uint32 getAppTime();
                const char* getAppTimeString();
                void setDelayTime(Uint32 delay);
                void applyDelay();
                void update();
            };
    #endif

    #ifndef _PHANTOMSDL_ALARM_
    #define _PHANTOMSDL_ALARM_
        class PhantomSDL_CALARM
            {
            private:
                //Private Propierties And Methods For Alarm Use
                PhantomSDL_CTIMER *mTimer;
                Uint32 mDelay;
                Uint32 mTime;
                Uint32 mFrames;
                bool mIsFrame;
                void (*CallBack)(void);

            public:
                //Public Propierties And Methods For Alarm Use
                PhantomSDL_CALARM( void (*callback)(void), Uint32 delay, bool isFrame=false);
                ~PhantomSDL_CALARM();

                void setCallBack( void(*callback)(void));

                void setDelayInMiliseconds(Uint32 miliseconds);
                void setDelayInFrames(Uint32 frames);

                bool step();
            };
    #endif

    #ifndef _PHANTOMSDL_LOG_
    #define _PHANTOMSDL_LOG_
        const int MAX_LOG_STRINGS=256;
        const int LOG_APP=1;
        const int LOG_CLIENT=2;
        const int LOG_SERVER=4;
        const int LOG_USER=8;

        class PhantomSDL_CLOG
            {
            private:
                //Private Properties And Methods For Singleton Pattern
                static PhantomSDL_CLOG* mInstance;
                PhantomSDL_CLOG();

                //Private Properties And Methods For The Logger
                std::ofstream mAppLog;
                std::ofstream mClientLog;
                std::ofstream mServerLog;

                std::string logStrings[MAX_LOG_STRINGS];
                bool loadStrings();

                PhantomSDL_CTIMER *mTimer;

            public:
                //Public Properties And Methods For Singleton Pattern
                static PhantomSDL_CLOG* getInstance();
                static void erase();
                ~PhantomSDL_CLOG();

                //Public Properties And Methods For The Logger
                void write(Uint32 target, const char * Message, bool printTime=true, ...);
                void write(Uint32 target, unsigned long msgID, bool printTime=true, ...);

            };
    #endif

    #ifndef _PHANTOMSDL_FPS_
    #define _PHANTOMSDL_FPS_
        class PhantomSDL_CFPS
            {
            private:
                PhantomSDL_CALARM* mAlarmFps;
                Uint32 mFps;
                Uint32 mShownFps;

                void reset();
            public:
                PhantomSDL_CFPS();
                ~PhantomSDL_CFPS();

                Uint32 getFps() const { return mShownFps; }
                void step();
            };
    #endif

    #ifndef _PHANTOMSDL_SDLCONFIG_
    #define _PHANTOMSDL_SDLCONFIG_
        struct PhantomSDL_SDLCONFIG
            {
            Uint32 Flags;       //SDL_Init(Flags);
            Uint32 VideoFlags;  //SDL_SetVideoMode(x,x,x, Flags);
            Uint32 VideoWidth;  //SDL_SetVideoMode(Width,x,x,x);
            Uint32 VideoHeight; //SDL_SetVideoMode(x,Height,x,x);
            Uint32 VideoBPP;    //SDL_SetVideoMode(x,x,BPP,x);
            };
    #endif

    #ifndef _PHANTOMSDL_SDLMAIN_
    #define _PHANTOMSDL_SDLMAIN_
        class PhantomSDL_CSDL
            {
            private:
                //Private Properties And Methods For Singleton Pattern
                static PhantomSDL_CSDL* mInstance;
                PhantomSDL_CSDL();

                //Private Properties And Methods For SDL Functions
                PhantomSDL_SDLCONFIG *mConfig;
                PhantomSDL_SDLCONFIG *mLastConfig;
                PhantomSDL_CLOG *mLog;
                SDL_Surface *mScreen;
                bool mFullscreen;

            public:
                //Public Properties And Methods For Singleton Pattern
                static PhantomSDL_CSDL* getInstance();
                static void erase();
                ~PhantomSDL_CSDL();

                //Public Properties And Methods For SDL Functions
                Uint32 init(Uint32 SDLFlags, Uint32 SDLVideoFlags, Uint32 W, Uint32 H, Uint32 BPP);
                Uint32 changeVideoMode(Uint32 SDLVideoFlags, Uint32 W, Uint32 H, Uint32 BPP);
                Uint32 resetVideoMode();
                Uint32 switchFullscreen();

                PhantomSDL_SDLCONFIG* getConfig();
                void setConfig(PhantomSDL_SDLCONFIG *Config);
                Uint32 applyConfig();

                SDL_Surface* getScreen();

                void setGLAttribute(SDL_GLattr attribute, Uint32 value);
                void setCaption(const char * caption,...);

                void updateScreen();
            };
    #endif

    #ifndef _PHANTOMSDL_KEYBOARD_
    #define _PHANTOMSDL_KEYBOARD_
        class PhantomSDL_CKEYBOARD
            {
            private:
                //Private Properties And Methods For Singleton Pattern
                static PhantomSDL_CKEYBOARD* mInstance;
                PhantomSDL_CKEYBOARD();

                //Private Properties And Methods For SDL Key Input Functions
                SDL_Event mEvent;
                SDL_Event mPushForEvent;
                Uint8 *mKey;
                SDL_Event mLastKey;
                bool mPumped;

                PhantomSDL_CLOG *mLog;
            public:
                //Public Properties And Methods For Singleton Pattern
                static PhantomSDL_CKEYBOARD* getInstance();
                static void erase();
                ~PhantomSDL_CKEYBOARD();

                //Public Properties And Methods For SDL Key Input Functions
                SDL_Event getEv();
                bool pollEv();
                bool getKey(SDLKey key,bool up=true);
                bool pollKey();
                SDL_Event getLastKey();
                void pushEv();
                void pump();

            };
    #endif

    #ifndef _PHANTOMSDL_MOUSE_
    #define _PHANTOMSDL_MOUSE_
        class PhantomSDL_CMOUSE
            {
            /*
            CMouse Singleton
            getMouseState
            getMouseClick
            warpMouse(x,y)
            getMouseX
            getMouseY
            setMouseMask
            setMouseSprite
            getMouseMask
            getMouseSprite
            */
            };
    #endif

    #ifndef _PHANTOMSDL_JOYSTICK_
    #define _PHANTOMSDL_JOYSTICK_
        class PhantomSDL_CJOYSTICK
            {
            /*
            CJoystick Singleton
            getJoystickState
            getJoystickButtonPress
            getJoystickButtonRelease
            getJoystickHatState
            */
            };
    #endif

    #ifndef _PHANTOMSDL_INSTANCE_
    #define _PHANTOMSDL_INSTANCE_
        class PhantomSDL_CINSTANCE
            {
            private:
                //Private Propierties And Methods For Instance Easy-Use
                Uint32 mId;
                Uint32 mDepth;
                bool mVisible;
                std::string mName;
              //Sprite *mSprite;
              //Sprite *mMask;

            public:
                PhantomSDL_CINSTANCE() { mId = (int)this; }

                //Public Propierties And Methods For Instance Easy-Use
                Uint32 getID() { return mId; }

                void setName(std::string Name) { mName = Name; }
                std::string getName() const { return mName; }

                //void setSprite( Sprite);
                //Sprite getSprite();

                //void setMask( Sprite);
                //Sprite getMask();

                void setVisible(bool visible) { mVisible = visible; }
                bool getVisible() const { return mVisible; }

                void setDepth(Uint32 depth) { mDepth = depth; }
                Uint32 getDepth() const { return mDepth; }

                virtual void createEvent()=0;
                virtual void destroyEvent()=0;
        /*        virtual void keyPress(SDLKey key)=0;
                virtual void keyRelease(SDLKey key)=0;
                virtual void mouseMove()=0;
                virtual void mousePress()=0;
                virtual void mouseRelease()=0;*/
                virtual void drawEvent()=0;
                virtual void stepEvent()=0;
              //virtual void Collision( Sprite* sprite)=0;
            };
    #endif

    #ifndef _PHANTOMSDL_INSTANCEHANDLER_
    #define _PHANTOMSDL_INSTANCEHANDLER_
        class PhantomSDL_CINSTANCEHANDLER
            {
            private:
                //Private Properties And Methods For Singleton Pattern
                static PhantomSDL_CINSTANCEHANDLER* mInstance;
                PhantomSDL_CINSTANCEHANDLER();

                //Private Properties And Methods For InstanceHandling Functions
                std::list<PhantomSDL_CINSTANCE*> mInstances;
                Uint32 mInstanceNumber;

                //Private Properties And Methods For State Logging
                PhantomSDL_CLOG *mLog;

            public:
                //Public Properties And Methods For Singleton Pattern
                static PhantomSDL_CINSTANCEHANDLER* getInstance();
                ~PhantomSDL_CINSTANCEHANDLER();
                static void erase();

                //Public Properties And Methods For InstanceHandling Functions
                PhantomSDL_CINSTANCE* getInstance(Uint32 instanceID);
                void addInstance(PhantomSDL_CINSTANCE* instance);
                void deleteInstance(PhantomSDL_CINSTANCE* instance);
                void deleteAll();

                void step();

                Uint32 getInstanceNumber() const { return mInstanceNumber; }
            };
    #endif

    #ifndef _PHANTOMSDL_SYSTEM_
    #define _PHANTOMSDL_SYSTEM_
        class PhantomSDL_CSYSTEM
            {
            private:
                //Private Properties And Methods For Singleton Pattern
                static PhantomSDL_CSYSTEM *mInstance;
                PhantomSDL_CSYSTEM();

                //Private Properties And Methods For System Functionality
                PhantomSDL_CSDL *mSDL;
                PhantomSDL_CLOG *mLog;
                PhantomSDL_CINSTANCEHANDLER *mInstHand;
                PhantomSDL_CKEYBOARD *mKeyIn;
                PhantomSDL_CFPS *mFps;
                PhantomSDL_CTIMER *mTimer;

                bool mIsRunning;

            public:
                //Public Properties And Methods For Singleton Pattern
                static PhantomSDL_CSYSTEM *getInstance();
                static void erase();
                ~PhantomSDL_CSYSTEM();

                //Public Properties And Methods For System Functionality
                PhantomSDL_CSDL* getSDL() { return mSDL; }
                PhantomSDL_CLOG* getLog() { return mLog; }
                PhantomSDL_CINSTANCEHANDLER* getInstanceHandler() { return mInstHand; }
                PhantomSDL_CKEYBOARD* getKeyInput() { return mKeyIn; }

                bool isRunning() const { return mIsRunning; }
                void run();
            };
    #endif

typedef PhantomSDL_CTIMER CTimer;
typedef PhantomSDL_CALARM CAlarm;
typedef PhantomSDL_CLOG CLog;
typedef PhantomSDL_CFPS CFps;
typedef PhantomSDL_SDLCONFIG SDLConfig;
typedef PhantomSDL_CSDL CSDL;
typedef PhantomSDL_CKEYBOARD CKeyboard;
typedef PhantomSDL_CMOUSE CMouse;
typedef PhantomSDL_CJOYSTICK CJoystick;
//typedef PhantomSDL_CINSTANCE CInstance;
typedef PhantomSDL_CINSTANCEHANDLER CInstanceHandler;
typedef PhantomSDL_CSYSTEM CSystem;
#endif
