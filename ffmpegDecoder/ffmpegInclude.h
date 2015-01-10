/*
 *  Include ffmpeg files
 */


#pragma once

#ifndef __STDC_CONSTANT_MACROS
  #define __STDC_CONSTANT_MACROS
#endif

//#include "stdint.h"
extern "C" 
{
#include <avcodec.h>
#include <avformat.h>
#include <swscale.h>
}