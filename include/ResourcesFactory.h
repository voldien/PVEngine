/**
    Simple physic simulation with a server-client model support.
    Copyright (C) 2016  Valdemar Lindberg

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _RESOURCE_FACTORY_H_
#define _RESOURCE_FACTORY_H_ 1
#include"Resources.h"

/**
 *	Responsible for creating a resource object
 *	and allocate the necessary data in respect
 *	what it's intended to be used.
 */
class ResourceFactory{
public:
	enum ResourceType{
		ePhysic 	= 0x1,      /*	Allocate all data needed for a physic interface.	*/
		eRenderer 	= 0x2,      /*	Allocate all data needed for the rendering interface.	*/
		eAll 		= ( ePhysic | eRenderer ),
	};

	/**
	 *	Create resource object.
	 *	It will create data pools for
	 *	scene and interface objects.
	 *
	 *	@Return	None null if successful.
	 */
	static Resources* createResources(ResourceType resourcetype = eAll);


private:	/*	Prevent one from creating an instance of this class.	*/

	ResourceFactory(void);
	ResourceFactory(const ResourceFactory& other);
};

#endif
