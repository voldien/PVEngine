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
#ifndef _RENDERING_PIPELINE_FACTORY_H_
#define _RENDERING_PIPELINE_FACTORY_H_ 1
#include"RenderPipelineBase.h"
#include"Prerequisites.h"

/**
 *	Responsible for creating rendering pipeline object.
 */
class RenderPipelineFactory{
public:

	enum RenderingPath{
		eForward = 0x1,		/*	*/
		eDeferred = 0x2,	/*	*/
	};

	/**
	 *	Create rendering pipeline.
	 *
	 *	@Return non-null if supported.
	 */
	static RenderPipelineBase* createRenderingPipeline(RenderingPath ePath);

private:	/*	Prevent one from creating an instance of this class.	*/

	RenderPipelineFactory(void);
	RenderPipelineFactory(const RenderPipelineFactory& other);
	~RenderPipelineFactory(void);

};



#endif
