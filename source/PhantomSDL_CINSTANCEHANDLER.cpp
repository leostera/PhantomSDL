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

PhantomSDL_CINSTANCEHANDLER* PhantomSDL_CINSTANCEHANDLER::mInstance=0;

PhantomSDL_CINSTANCEHANDLER::PhantomSDL_CINSTANCEHANDLER()
    {
    mLog = PhantomSDL_CLOG::getInstance();
    mLog->write(2,"[CInstanceHandler]-> Singleton Created.");
    mInstanceNumber = 0;
    }

PhantomSDL_CINSTANCEHANDLER::~PhantomSDL_CINSTANCEHANDLER()
    {
    deleteAll();
    mLog->write(2,"[CInstanceHandler]-> Singleton Destroyed.");
    }

PhantomSDL_CINSTANCEHANDLER* PhantomSDL_CINSTANCEHANDLER::getInstance()
    {
    if ( PhantomSDL_CINSTANCEHANDLER::mInstance == 0 )
        {
        mInstance = new PhantomSDL_CINSTANCEHANDLER;
        }
    return mInstance;
    }

void PhantomSDL_CINSTANCEHANDLER::erase()
    {
    if( PhantomSDL_CINSTANCEHANDLER::mInstance != 0)
        {
        delete mInstance;
        }
    }

PhantomSDL_CINSTANCE* PhantomSDL_CINSTANCEHANDLER::getInstance(Uint32 instanceID)
    {
    std::list<PhantomSDL_CINSTANCE*>::iterator i;
    for(i = mInstances.begin(); i != mInstances.end(); i++)
        if((*i)->getID()==instanceID) return *i;
    }

void PhantomSDL_CINSTANCEHANDLER::addInstance(PhantomSDL_CINSTANCE *instance)
    {
    if(instance == NULL)
        {
        mLog->write(2,"[CInstanceHandler]-> trying to add a NULL pointer.");
        return;
        }
    mInstanceNumber++;
    mInstances.push_back(instance);
    instance->createEvent();
    mLog->write(2,"[CInstanceHandler]-> added an Instance with the following ID: %d .\n\t\t     Instance Number: %d",false,instance->getID(),mInstanceNumber);
    }

void PhantomSDL_CINSTANCEHANDLER::deleteInstance(PhantomSDL_CINSTANCE *instance)
    {
    if(instance == NULL)
        {
        mLog->write(2,"[CInstanceHandler]-> trying to delete a NULL pointer.");
        return;
        }
    if(mInstances.empty())
        {
        mLog->write(2,"[CInstanceHandler]-> no instances to delete.");
        return;
        }
    std::list<PhantomSDL_CINSTANCE*>::iterator i;
    for (i = mInstances.begin(); i != mInstances.end(); i++)
        {
        if ((*i) == instance)
            {
            Uint32 id=instance->getID();
            instance->destroyEvent();
            mInstances.erase(i);
            (*i) = NULL;
            instance = NULL;
            mInstanceNumber--;
            if(mInstanceNumber<0)
                {
                mLog->write(2,"[CInstanceHandler]-> trying to delete more instances than added. Breaking Loop.");
                break;
                }
            mLog->write(2,"[CInstanceHandler]-> deleted an Instance with the following ID: %d.",false,id);
            break;
            }
        }
    }

void PhantomSDL_CINSTANCEHANDLER::deleteAll()
    {
    if(mInstanceNumber < 1 && mInstances.empty())
        {
        mLog->write(2,"[CInstanceHandler]-> no instances to delete.");
        return;
        }
    std::list<PhantomSDL_CINSTANCE*>::iterator i;
    for(i=mInstances.begin(); i!=mInstances.end(); i++)
        {
		if (!(*i))
            {
			mLog->write(2,"[CInstanceHandler]-> trying to delete a NULL pointer.");
			continue ;
            }
		(*i)->destroyEvent();
		mLog->write(2,"[CInstanceHandler]-> deleted an Instance with the following ID: %d.",false,(*i)->getID());
        (*i) = NULL ;
        }
    mInstances.remove(NULL) ;
    mLog->write(2,"[CInstanceHandler]-> deleted all %d objects.",false,mInstanceNumber);
    mInstanceNumber = 0;
    }

void PhantomSDL_CINSTANCEHANDLER::step()
    {
    std::list<PhantomSDL_CINSTANCE*>::iterator i;
    for(i = mInstances.begin(); i != mInstances.end(); i++)
        {
        if( (*i) != NULL)
            {
            (*i)->stepEvent();
            if( (*i)->getVisible() ) (*i)->drawEvent();
            }
        else
            {
            mLog->write(2,"[CInstanceHandler]-> NULL pointer avoided.");
            }
        }
    }
