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
#ifndef _SCENE_FACTORY_H_
#define _SCENE_FACTORY_H_
#include"Scene.h"

/**
 *	Responsible for creating scene object
 *	where object will be added in order for them
 *	be part of physic simulation and rendered to screen.
 */
class SceneFactory{
public:

	/**
	 *	Create scene.
	 *
	 *	\resources pointer to a resource object.
	 *
	 *	\rendering rendering interface assoicated with the scene.
	 *
	 *	@Return non-null scene.
	 */
	static Scene* createScene(Resources* __restrict__ resources,
			RenderingInterface* __restrict__ rendering);

private:	/*	Prevent one from creating an instance of this class.	*/

	SceneFactory(void);
	SceneFactory(const SceneFactory& other);
};


#endif
