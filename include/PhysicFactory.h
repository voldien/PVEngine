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
#ifndef _PHYSIC_FACTORY_H_
#define _PHYSIC_FACTORY_H_ 1
#include"PhysicInterface.h"

/**
 *	Responsible for creating the physic interface.
 */
class PhysicFactory{
public:
	enum PhysicAPI{
		eBullet,		/*	Bullet physic API.	*/
		eBullet3,		/*	Bullet3 physic API. support GPU acceleration.	*/
		ePhysx,			/*	Nvidia PhysicX.	*/
		eRPC,			/*	Remote procedure call. Used for off loading physic compution onto a server.	*/
	};

	/**
	 *	Create PhysicInterface object based on what API.
	 *
	 *	\api
	 *
	 *	\connection will connect to remote server. if NULL
	 *	it will attempt to create a local connection by creating
	 *	a physic interface that does not uses the socket communication.
	 *
	 *	\resource
	 *
	 *	@Return none NULL pointer if succesful.
	 */
	static PhysicInterface* createPhysic(PhysicAPI api, Resources* resource, Connection* connection, Config* config);

	/**
	 *	Load physicinterface by its library filename.
	 *
	 *	\libpath
	 *
	 *	\connection
	 *
	 *	@Return none NULL if successful.
	 */
	static PhysicInterface* createPhysic(const char* libpath, Resources* resource, Connection* connection, Config* config);


private:	/*	Prevent one from creating an instance of this class.	*/

	PhysicFactory(void);
	PhysicFactory(const PhysicFactory& other);

};

#endif
