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

PhantomSDL_CLOG *PhantomSDL_CLOG::mInstance = 0;

PhantomSDL_CLOG::PhantomSDL_CLOG()
    {
    mAppLog.open("PhantomSDL_AppLog.log");
    mClientLog.open("PhantomSDL_ClientLog.log");
    mServerLog.open("PhantomSDL_ServerLog.log");

    if(!loadStrings()) write(1,"Impossible To Load Strings.\n");

    mTimer = PhantomSDL_CTIMER::getInstance();

    char *Copyright ="|*****************************************************|\n"
                     "|                                                     |\n"
                     "|                  PhantomSDL 2.0                     |\n"
                     "|             written by Leandro Ostera               |\n"
                     "|              Copyright (C) 2005-2006                |\n"
                     "|                                                     |\n"
                     "|*****************************************************|\n\n";

    write(2,Copyright,false);
    write(4,Copyright,false);

    write(2,"[CLog]-> Singleton Created.");
    }

PhantomSDL_CLOG::~PhantomSDL_CLOG()
    {
    write(2,"[CLog]-> Singleton Destroyed.");
    }

PhantomSDL_CLOG* PhantomSDL_CLOG::getInstance()
    {
    if ( PhantomSDL_CLOG::mInstance == 0 )
        {
        mInstance = new PhantomSDL_CLOG;
        }
    return mInstance;
    }

void PhantomSDL_CLOG::erase()
    {
    if( PhantomSDL_CLOG::mInstance != 0)
        {
        delete mInstance;
        }
    }

void PhantomSDL_CLOG::write(Uint32 target, const char * Message, bool printTime, ...)
    {
    char string[1024];
    va_list ap;
    va_start(ap, Message);
    vsprintf(string, Message, ap);
    va_end(ap);

    if(target&LOG_APP)
       {
 //      if(printTime) mAppLog<<"["<<mTimer->getTimeString()<<"]-";
       mAppLog<<string<<"\n\n";
       mAppLog.flush();
       }
   if(target&LOG_CLIENT)
       {
       //if(printTime) mClientLog<<"["<<mTimer->getTimeString()<<"]-";
       mClientLog<<string<<"\n\n";
       mClientLog.flush();
       }
   if(target&LOG_SERVER)
       {
       //if(printTime) mServerLog<<"["<<mTimer->getTimeString()<<"]-";
       mServerLog<<string<<"\n\n";
       mServerLog.flush();
       }
   if(target&LOG_USER)
       {
    #ifdef _WIN32
       MessageBox(NULL,string,"Message",MB_OK);
    #else
    #error User-level logging is not yet implemented for this platform.
    #endif
        }
    }

void PhantomSDL_CLOG::write(Uint32 target, unsigned long msgID, bool printTime, ...)
   {
   va_list args;
   va_start(args, msgID);
   char szBuf[1024];
   vsprintf(szBuf,logStrings[msgID].c_str(),args);
   va_end(args);
   write(target,szBuf);
   }

bool PhantomSDL_CLOG::loadStrings()
    {
#ifdef _WIN32

#else

#endif
    }
