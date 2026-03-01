/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   CMakeLists_txt;
    const int            CMakeLists_txtSize = 4243;

    extern const char*   CMakePresets_json;
    const int            CMakePresets_jsonSize = 4381;

    extern const char*   libbungee_pc_in;
    const int            libbungee_pc_inSize = 237;

    extern const char*   LICENSE;
    const int            LICENSESize = 17097;

    extern const char*   README_md;
    const int            README_mdSize = 13256;

    extern const char*   README_mdwaveform_png;
    const int            README_mdwaveform_pngSize = 17945;

    extern const char*   Makefile_am;
    const int            Makefile_amSize = 1074;

    extern const char*   soundtouch_config_h_in;
    const int            soundtouch_config_h_inSize = 188;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 8;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
