/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#include <cstring>

namespace BinaryData
{

//================== Makefile.am ==================
static const unsigned char temp_binary_data_0[] =
"## Process this file with automake to create Makefile.in\n"
"##\n"
"## This file is part of SoundTouch, an audio processing library for pitch/time adjustments\n"
"## \n"
"## SoundTouch is free software; you can redistribute it and/or modify it under the\n"
"## terms of the GNU General Public License as published by the Free Software\n"
"## Foundation; either version 2 of the License, or (at your option) any later\n"
"## version.\n"
"## \n"
"## SoundTouch is distributed in the hope that it will be useful, but WITHOUT ANY\n"
"## WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR\n"
"## A PARTICULAR PURPOSE.  See the GNU General Public License for more details.\n"
"## \n"
"## You should have received a copy of the GNU General Public License along with\n"
"## this program; if not, write to the Free Software Foundation, Inc., 59 Temple\n"
"## Place - Suite 330, Boston, MA  02111-1307, USA\n"
"\n"
"## I used config/am_include.mk for common definitions\n"
"include $(top_srcdir)/config/am_include.mk\n"
"\n"
"pkginclude_HEADERS=FIFOSampleBuffer.h FIFOSamplePipe.h SoundTouch.h STTypes.h BPMDetect.h soundtouch_config.h\n"
"\n";

const char* Makefile_am = (const char*) temp_binary_data_0;

//================== soundtouch_config.h.in ==================
static const unsigned char temp_binary_data_1[] =
"/* Use Float as Sample type */\n"
"#undef SOUNDTOUCH_FLOAT_SAMPLES\n"
"\n"
"/* Use Integer as Sample type */\n"
"#undef SOUNDTOUCH_INTEGER_SAMPLES\n"
"\n"
"/* Use ARM NEON extension */\n"
"#undef SOUNDTOUCH_USE_NEON\n";

const char* soundtouch_config_h_in = (const char*) temp_binary_data_1;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes);
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x1a187401:  numBytes = 1074; return Makefile_am;
        case 0x6fff950a:  numBytes = 188; return soundtouch_config_h_in;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "Makefile_am",
    "soundtouch_config_h_in"
};

const char* originalFilenames[] =
{
    "Makefile.am",
    "soundtouch_config.h.in"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
        if (strcmp (namedResourceList[i], resourceNameUTF8) == 0)
            return originalFilenames[i];

    return nullptr;
}

}
