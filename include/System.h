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
#ifndef _SYSTEM_H_
#define _SYSTEM_H_ 1
#include"Def.h"
#include"Prerequisites.h"

/*	Exceptions.	*/
#include"exception/NotImplementedException.h"

/*	C++ standard data type.	*/
#include<vector>
#include<map>
#include<list>

/*	Vector data types for rendering geometries.	*/
#include<hpmcpp/HC.h>
#include<hpmcpp/HCPlane.h>
#include<hpmcpp/HCVector2.h>

typedef HCVector3 PVVector3;
typedef HCVector4 PVVector4;
typedef HCVector2 PVVector2;
typedef HCMatrix4x4 PVMatrix4x4;
typedef HCMatrix3x3 PVMatrix3x3;
typedef HCQuaternion PVQuaternion;
typedef HCPlane PVPlane;
typedef HCAABB PVAABB;
typedef HCBoundingSphere PVBoundingSphere;
typedef HCRay PVRay;
typedef HCVector4 PVColor;

#endif
