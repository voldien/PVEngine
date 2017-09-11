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
#ifndef _prerequisites_H_
#define _prerequisites_H_ 1
#include"Def.h"

/*	*/
class Resources;
class ResourceFactory;

/*	*/
class Config;
class Library;
class Debug;
class Profiler;

/*	*/
class Connection;
class NetWork;

/*	*/
class Material;
class Renderer;
class Light;
class Node;
class Frustum;
class Plane;
class Camera;
class Gizmo;
class Shape;
class Ray;
class Input;
class Time;

/*	*/
class SceneFactory;
class Scene;

/*	*/
class DynamicInterface;
class MapperObject;

/*	*/
class PhysicInterface;
class PhysicFactory;
class PhysicDispatcher;
class PhysicInterpreter;
class PhysicObject;
class RigidBody;
class Collision;
class Constraints;
class RayCastHit;

/*	*/
class RenderingFactory;
class RenderingInterface;
class RenderingPipeline;

/*	*/
class GraphicObject;
class TextureObject;
class BufferObject;
class GeometryObject;
class QueryObject;
class FontObject;
class ShaderObject;
class FrameBufferObject;
class PostEffectObject;


#endif
