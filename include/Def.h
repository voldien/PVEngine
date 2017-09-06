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
#ifndef _DEF_H_
#define _DEF_H_ 1
#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<errno.h>

/**
 *	Compiler version macro.
 */
#define PV_COMPILER_VERSION(major, minor, revision, state) PV_STR(major)PV_TEXT(".")PV_STR(minor)PV_TEXT(".")PV_STR(revision)

/**
 *    Compiler
 */
#ifdef _MSC_VER 	/*	Visual Studio C++ Compiler.	*/
	#define PV_VC
	#define PV_COMPILER 1
	#if _MSC_VER >= 1900
		#define PV_V13 _MSC_VER
	#elif _MSC_VER >= 1800
		#define PV_V12 _MSC_VER
	#elif _MSC_VER >= 1700
		#define PV_VC11 _MSC_VER
	#elif _MSC_VER >= 1600
		#define PV_VC10 _MSC_VER
	#elif _MSC_VER >= 1500
		#define PV_VC9 _MSC_VER
	#elif _MSC_VER >= 1400
		#define PV_VC8 _MSC_VER
	#elif _MSC_VER >= 1300
		#define PV_VC7 _MSC_VER
	#else
		#define PV_VC6 _MSC_VER
	#endif
    	#pragma warning(disable : 4201)
	#define PV_COMPILER_NAME "Visual Studio C++/C"

#elif defined(__clang__)  || defined(__llvm__)           /*  LLVM, clang   */
    #define PV_LLVM 1
	#define PV_CLANG 1
	#define PV_COMPILER 5
	#define PV_COMPILER_NAME "LLVM/CLANG"
	#define PV_COMPILER_MAJOR_VERSION __clang_major__
	#define PV_COMPILER_MINOR_VERSION __clang_minor__

#elif defined(__GNUC__) || defined(__SNC__) || defined( __GNUC_MINOR__)	/*  GNU C Compiler*/
	#define PV_GNUC 1
	#define PV_COMPILER 2
	#define PV_COMPILER_NAME "GNU C"
	#define PV_COMPILER_MAJOR_VERSION __clang_major__
	#define PV_COMPILER_MINOR_VERSION __clang_minor__

#elif defined(__GNUG__) /*  GNU C++ Compiler*/
	#define PV_GNUC 2

#elif defined(__ghs__)		/* GHS	*/
	#define PV_GHS 1
	#define PV_COMPILER 3

#elif defined(__HP_cc) || defined(__HP_aCC)			/*	*/

#elif defined(__PGI)			/*	*/

#elif defined(__ICC) || defined(__INTEL_COMPILER) /*  Intel Compiler  */
	#define PV_INTEL
	#define PV_COMPILER 4
	#define PV_COMPILER_NAME "Intel C++"

#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)

#else
	#error Unsupported Compiler.
#endif


#if defined(__GNUC__) && defined(__ARM_NEON__)
     /* GCC-compatible compiler, targeting ARM with NEON */
     #include <arm_neon.h>
#endif	/**/


/**
 *	Platform define
 *	Architecture!
 */
#ifdef PV_VC
	#if defined(_M_IX86) || defined(_WIN32)
		#define PV_X86                          /**/
		#define PV_X32                          /**/
		#define PV_WIN32                        /**/
		#define PV_WINDOWS                      /**/
	#elif defined(_M_X64) || defined(_WIN64)
		#define PV_X64                          /**/
		#define PV_WIN64                        /**/
		#define PV_WINDOWS                      /**/
	#elif defined(_M_PPC)
		#define PV_PPC                          /**/
		#define PV_X360                         /**/
		#define PV_VMX                          /**/
	#elif defined(_M_ARM)
		#define PV_ARM                          /**/
		#define PV_ARM_NEON                     /**/
	#endif
