/**
    Internal common glsl deceleration for the PVEngine.
    Copyright (C) 2017  Valdemar Lindberg

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

/*	Extension used.*/
#extension ARB_uniform_buffer_object : enable

/*	Check if mobile OpenGL is used.	*/
#ifdef GL_ES
precision mediump float;
precision mediump int;
#endif

/*	Translate fragment location decleration based on what version.	*/
#if __VERSION__ > 130
	#define FRAGLOCATION(x, vtype, name) layout(location = x) out vtype name
#elif __VERSION__ == 130
	#define FRAGLOCATION(x, vtype, name) out vtype name
#else
	#define FRAGLOCATION(x) 
#endif

/*	Translate based on glsl version.	*/
#if __VERSION__ > 130
	#define ATTRIBUTE_IN(x) layout(location = x) in 
	#define ATTRIBUTE_OUT(x) layout(location = x) out
#else
	#define ATTRIBUTE_IN(x) attribute
	#define ATTRIBUTE_OUT(x) attribute
#endif

/*	Translate based on glsl version.	*/
#if __VERSION__ > 120
	#define OUT out
	#define SMOOTH_OUT smooth out
	#define FLAT_OUT flat out
	#define IN in
	#define SMOOTH_IN smooth in
	#define FLAT_IN flat in
#else
	#define OUT varying
	#define SMOOTH_OUT smooth varying
	#define FLAT_IN flat varying
	#define IN varying
	#define SMOOTH_IN smooth varying
	#define FLAT_IN flat varying
#endif

/**
 *	Responsible for common 
 *	global variable shared across
 *	all shaders.
 */
struct global_uniform{

	mat4 projection;
	mat4 viewMatrix;
	mat4 viewProjection;
	mat4 viewRotMatrix;
	vec4 ambientColor;
	vec2 resolution;
	/*	*/
	vec4 cameraPosition;
	vec4 cameraDir;
	/*	*/	
	float time;
	float deltatime;
	float timescale;
	/*	*/
	float cameraNear;
	float cameraFar;
	float deltaTime;
	int numLights;
	int maxLights;
	int xpos;
	int ypos;
	int numShadows;
	 int shadow;
	/*	*/
	int numDirection;
	int numSpot;
	int numPoint;
	int numShadowDirection;
	int numShadowSpot;
	int numShadowPoint;
	int ambientType;
	float ambientIntensity;
	/*	*/
	float fogStart;
	float fogEnd;
	float fogHeight;
	int fogType;
	float fogDensity;
	vec4 fogColor;
	vec4 fogplane;
};

/**
 *	Shared uniform buffer.
 */
#if __VERSION__ > 130
layout(std140, shared) uniform globaluniform{
	global_uniform global;
};
#else
uniform global_uniform global;
#endif

/**
 *	Get current time in high precision in 
 *	seconds.
 */
float getTime(void){
        return global.time;
}

/**
 *	Get delta time since previous frame.
 */
float getDeltaTime(void){
        return global.deltaTime;
}

/**
 * Get screen resolution in pixels.
 */
vec2 getScreen(void){
        return global.resolution;
}

/**
 *	Get UV coordination of current pixel in
 *	fragment shader.
 */
vec2 getScreenUV(void){
#ifdef PV_FRAGMENT
       return gl_FragCoord.xy / getScreen();
#else
        return vec2(0); 
#endif
}

/**
 *	Get camera position in model space.
 */
vec3 getCameraPosition(void){
        return global.cameraPosition.xyz;
}

/**
 *	Get camera orientation direction.
 */
vec3 getCameraDirection(void){
        return global.cameraDir.xyz;
}

/**
 *	Get camera near frustum.
 */
float getCameraNear(void){
        return global.cameraNear;
}

/**
 *	Get camera far frustum.
 */
float getCameraFar(void){
        return global.cameraFar;
}

/**
 *	Get current view matrix.
 */
mat4 getViewMatrix(void){
        return global.viewMatrix;
}

/**
 *	Get projection matrix.
 */
mat4 getProjectionMatrix(void){
        return global.projection;
}

/**
 *	Get current project view matrix.
 */
mat4 getViewProjectionMatrix(void){
        return global.viewProjection;
}

/**
 *	Get view rotation matrix.
 *	Used with skybox.
 */
mat4 getViewRotationMatrix(void){
	return global.viewRotMatrix;
}

/**
 *
 */
#define FOGNONE		0x0	/*	*/
#define FOGLINEAR       0x1	/*	Get linear fog.	*/
#define FOGEXP          0x2	/*	*/
#define FOGEXP2         0x3	/*	*/
#define FOGHEIGHT       0x4	/*	*/

/**
 *	Compute fog intensity factor.	TODO optimize
 */
float getFogFactor(void){

    int fogtype = global.fogType;

	/*	Prevent unnecessary computation.	*/
	if(fogtype == 0)
		return 0.0;

    float near = getCameraNear();
    float far = getCameraFar();
    float endFog = global.fogEnd / (far - near);
    float startFog = global.fogStart  / (far - near);
    float densityFog =  global.fogDensity;
    /*      z normalized.   */
    #ifdef PV_FRAGMENT
    float z = getExpToLinear(near, far, gl_FragCoord.z );
    #else
    float z = 1.0;
    #endif
    
    switch(fogtype){
    case 1:
            return 1.0 - clamp( (endFog - z) / (endFog - startFog), 0.0, 1.0 );
    case 2:
            return 1.0 - clamp( exp( -(densityFog * z) ), 0.0, 1.0);
    case 3:
            return 1.0 - clamp( exp( - ( densityFog * z * densityFog * z) ) , 0.0, 1.0);
    case 4:
            float dist = z * (far - near);
            float b = 0.5;
            float c = 0.9;
            return clamp( c*exp(-getCameraPosition().y*b)*(1.0-exp(-dist*getCameraDirection().y*b))/getCameraDirection().y, 0.0, 1.0);
    default:
            return 0.0;
    }
}

/**
 *	Compute fog color and blend it with current 
 *	init color.
 */
vec4 internalFog(const in vec4 initColor){
    vec4 fogColor = global.fogColor;  
    return mix(initColor, fogColor, getFogFactor() ).rgba;
}

