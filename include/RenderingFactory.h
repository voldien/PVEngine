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
#ifndef _RENDERING_FACTORY_H_
#define _RENDERING_FACTORY_H_ 1
#include"System.h"
#include"Library.h"
#include"RenderingInterface.h"


/**
 *	Responsible for creating a rendering
 *	interface.
 */
class RenderingFactory{
public:

	enum RenderingAPI{
		eOpenGL,			/*	OpenGL rendering API.	*/
		eVulkan,			/*	Vulkan rendering API.	*/
		eDirectX,			/*	DirectX rendering API.	*/
	};

	/**
	 *	Create rendering interface
	 *
	 *	\renderingapi
	 *
	 *	\resources
	 *
	 *	@Return none NULL if successful.
	 */
	static RenderingInterface* createRendering(RenderingAPI renderingapi, Resources* resources, Config* config);

	/**
	 *	Create rendering interface
	 *
	 *	\cpathlib
	 *
	 *	\resources
	 *
	 *	@Return none NULL if successful.
	 */
	static RenderingInterface* createRendering(const char* cpathlib, Resources* resources, Config* config);


private:	/*	Prevent one from creating an instance of this class.	*/

	RenderingFactory(void);
	RenderingFactory(const RenderingFactory& other);
};


#endif