#elif defined(PV_GNUC) || defined(PV_CLANG)
	#ifdef __CELLOS_LV2__   /**/
        #define PV_PS3                          /*	playstation 3*/
	#elif defined(__arm__)	/**/
		#define PV_ARM
        #define PV_PSP2                         /*	playstation portable 2*/
        #define PV_RAS_PI                       /*	rasberry pi	*/
	#endif
	#if defined(_WIN32) /**  Window*/
		#define PV_X86
		#define PV_WINDOWS                      /**/
	#endif
	#if ( defined(__linux__) || defined(__linux) || defined(linux) ) && (!(__ANDROID__) || !(ANDROID))/* Linux */
		#define PV_LINUX 1                       /**/
		#if defined(__amd64) || defined(__x86_64__) || defined(__i386__)
            #define PV_X86 1
			#define PV_X86_64 1
		#endif
		#if defined(__arm__)
              #define EX_ARM 1
        #endif

	#elif defined (ANDROID) || defined(__ANDROID__) || __ANDROID_API__ > 9  /** Android */
        #include<jni.h>
		#define PV_ANDROID 1
		/*  android Architecture*/
        #if defined(__arm__)
			#define PV_ARM 1
		  #if defined(__ARM_ARCH_7A__)
			#if defined(__ARM_NEON__)
			  #if defined(__ARM_PCS_VFP)
				#define ABI "armeabi-v7a/NEON (hard-float)"
			  #else
				#define ABI "armeabi-v7a/NEON"
			  #endif
			#else
			  #if defined(__ARM_PCS_VFP)
				#define ABI "armeabi-v7a (hard-float)"
			  #else
				#define ABI "armeabi-v7a"
			  #endif
			#endif
		  #else
		   #define ABI "armeabi"
		  #endif
		#elif defined(__i386__)
		   #define ABI "x86"
		#elif defined(__x86_64__)
		   #define ABI "x86_64"
		#elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
		   #define ABI "mips64"
		#elif defined(__mips__)
		   #define ABI "mips"
		#elif defined(__aarch64__)
		   #define ABI "arm64-v8a"
		#else
		   #define ABI "unknown"
		#endif

	#elif defined (__APPLE__)   /*  Apple product   */
		#define PV_APPLE 1
		#if defined(__arm__)
			#define PV_APPLE_IOS    /*  Apple iphone/ipad OS    */
		#elif defined(MACOSX) || defined(macintosh) || defined(Macintosh)
			#define EX_MAC 1
		#endif
	#elif defined(__CYGWIN) 	/**/
		#define PV_CYGWIN 1
		#define PV_LINUX 1
	#elif defined(__FreeBSD__) || defined(__FreeBSD_kernel__)   /*  BSD*/
		#define PV_BSD
    	#elif defined(__llvm__) || defined(__clang__)   	/*  llvm    */
        	#define PV_LLVM 1
	#endif

#elif defined(__ICC) || defined(__INTEL_COMPILER)


#else
	#error  Unsupported architecture!   /*  No architecture support implicitly. remove this line to compile anyway*/
#endif

#if defined(__native_client__)	/*	nacl google	*/
	#define PV_NACL 1
#endif
#if defined(__pnacl__)          /* portable nacl google */
	#define PV_PNACL 1
#endif
#if defined(__unix__) || defined(__unix) || defined(unix)	/*  Unix    */
	#   define PV_UNIX 1
#endif



/**
 *	Calling function convention.
 */
#ifdef PV_WINDOWS	        /** Windows Calling Convention.*/
	#define PVAPIENTRY     __cdecl
	#define PVAPIFASTENTRY __fastcall
	#define PVAPITHISENTRY __thiscall
	#define PVAPISTDENTRY  __stdcall
#elif defined(PV_ANDROID)   /** Android Calling Convention	*/
    #define PVAPIENTRY JNICALL
    #define PVAPIFASTENTRY JNICALL
    #define PVAPITHISENTRY JNICALL
    #define PVAPISTDENTRY JNICALL
#else
#   if !defined(__cdecl) && ( defined(PV_GNUC)  || defined(PV_CLANG) )
        #define __cdecl  __attribute__ ((__cdecl__))
        #define __stdcall  __attribute__ ((stdcall))
		#define __fastcall __attribute__((fastcall))
#   endif
	#define PVAPIENTRY     __cdecl
	#define PVAPISTDENTRY  __stdcall
	#define PVAPIFASTENTRY __fastcall
#endif

/*
 *	force inline.
 */
#if defined(PV_MSVC)
	#define PV_ALWAYS_INLINE __forceinline
#elif defined(PV_GNUC)
	#define PV_ALWAYS_INLINE inline __attribute__((always_inline))
#elif defined(PV_GNUC) || defined(PV_GHS)
	#define PV_ALWAYS_INLINE inline __attribute__((always_inline))
#else
	/*#pragma message("Warning: You'd need to add PV_ALWAYS_INLINE for this compiler.")*/
#endif


/**
 *	Alignment of data and vectors.
 */
#if defined(PV_GNUC) || defined(PV_CLANG)
	#define PV_ALIGN(alignment) __attribute__ ((aligned(alignment)))
	#define PV_VECTORALIGN(alignment) __attribute__ ((__vector_size__ (alignment), __may_alias__))
	#define PV_VECTORALIGNI(alignment) __attribute__ ((__vector_size__ (alignment)))
#elif defined(PV_VC)
	#define PV_ALIGN(alignment) __attribute__ ((aligned(alignment)))
	#define PV_VECTORALIGN(alignment) __attribute__ ((__vector_size__ (alignment), __may_alias__))
	#define PV_VECTORALIGNI(alignment) __attribute__ ((__vector_size__ (alignment)))
#elif defined(PV_)
#endif



/**
 *	library declaration.
 */
#if defined(PV_GNUC) || defined(PV_CLANG)
	#if defined(PV_UNIX)
		#define PVDECLSPEC	 __attribute__((__visibility__ ("default")))
	#else
		#define PVDECLSPEC
	#endif
#elif defined(PV_VC)
	#if PV_INTERNAL
		#define PVDECLSPEC __declspec(dllexport)
	#else
		#define PVDECLSPEC __declspec(dllimport)
	#endif
#endif


#if defined(PV_ARM) || defined(PV_I386)

#endif


/**
 *	String macros.
 */
#define PV_STR_HELPER(x) #x										/*	String helper macro.*/
#define PV_STR(x) PV_STR_HELPER(x)								/*	Convert input to a double quoate string.	*/
#define PV_TEXT(quote) quote										/*	*/

#endif
