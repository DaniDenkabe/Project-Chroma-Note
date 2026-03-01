/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#include <cstring>

namespace BinaryData
{

//================== CMakeLists.txt ==================
static const unsigned char temp_binary_data_0[] =
"set(BUNGEE_VERSION 0.0.0 CACHE STRING \"Bungee version string\")\r\n"
"set(BUNGEE_SELF_TEST 0 CACHE STRING \"Enable Bungee self tests (0=off, 1=fast, 2=full)\")\r\n"
"option(BUNGEE_BUILD_SHARED_LIBRARY \"Build shared, dynamic Bungee library in addition to a static libary\" ON)\r\n"
"option(BUNGEE_INSTALL_FRAMEWORK \"Install as a framework\" OFF)\r\n"
"set(BUNGEE_PRESET \"\" CACHE STRING \"Name of the preset that we're building\")\r\n"
"\r\n"
"if (BUNGEE_BUILD_SHARED_LIBRARY)\r\n"
"  set(CMAKE_POSITION_INDEPENDENT_CODE ON)\r\n"
"endif()\r\n"
"\r\n"
"cmake_minimum_required(VERSION 3.30...3.31)\r\n"
"include(CheckCXXCompilerFlag)\r\n"
"\r\n"
"project(bungee VERSION ${BUNGEE_VERSION})\r\n"
"set(CMAKE_CXX_STANDARD 20)\r\n"
"\r\n"
"if (WIN32)\r\n"
"  set(BUNGEE_EXPORT \"__declspec(dllexport)\")\r\n"
"else()\r\n"
"  set(BUNGEE_EXPORT \"__attribute__((visibility(\\\"default\\\")))\")\r\n"
"endif()\r\n"
"\r\n"
"# Bungee library target: \"bungee_library\"\r\n"
"file(GLOB BUNGEE_LIBRARY_HEADERS \"${CMAKE_CURRENT_SOURCE_DIR}/bungee/*.h\")\r\n"
"file(GLOB BUNGEE_SOURCE_FILES \"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp\")\r\n"
"if (BUNGEE_BUILD_SHARED_LIBRARY)\r\n"
"  add_library(bungee_library SHARED ${BUNGEE_LIBRARY_HEADERS} ${BUNGEE_SOURCE_FILES})\r\n"
"else()\r\n"
"  add_library(bungee_library STATIC ${BUNGEE_LIBRARY_HEADERS} ${BUNGEE_SOURCE_FILES})\r\n"
"endif()  \r\n"
"target_include_directories(bungee_library PRIVATE  submodules/eigen submodules .)\r\n"
"target_compile_definitions(bungee_library PRIVATE\r\n"
"  BUNGEE_VISIBILITY=${BUNGEE_EXPORT}\r\n"
"  BUNGEE_SELF_TEST=${BUNGEE_SELF_TEST}\r\n"
"  eigen_assert=BUNGEE_ASSERT1\r\n"
"  EIGEN_DONT_PARALLELIZE=1\r\n"
"  $<$<CONFIG:Debug>:EIGEN_RUNTIME_NO_MALLOC=1>\r\n"
")\r\n"
"set_source_files_properties(${CMAKE_CURRENT_SOURCE_DIR}/src/version.cpp PROPERTIES COMPILE_DEFINITIONS BUNGEE_VERSION=\\\"${BUNGEE_VERSION}\\\")\r\n"
"target_compile_options(bungee_library PRIVATE $<$<CXX_COMPILER_ID:GNU,Clang>:-fwrapv>)\r\n"
"target_link_libraries(bungee_library PRIVATE pffft)\r\n"
"if (ANDROID)\r\n"
"  target_link_libraries(bungee_library PRIVATE log)\r\n"
"endif()\r\n"
"set_target_properties(bungee_library PROPERTIES OUTPUT_NAME bungee)\r\n"
"\r\n"
"# Bungee command-line executable target: \"bungee_executable\"\r\n"
"add_executable(bungee_executable cmd/main.cpp)\r\n"
"target_include_directories(bungee_executable PRIVATE submodules/cxxopts/include .)\r\n"
"target_link_libraries(bungee_executable PRIVATE bungee_library)\r\n"
"set_target_properties(bungee_executable PROPERTIES \r\n"
"  OUTPUT_NAME bungee\r\n"
"  INSTALL_RPATH \"${CMAKE_INSTALL_RPATH};${CMAKE_INSTALL_PREFIX}\"\r\n"
")\r\n"
"\r\n"
"# PFFFT as a static library\r\n"
"add_library(pffft EXCLUDE_FROM_ALL STATIC\r\n"
"  submodules/pffft/pffft.c\r\n"
"  submodules/pffft/fftpack.c\r\n"
")\r\n"
"target_compile_options(pffft PRIVATE -ffast-math -fno-finite-math-only -fno-exceptions)\r\n"
"\r\n"
"# Installation\r\n"
"if (BUNGEE_BUILD_SHARED_LIBRARY)\r\n"
"  if (BUNGEE_INSTALL_FRAMEWORK)\r\n"
"    set_target_properties(bungee_library PROPERTIES\r\n"
"      FRAMEWORK TRUE\r\n"
"      XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY \"iPhone Developer\"\r\n"
"      MACOSX_FRAMEWORK_BUNDLE_VERSION ${BUNGEE_VERSION}\r\n"
"      MACOSX_FRAMEWORK_SHORT_VERSION_STRING ${BUNGEE_VERSION}\r\n"
"      VERSION ${BUNGEE_VERSION}\r\n"
"    )\r\n"
"    set_source_files_properties(\r\n"
"      ${BUNGEE_LIBRARY_HEADERS} \r\n"
"      PROPERTIES\r\n"
"      MACOSX_PACKAGE_LOCATION Headers/bungee\r\n"
"    )\r\n"
"  endif()\r\n"
"  install(FILES \r\n"
"    ${BUNGEE_LIBRARY_HEADERS}\r\n"
"    DESTINATION ${CMAKE_INSTALL_PREFIX}/include/bungee\r\n"
"  )\r\n"
"  install(TARGETS bungee_library bungee_executable\r\n"
"    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/${BUNGEE_PRESET}\r\n"
"    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/${BUNGEE_PRESET}\r\n"
"    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${BUNGEE_PRESET}\r\n"
"    BUNDLE DESTINATION ${CMAKE_INSTALL_PREFIX}/${BUNGEE_PRESET}\r\n"
"    FRAMEWORK DESTINATION ${CMAKE_INSTALL_PREFIX}/${BUNGEE_PRESET}\r\n"
"  )\r\n"
"  install(FILES \r\n"
"    cmd/main.cpp  \r\n"
"    submodules/cxxopts/include/cxxopts.hpp\r\n"
"    DESTINATION ${CMAKE_INSTALL_PREFIX}/sample\r\n"
"  )\r\n"
"\r\n"
"get_property(BUNGEE_LIBRARY_OUTPUT_NAME TARGET bungee_library PROPERTY OUTPUT_NAME)\r\n"
"\r\n"
"if (APPLE)\r\n"
"  set(PKGCONFIG_LINK_PATH -F)\r\n"
"  set(PKGCONFIG_LINK_FLAG \"-framework \")\r\n"
"else()\r\n"
"  set(PKGCONFIG_LINK_PATH -L)\r\n"
"  set(PKGCONFIG_LINK_FLAG \"-I\")\r\n"
"endif()\r\n"
"configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libbungee.pc.in ${CMAKE_CURRENT_BINARY_DIR}/libbungee.pc @ONLY)\r\n"
"\r\n"
"install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libbungee.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/${BUNGEE_PRESET}/pkgconfig)\r\n"
"\r\n"
"endif()\r\n";

const char* CMakeLists_txt = (const char*) temp_binary_data_0;

//================== CMakePresets.json ==================
static const unsigned char temp_binary_data_1[] =
"{\r\n"
"    \"version\": 6,\r\n"
"    \"cmakeMinimumRequired\": {\r\n"
"        \"major\": 3,\r\n"
"        \"minor\": 25,\r\n"
"        \"patch\": 0\r\n"
"    },\r\n"
"    \"configurePresets\": [\r\n"
"        {\r\n"
"            \"name\": \"base\",\r\n"
"            \"hidden\": true,\r\n"
"            \"generator\": \"Ninja\",\r\n"
"            \"cacheVariables\": {\r\n"
"                \"BUNGEE_SELF_TEST\": \"0\",\r\n"
"                \"CMAKE_EXPORT_COMPILE_COMMANDS\": \"ON\"\r\n"
"            }\r\n"
"        },\r\n"
"        {\r\n"
"            \"name\": \"windows-x86_64\",\r\n"
"            \"inherits\": \"base\",\r\n"
"            \"cacheVariables\": {\r\n"
"                \"CMAKE_BUILD_TYPE\": \"Release\",\r\n"
"                \"CMAKE_SYSTEM_NAME\": \"Windows\",\r\n"
"                \"CMAKE_C_COMPILER\": \"x86_64-w64-mingw32-gcc\",\r\n"
"                \"CMAKE_CXX_COMPILER\": \"x86_64-w64-mingw32-g++\",\r\n"
"                \"CMAKE_FIND_ROOT_PATH_MODE_PROGRAM\": \"NEVER\",\r\n"
"                \"CMAKE_FIND_ROOT_PATH_MODE_INCLUDE\": \"ONLY\",\r\n"
"                \"CMAKE_EXE_LINKER_FLAGS\": \"-static-libgcc -static-libstdc++ -static \",\r\n"
"                \"CMAKE_SHARED_LINKER_FLAGS\": \"-static-libgcc -static-libstdc++ -static\",\r\n"
"                \"CMAKE_SHARED_LIBRARY_PREFIX_CXX\": \"\",\r\n"
"                \"CMAKE_IMPORT_LIBRARY_PREFIX_CXX\": \"\",\r\n"
"                \"CMAKE_IMPORT_LIBRARY_SUFFIX_CXX\": \".lib\"\r\n"
"            }\r\n"
"        },\r\n"
"        {\r\n"
"            \"name\": \"linux-x86_64\",\r\n"
"            \"inherits\": \"base\",\r\n"
"            \"cacheVariables\": {\r\n"
"                \"CMAKE_BUILD_TYPE\": \"Release\"\r\n"
"            }\r\n"
"        },\r\n"
"        {\r\n"
"            \"name\": \"linux-aarch64\",\r\n"
"            \"inherits\": \"base\",\r\n"
"            \"cacheVariables\": {\r\n"
"                \"CMAKE_BUILD_TYPE\": \"Release\",\r\n"
"                \"CMAKE_C_COMPILER\": \"aarch64-linux-gnu-gcc\",\r\n"
"                \"CMAKE_CXX_COMPILER\": \"aarch64-linux-gnu-g++\",\r\n"
"                \"CMAKE_STRIP\": \"aarch64-linux-gnu-strip\",\r\n"
"                \"CMAKE_FIND_ROOT_PATH_MODE_PROGRAM\": \"NEVER\",\r\n"
"                \"CMAKE_FIND_ROOT_PATH_MODE_LIBRARY\": \"ONLY\",\r\n"
"                \"CMAKE_FIND_ROOT_PATH_MODE_INCLUDE\": \"ONLY\"\r\n"
"            }\r\n"
"        },\r\n"
"        {\r\n"
"            \"name\": \"android\",\r\n"
"            \"hidden\": true,\r\n"
"            \"inherits\": \"base\",\r\n"
"            \"toolchainFile\": \"$env{ANDROID_NDK_LATEST_HOME}/build/cmake/android.toolchain.cmake\",\r\n"
"            \"cacheVariables\": {\r\n"
"                \"CMAKE_BUILD_TYPE\": \"Release\",\r\n"
"                \"ANDROID_TOOLCHAIN\": \"clang\",\r\n"
"                \"ANDROID_STL\": \"c++_static\",\r\n"
"                \"BUILD_SHARED_LIBS\": \"false\"\r\n"
"            }\r\n"
"        },\r\n"
"        {\r\n"
"            \"name\": \"android-armeabi-v7a\",\r\n"
"            \"inherits\": \"android\",\r\n"
"            \"cacheVariables\": {\r\n"
"                \"ANDROID_ABI\": \"armeabi-v7a\",\r\n"
"                \"ANDROID_PLATFORM\": \"android-16\"\r\n"
"            }\r\n"
"        },\r\n"
"        {\r\n"
"            \"name\": \"android-arm64-v8a\",\r\n"
"            \"inherits\": \"android\",\r\n"
"            \"cacheVariables\": {\r\n"
"                \"ANDROID_ABI\": \"arm64-v8a\",\r\n"
"                \"ANDROID_PLATFORM\": \"android-21\"\r\n"
"            }\r\n"
"        },\r\n"
"        {\r\n"
"            \"name\": \"android-x86\",\r\n"
"            \"inherits\": \"android\",\r\n"
"            \"cacheVariables\": {\r\n"
"                \"ANDROID_ABI\": \"x86\",\r\n"
"                \"ANDROID_PLATFORM\": \"android-16\"\r\n"
"            }\r\n"
"        },\r\n"
"        {\r\n"
"            \"name\": \"android-x86_64\",\r\n"
"            \"inherits\": \"android\",\r\n"
"            \"cacheVariables\": {\r\n"
"                \"ANDROID_ABI\": \"x86_64\",\r\n"
"                \"ANDROID_PLATFORM\": \"android-21\"\r\n"
"            }\r\n"
"        },\r\n"
"        {\r\n"
"            \"name\": \"apple\",\r\n"
"            \"hidden\": true,\r\n"
"            \"inherits\": \"base\",\r\n"
"            \"generator\": \"Xcode\",\r\n"
"            \"cacheVariables\": {\r\n"
"                \"BUNGEE_INSTALL_FRAMEWORK\": \"ON\",\r\n"
"                \"CMAKE_CONFIGURATION_TYPES\": \"Release\",\r\n"
"                \"CMAKE_XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER\": \"com.parabolaresearch.bungee\",\r\n"
"                \"CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_ALLOWED\": \"NO\"\r\n"
"            }\r\n"
"        },\r\n"
"        {\r\n"
"            \"name\": \"apple-mac\",\r\n"
"            \"inherits\": \"apple\",\r\n"
"            \"cacheVariables\": {\r\n"
"                \"CMAKE_SYSTEM_NAME\": \"Darwin\",\r\n"
"                \"CMAKE_OSX_ARCHITECTURES\": \"x86_64;arm64\",\r\n"
"                \"CMAKE_OSX_DEPLOYMENT_TARGET\": \"12.0\"\r\n"
"            }\r\n"
"        },\r\n"
"        {\r\n"
"            \"name\": \"apple-ios\",\r\n"
"            \"inherits\": \"apple\",\r\n"
"            \"cacheVariables\": {\r\n"
"                \"CMAKE_SYSTEM_NAME\": \"iOS\"\r\n"
"            }\r\n"
"        }\r\n"
"    ]\r\n"
"}";

const char* CMakePresets_json = (const char*) temp_binary_data_1;

//================== libbungee.pc.in ==================
static const unsigned char temp_binary_data_2[] =
"Name: bungee\r\n"
"Description: Bungee audio time-stretch and pitch-shift library\r\n"
"Version: @BUNGEE_VERSION@\r\n"
"Libs: @PKGCONFIG_LINK_PATH@${pcfiledir}/.. @PKGCONFIG_LINK_FLAG@@BUNGEE_LIBRARY_OUTPUT_NAME@\r\n"
"Cflags: -I${pcfiledir}/../../include\r\n";

const char* libbungee_pc_in = (const char*) temp_binary_data_2;

//================== LICENSE ==================
static const unsigned char temp_binary_data_3[] =
"Mozilla Public License Version 2.0\r\n"
"==================================\r\n"
"\r\n"
"1. Definitions\r\n"
"--------------\r\n"
"\r\n"
"1.1. \"Contributor\"\r\n"
"    means each individual or legal entity that creates, contributes to\r\n"
"    the creation of, or owns Covered Software.\r\n"
"\r\n"
"1.2. \"Contributor Version\"\r\n"
"    means the combination of the Contributions of others (if any) used\r\n"
"    by a Contributor and that particular Contributor's Contribution.\r\n"
"\r\n"
"1.3. \"Contribution\"\r\n"
"    means Covered Software of a particular Contributor.\r\n"
"\r\n"
"1.4. \"Covered Software\"\r\n"
"    means Source Code Form to which the initial Contributor has attached\r\n"
"    the notice in Exhibit A, the Executable Form of such Source Code\r\n"
"    Form, and Modifications of such Source Code Form, in each case\r\n"
"    including portions thereof.\r\n"
"\r\n"
"1.5. \"Incompatible With Secondary Licenses\"\r\n"
"    means\r\n"
"\r\n"
"    (a) that the initial Contributor has attached the notice described\r\n"
"        in Exhibit B to the Covered Software; or\r\n"
"\r\n"
"    (b) that the Covered Software was made available under the terms of\r\n"
"        version 1.1 or earlier of the License, but not also under the\r\n"
"        terms of a Secondary License.\r\n"
"\r\n"
"1.6. \"Executable Form\"\r\n"
"    means any form of the work other than Source Code Form.\r\n"
"\r\n"
"1.7. \"Larger Work\"\r\n"
"    means a work that combines Covered Software with other material, in\r\n"
"    a separate file or files, that is not Covered Software.\r\n"
"\r\n"
"1.8. \"License\"\r\n"
"    means this document.\r\n"
"\r\n"
"1.9. \"Licensable\"\r\n"
"    means having the right to grant, to the maximum extent possible,\r\n"
"    whether at the time of the initial grant or subsequently, any and\r\n"
"    all of the rights conveyed by this License.\r\n"
"\r\n"
"1.10. \"Modifications\"\r\n"
"    means any of the following:\r\n"
"\r\n"
"    (a) any file in Source Code Form that results from an addition to,\r\n"
"        deletion from, or modification of the contents of Covered\r\n"
"        Software; or\r\n"
"\r\n"
"    (b) any new file in Source Code Form that contains any Covered\r\n"
"        Software.\r\n"
"\r\n"
"1.11. \"Patent Claims\" of a Contributor\r\n"
"    means any patent claim(s), including without limitation, method,\r\n"
"    process, and apparatus claims, in any patent Licensable by such\r\n"
"    Contributor that would be infringed, but for the grant of the\r\n"
"    License, by the making, using, selling, offering for sale, having\r\n"
"    made, import, or transfer of either its Contributions or its\r\n"
"    Contributor Version.\r\n"
"\r\n"
"1.12. \"Secondary License\"\r\n"
"    means either the GNU General Public License, Version 2.0, the GNU\r\n"
"    Lesser General Public License, Version 2.1, the GNU Affero General\r\n"
"    Public License, Version 3.0, or any later versions of those\r\n"
"    licenses.\r\n"
"\r\n"
"1.13. \"Source Code Form\"\r\n"
"    means the form of the work preferred for making modifications.\r\n"
"\r\n"
"1.14. \"You\" (or \"Your\")\r\n"
"    means an individual or a legal entity exercising rights under this\r\n"
"    License. For legal entities, \"You\" includes any entity that\r\n"
"    controls, is controlled by, or is under common control with You. For\r\n"
"    purposes of this definition, \"control\" means (a) the power, direct\r\n"
"    or indirect, to cause the direction or management of such entity,\r\n"
"    whether by contract or otherwise, or (b) ownership of more than\r\n"
"    fifty percent (50%) of the outstanding shares or beneficial\r\n"
"    ownership of such entity.\r\n"
"\r\n"
"2. License Grants and Conditions\r\n"
"--------------------------------\r\n"
"\r\n"
"2.1. Grants\r\n"
"\r\n"
"Each Contributor hereby grants You a world-wide, royalty-free,\r\n"
"non-exclusive license:\r\n"
"\r\n"
"(a) under intellectual property rights (other than patent or trademark)\r\n"
"    Licensable by such Contributor to use, reproduce, make available,\r\n"
"    modify, display, perform, distribute, and otherwise exploit its\r\n"
"    Contributions, either on an unmodified basis, with Modifications, or\r\n"
"    as part of a Larger Work; and\r\n"
"\r\n"
"(b) under Patent Claims of such Contributor to make, use, sell, offer\r\n"
"    for sale, have made, import, and otherwise transfer either its\r\n"
"    Contributions or its Contributor Version.\r\n"
"\r\n"
"2.2. Effective Date\r\n"
"\r\n"
"The licenses granted in Section 2.1 with respect to any Contribution\r\n"
"become effective for each Contribution on the date the Contributor first\r\n"
"distributes such Contribution.\r\n"
"\r\n"
"2.3. Limitations on Grant Scope\r\n"
"\r\n"
"The licenses granted in this Section 2 are the only rights granted under\r\n"
"this License. No additional rights or licenses will be implied from the\r\n"
"distribution or licensing of Covered Software under this License.\r\n"
"Notwithstanding Section 2.1(b) above, no patent license is granted by a\r\n"
"Contributor:\r\n"
"\r\n"
"(a) for any code that a Contributor has removed from Covered Software;\r\n"
"    or\r\n"
"\r\n"
"(b) for infringements caused by: (i) Your and any other third party's\r\n"
"    modifications of Covered Software, or (ii) the combination of its\r\n"
"    Contributions with other software (except as part of its Contributor\r\n"
"    Version); or\r\n"
"\r\n"
"(c) under Patent Claims infringed by Covered Software in the absence of\r\n"
"    its Contributions.\r\n"
"\r\n"
"This License does not grant any rights in the trademarks, service marks,\r\n"
"or logos of any Contributor (except as may be necessary to comply with\r\n"
"the notice requirements in Section 3.4).\r\n"
"\r\n"
"2.4. Subsequent Licenses\r\n"
"\r\n"
"No Contributor makes additional grants as a result of Your choice to\r\n"
"distribute the Covered Software under a subsequent version of this\r\n"
"License (see Section 10.2) or under the terms of a Secondary License (if\r\n"
"permitted under the terms of Section 3.3).\r\n"
"\r\n"
"2.5. Representation\r\n"
"\r\n"
"Each Contributor represents that the Contributor believes its\r\n"
"Contributions are its original creation(s) or it has sufficient rights\r\n"
"to grant the rights to its Contributions conveyed by this License.\r\n"
"\r\n"
"2.6. Fair Use\r\n"
"\r\n"
"This License is not intended to limit any rights You have under\r\n"
"applicable copyright doctrines of fair use, fair dealing, or other\r\n"
"equivalents.\r\n"
"\r\n"
"2.7. Conditions\r\n"
"\r\n"
"Sections 3.1, 3.2, 3.3, and 3.4 are conditions of the licenses granted\r\n"
"in Section 2.1.\r\n"
"\r\n"
"3. Responsibilities\r\n"
"-------------------\r\n"
"\r\n"
"3.1. Distribution of Source Form\r\n"
"\r\n"
"All distribution of Covered Software in Source Code Form, including any\r\n"
"Modifications that You create or to which You contribute, must be under\r\n"
"the terms of this License. You must inform recipients that the Source\r\n"
"Code Form of the Covered Software is governed by the terms of this\r\n"
"License, and how they can obtain a copy of this License. You may not\r\n"
"attempt to alter or restrict the recipients' rights in the Source Code\r\n"
"Form.\r\n"
"\r\n"
"3.2. Distribution of Executable Form\r\n"
"\r\n"
"If You distribute Covered Software in Executable Form then:\r\n"
"\r\n"
"(a) such Covered Software must also be made available in Source Code\r\n"
"    Form, as described in Section 3.1, and You must inform recipients of\r\n"
"    the Executable Form how they can obtain a copy of such Source Code\r\n"
"    Form by reasonable means in a timely manner, at a charge no more\r\n"
"    than the cost of distribution to the recipient; and\r\n"
"\r\n"
"(b) You may distribute such Executable Form under the terms of this\r\n"
"    License, or sublicense it under different terms, provided that the\r\n"
"    license for the Executable Form does not attempt to limit or alter\r\n"
"    the recipients' rights in the Source Code Form under this License.\r\n"
"\r\n"
"3.3. Distribution of a Larger Work\r\n"
"\r\n"
"You may create and distribute a Larger Work under terms of Your choice,\r\n"
"provided that You also comply with the requirements of this License for\r\n"
"the Covered Software. If the Larger Work is a combination of Covered\r\n"
"Software with a work governed by one or more Secondary Licenses, and the\r\n"
"Covered Software is not Incompatible With Secondary Licenses, this\r\n"
"License permits You to additionally distribute such Covered Software\r\n"
"under the terms of such Secondary License(s), so that the recipient of\r\n"
"the Larger Work may, at their option, further distribute the Covered\r\n"
"Software under the terms of either this License or such Secondary\r\n"
"License(s).\r\n"
"\r\n"
"3.4. Notices\r\n"
"\r\n"
"You may not remove or alter the substance of any license notices\r\n"
"(including copyright notices, patent notices, disclaimers of warranty,\r\n"
"or limitations of liability) contained within the Source Code Form of\r\n"
"the Covered Software, except that You may alter any license notices to\r\n"
"the extent required to remedy known factual inaccuracies.\r\n"
"\r\n"
"3.5. Application of Additional Terms\r\n"
"\r\n"
"You may choose to offer, and to charge a fee for, warranty, support,\r\n"
"indemnity or liability obligations to one or more recipients of Covered\r\n"
"Software. However, You may do so only on Your own behalf, and not on\r\n"
"behalf of any Contributor. You must make it absolutely clear that any\r\n"
"such warranty, support, indemnity, or liability obligation is offered by\r\n"
"You alone, and You hereby agree to indemnify every Contributor for any\r\n"
"liability incurred by such Contributor as a result of warranty, support,\r\n"
"indemnity or liability terms You offer. You may include additional\r\n"
"disclaimers of warranty and limitations of liability specific to any\r\n"
"jurisdiction.\r\n"
"\r\n"
"4. Inability to Comply Due to Statute or Regulation\r\n"
"---------------------------------------------------\r\n"
"\r\n"
"If it is impossible for You to comply with any of the terms of this\r\n"
"License with respect to some or all of the Covered Software due to\r\n"
"statute, judicial order, or regulation then You must: (a) comply with\r\n"
"the terms of this License to the maximum extent possible; and (b)\r\n"
"describe the limitations and the code they affect. Such description must\r\n"
"be placed in a text file included with all distributions of the Covered\r\n"
"Software under this License. Except to the extent prohibited by statute\r\n"
"or regulation, such description must be sufficiently detailed for a\r\n"
"recipient of ordinary skill to be able to understand it.\r\n"
"\r\n"
"5. Termination\r\n"
"--------------\r\n"
"\r\n"
"5.1. The rights granted under this License will terminate automatically\r\n"
"if You fail to comply with any of its terms. However, if You become\r\n"
"compliant, then the rights granted under this License from a particular\r\n"
"Contributor are reinstated (a) provisionally, unless and until such\r\n"
"Contributor explicitly and finally terminates Your grants, and (b) on an\r\n"
"ongoing basis, if such Contributor fails to notify You of the\r\n"
"non-compliance by some reasonable means prior to 60 days after You have\r\n"
"come back into compliance. Moreover, Your grants from a particular\r\n"
"Contributor are reinstated on an ongoing basis if such Contributor\r\n"
"notifies You of the non-compliance by some reasonable means, this is the\r\n"
"first time You have received notice of non-compliance with this License\r\n"
"from such Contributor, and You become compliant prior to 30 days after\r\n"
"Your receipt of the notice.\r\n"
"\r\n"
"5.2. If You initiate litigation against any entity by asserting a patent\r\n"
"infringement claim (excluding declaratory judgment actions,\r\n"
"counter-claims, and cross-claims) alleging that a Contributor Version\r\n"
"directly or indirectly infringes any patent, then the rights granted to\r\n"
"You by any and all Contributors for the Covered Software under Section\r\n"
"2.1 of this License shall terminate.\r\n"
"\r\n"
"5.3. In the event of termination under Sections 5.1 or 5.2 above, all\r\n"
"end user license agreements (excluding distributors and resellers) which\r\n"
"have been validly granted by You or Your distributors under this License\r\n"
"prior to termination shall survive termination.\r\n"
"\r\n"
"************************************************************************\r\n"
"*                                                                      *\r\n"
"*  6. Disclaimer of Warranty                                           *\r\n"
"*  -------------------------                                           *\r\n"
"*                                                                      *\r\n"
"*  Covered Software is provided under this License on an \"as is\"       *\r\n"
"*  basis, without warranty of any kind, either expressed, implied, or  *\r\n"
"*  statutory, including, without limitation, warranties that the       *\r\n"
"*  Covered Software is free of defects, merchantable, fit for a        *\r\n"
"*  particular purpose or non-infringing. The entire risk as to the     *\r\n"
"*  quality and performance of the Covered Software is with You.        *\r\n"
"*  Should any Covered Software prove defective in any respect, You     *\r\n"
"*  (not any Contributor) assume the cost of any necessary servicing,   *\r\n"
"*  repair, or correction. This disclaimer of warranty constitutes an   *\r\n"
"*  essential part of this License. No use of any Covered Software is   *\r\n"
"*  authorized under this License except under this disclaimer.         *\r\n"
"*                                                                      *\r\n"
"************************************************************************\r\n"
"\r\n"
"************************************************************************\r\n"
"*                                                                      *\r\n"
"*  7. Limitation of Liability                                          *\r\n"
"*  --------------------------                                          *\r\n"
"*                                                                      *\r\n"
"*  Under no circumstances and under no legal theory, whether tort      *\r\n"
"*  (including negligence), contract, or otherwise, shall any           *\r\n"
"*  Contributor, or anyone who distributes Covered Software as          *\r\n"
"*  permitted above, be liable to You for any direct, indirect,         *\r\n"
"*  special, incidental, or consequential damages of any character      *\r\n"
"*  including, without limitation, damages for lost profits, loss of    *\r\n"
"*  goodwill, work stoppage, computer failure or malfunction, or any    *\r\n"
"*  and all other commercial damages or losses, even if such party      *\r\n"
"*  shall have been informed of the possibility of such damages. This   *\r\n"
"*  limitation of liability shall not apply to liability for death or   *\r\n"
"*  personal injury resulting from such party's negligence to the       *\r\n"
"*  extent applicable law prohibits such limitation. Some               *\r\n"
"*  jurisdictions do not allow the exclusion or limitation of           *\r\n"
"*  incidental or consequential damages, so this exclusion and          *\r\n"
"*  limitation may not apply to You.                                    *\r\n"
"*                                                                      *\r\n"
"************************************************************************\r\n"
"\r\n"
"8. Litigation\r\n"
"-------------\r\n"
"\r\n"
"Any litigation relating to this License may be brought only in the\r\n"
"courts of a jurisdiction where the defendant maintains its principal\r\n"
"place of business and such litigation shall be governed by laws of that\r\n"
"jurisdiction, without reference to its conflict-of-law provisions.\r\n"
"Nothing in this Section shall prevent a party's ability to bring\r\n"
"cross-claims or counter-claims.\r\n"
"\r\n"
"9. Miscellaneous\r\n"
"----------------\r\n"
"\r\n"
"This License represents the complete agreement concerning the subject\r\n"
"matter hereof. If any provision of this License is held to be\r\n"
"unenforceable, such provision shall be reformed only to the extent\r\n"
"necessary to make it enforceable. Any law or regulation which provides\r\n"
"that the language of a contract shall be construed against the drafter\r\n"
"shall not be used to construe this License against a Contributor.\r\n"
"\r\n"
"10. Versions of the License\r\n"
"---------------------------\r\n"
"\r\n"
"10.1. New Versions\r\n"
"\r\n"
"Mozilla Foundation is the license steward. Except as provided in Section\r\n"
"10.3, no one other than the license steward has the right to modify or\r\n"
"publish new versions of this License. Each version will be given a\r\n"
"distinguishing version number.\r\n"
"\r\n"
"10.2. Effect of New Versions\r\n"
"\r\n"
"You may distribute the Covered Software under the terms of the version\r\n"
"of the License under which You originally received the Covered Software,\r\n"
"or under the terms of any subsequent version published by the license\r\n"
"steward.\r\n"
"\r\n"
"10.3. Modified Versions\r\n"
"\r\n"
"If you create software not governed by this License, and you want to\r\n"
"create a new license for such software, you may create and use a\r\n"
"modified version of this License if you rename the license and remove\r\n"
"any references to the name of the license steward (except to note that\r\n"
"such modified license differs from this License).\r\n"
"\r\n"
"10.4. Distributing Source Code Form that is Incompatible With Secondary\r\n"
"Licenses\r\n"
"\r\n"
"If You choose to distribute Source Code Form that is Incompatible With\r\n"
"Secondary Licenses under the terms of this version of the License, the\r\n"
"notice described in Exhibit B of this License must be attached.\r\n"
"\r\n"
"Exhibit A - Source Code Form License Notice\r\n"
"-------------------------------------------\r\n"
"\r\n"
"  This Source Code Form is subject to the terms of the Mozilla Public\r\n"
"  License, v. 2.0. If a copy of the MPL was not distributed with this\r\n"
"  file, You can obtain one at https://mozilla.org/MPL/2.0/.\r\n"
"\r\n"
"If it is not possible or desirable to put the notice in a particular\r\n"
"file, then You may include the notice in a location (such as a LICENSE\r\n"
"file in a relevant directory) where a recipient would be likely to look\r\n"
"for such a notice.\r\n"
"\r\n"
"You may add additional accurate notices of copyright ownership.\r\n"
"\r\n"
"Exhibit B - \"Incompatible With Secondary Licenses\" Notice\r\n"
"---------------------------------------------------------\r\n"
"\r\n"
"  This Source Code Form is \"Incompatible With Secondary Licenses\", as\r\n"
"  defined by the Mozilla Public License, v. 2.0.";

const char* LICENSE = (const char*) temp_binary_data_3;

//================== README.md ==================
static const unsigned char temp_binary_data_4[] =
"# Bungee: Audio Time-Stretching & Pitch-Shifting Library\r\n"
"\r\n"
"Bungee is a modern, open-source C++ library for high-quality audio time-stretching and pitch-shifting in real-time or offline. It brings powerful audio timescale processing to your application.\r\n"
"\r\n"
"Bungee can adjust the speed of audio without affecting pitch; transpose audio pitch without affecting speed; or apply any combination of playhead position and pitch manipulation.\r\n"
"* Simple, fast phase-vocoder-based algorithm with good quality audio output (\xf0\x9f\x8e\xa7  hear [some comparisons](https://bungee.parabolaresearch.com/compare-audio-stretch-tempo-pitch-change.html) with other algorithms)\r\n"
"* Modern C++ for clean and resilient code\r\n"
"\r\n"
"Bungee is unique in its controllability, allowing continually changing audio tempo and pitch manipulation with seamless support of zero and negative playback speeds. So it can be used for a \"smooth scrub\" or for rendering lifelike audio for slow-mo"
"tion videos.\r\n"
"\r\n"
"Bungee is often used for slowing down music or speeding up speech without affecting pitch. It is also popular in music software for changing tempo, transposing and other effects.\r\n"
"\r\n"
" \xe2\xad\x90\xef\xb8\x8f _To support Bungee, please consider [giving this repo a star](https://github.com/bungee-audio-stretch/bungee/stargazers)_ .\r\n"
"\r\n"
"![GitHub Release](https://img.shields.io/github/v/release/bungee-audio-stretch/bungee)\r\n"
"![GitHub License](https://img.shields.io/github/license/bungee-audio-stretch/bungee)\r\n"
"![GitHub Downloads](https://img.shields.io/github/downloads/bungee-audio-stretch/bungee/total)\r\n"
"![GitHub Repo stars](https://img.shields.io/github/stars/bungee-audio-stretch/bungee)\r\n"
"\r\n"
"## Getting started with Bungee Audio Time-Stretching\r\n"
"\r\n"
"### Clone and Build\r\n"
"\r\n"
"Bungee's dependencies are managed as git submodules; so clone like this:\r\n"
"```\r\n"
"git clone --recurse-submodules https://github.com/bungee-audio-stretch/bungee\r\n"
"```\r\n"
"\r\n"
"Use CMake to configure and build the bungee library and command-line executable:\r\n"
"```\r\n"
"cd bungee\r\n"
"mkdir build && cd build\r\n"
"cmake ..\r\n"
"cmake --build .\r\n"
"```\r\n"
"\r\n"
"After a successful build, try the bungee executable\r\n"
"```\r\n"
"./bungee --help\r\n"
"```\r\n"
"### Pre-built Releases\r\n"
"\r\n"
"Every commit pushed to this repo's main branch is automatically tagged and built into a release. Each release contains Bungee built as a shared library together with headers, sample code and a sample command-line executable that uses the shared libra"
"ry. Releases support common platforms including Linux, Windows, MacOS, Android and iOS.\r\n"
"\r\n"
"\r\n"
"## Integrating Bungee C++ Audio Library\r\n"
"\r\n"
"Bungee operates on discrete, overlapping \"grains\" of audio, typically processing around 100 grains per second. Parameters such as position and pitch are provided on a per-grain basis so that they can be changed continuously as audio rendering progr"
"esses.\r\n"
"\r\n"
"The Bungee API supports two modes of operation: \"granular\" and \"streaming\". Both modes offer identical audio quality and similar CPU performance. Developers should select the mode that best suits the needs of their application.\r\n"
"\r\n"
"| Mode | Granular | Streaming |\r\n"
"|--|--|--|\r\n"
"| `#include` | `<bungee/Bungee.h>` | `<bungee/Stream.h>` |\r\n"
"| Description | Fundamental, low-level interface. | Simplified API built atop the granular interface. |\r\n"
"| Operation | The caller iterates over a \"granular loop\" where they control exactly what happens at each of the Bungee grains. | The granular nature of the underlying library is hidden and the caller instead manages an input audio stream and an out"
"put audio stream. Iterations are over \"chunks\" of audio that need not map to the underlying grains. |\r\n"
"| Benefits | Allows any arbritrary movements within the input audio: play at any speed, reverse play, infinite stretch, trick play. Lowest latency and no additional data copies | Simpler \"FIFO\" operation, more similar to traditional \"linear playba"
"ck\" audio processing code. Designed to be easy to integrate to frameworks such as JUCE and FFmpeg.  |\r\n"
"| Restrictions | | Supports only forward playback.|\r\n"
"| Example | [cmd/main.cpp](./cmd/main.cpp) with `--push 0` | [cmd/main.cpp](./cmd/main.cpp)  when `--push` has a non-zero value |\r\n"
"\r\n"
"\r\n"
"### Granular Audio Time-Stretching and Pitch-Shifting Example\r\n"
"\r\n"
"#### Instantiation for Granular Processing\r\n"
"\r\n"
"``` C++\r\n"
"#include <bungee/Bungee.h>\r\n"
"```\r\n"
"``` C++\r\n"
"// Define stretcher input and output sample rates\r\n"
"const Bungee::SampleRates sampleRates{44100, 44100};\r\n"
"\r\n"
"// Instantiate a stretcher for two-channel (stereo) operation.\r\n"
"Bungee::Stretcher<Bungee::Basic> stretcher(sampleRates, 2);\r\n"
"\r\n"
"// Enable instrumentation. When done debugging, this can be removed.\r\n"
"stretcher.enableInstrumentation(true);\r\n"
"\r\n"
"Bungee::Request request{};\r\n"
"\r\n"
"// Set pitch, this example shows an upward transposition of one semitone.\r\n"
"request.pitch = std::pow(2., 1. / 12.);\r\n"
"\r\n"
"// Set initial speed, this example shows how to achieve constant 75% output speed.\r\n"
"request.speed = 0.75;\r\n"
"\r\n"
"// Set initial starting position at 0.5 seconds offset from the start of the input buffer.\r\n"
"request.position = 0.5 * sampleRate;\r\n"
"\r\n"
"// This call adjusts request.position so that stretcher's pipeline will be fully initialised by the\r\n"
"// time it reaches the starting position of 0.5 seconds offset.\r\n"
"stretcher.preroll(request);\r\n"
"```\r\n"
"\r\n"
"#### Granular Loop\r\n"
"\r\n"
"`Stretcher`'s processing functions are typically called from within a loop, each iteration of which corresponds to a grain of audio. For each grain, the functions `Stretcher<Basic>::specifyGrain`, `Stretcher<Basic>::analyseGain` and `Stretcher<Basic>"
"::synthesiseGrain` should be called in sequence.\r\n"
"```C++\r\n"
"while (true)\r\n"
"{\r\n"
"    // ...\r\n"
"    // Change request's members, for example, position, speed or pitch, as required here.\r\n"
"    // ...\r\n"
" \r\n"
"    auto inputChunk = stretcher.specifyGrain(request);\r\n"
"\r\n"
"    // ...\r\n"
"    // Examine inputChunk and retrieve the segment of input audio that the stretcher requires here.\r\n"
"    // Set data and channelStride to point to the required segment of input data.\r\n"
"    // ...\r\n"
"\r\n"
"    stretcher.analyseGrain(data, channelStride);\r\n"
"\r\n"
"    Bungee::OutputChunk outputChunk;\r\n"
"    stretcher.synthesiseGrain(outputChunk);\r\n"
"\r\n"
"    // ...\r\n"
"    // Output the audio buffer indicated by outputChunk here.\r\n"
"    // ...\r\n"
"\r\n"
"    // Prepare request for the next grain (modifies request.position according to request.speed)\r\n"
"    stretcher.next(request);\r\n"
"}\r\n"
"```\r\n"
"\r\n"
"#### Granular Notes\r\n"
"\r\n"
"* `Request::position` is a timestamp, it defines the grain centre point in terms of an input audio frame offset. It is the primary control for speed adjustments and is also the driver for seek and scrub operations. The caller is responsible for decid"
"ing  `Request::position` for each grain. \r\n"
"\r\n"
"* The caller owns the input audio buffer and must provide the audio segment indicated by `InputChunk`. Successive grains' input audio chunks may overlap. The `Stretcher<Basic>` instance reads in the input chunk data when `Stretcher<Basic>::analyseGra"
"in` is called.\r\n"
"\r\n"
"* The `Stretcher<Basic>` instance owns the output audio buffer. It is valid from when `Stretcher<Basic>::synthesiseGrain` returns up until `Stretcher<Basic>::synthesiseGrain` is called for the subsequent grain. Output audio chunks do not overlap: the"
"y should be concatenated to produce an output audio stream.\r\n"
"\r\n"
"* Output audio is timestamped. The original `Request` objects corresponding to the start and end of the chunk are provided by `OutputChunk`.\r\n"
"\r\n"
"### Streaming Audio Time-Stretching and Pitch-Shifting Example\r\n"
"\r\n"
"#### Streaming Instantiation\r\n"
"\r\n"
"``` C++\r\n"
"#include <bungee/Stream.h>\r\n"
"```\r\n"
"\r\n"
"``` C++\r\n"
"// Define stretcher input and output sample rates\r\n"
"const Bungee::SampleRates sampleRates{44100, 44100};\r\n"
"const auto channelCount = 2;\r\n"
"\r\n"
"// What is the maximum number of input \r\n"
"const auto maxInputFrameCount = 1024; // for example\r\n"
"\r\n"
"// Instantiate a stretcher.\r\n"
"Bungee::Stretcher<Bungee::Basic> stretcher(sampleRates, channelCount);\r\n"
"\r\n"
"// Enable instrumentation. When done debugging, this can be removed.\r\n"
"stretcher.enableInstrumentation(true);\r\n"
"\r\n"
"// Instantiate a Stream object.\r\n"
"Bungee::Stream<Bungee::Basic> stream(stretcher, maxInputFrameCount, channelCount);\r\n"
"```\r\n"
"\r\n"
"#### Streaming Loop\r\n"
"\r\n"
"```C++\r\n"
"while (true)\r\n"
"{\r\n"
"    // Each iteration of this loop processes the next contiguous chunk of audio data.\r\n"
"\r\n"
"    std::vector<const float *> inputChannelPointers(channelCount);\r\n"
"    int inputSampleCount;\r\n"
"\r\n"
"    std::vector<float *> outputChannelPointers(channelCount);\r\n"
"\r\n"
"    // ...\r\n"
"    // Insert code here to: \r\n"
"    // 1. Receive the next chunk of input audio, set inputChannelPointers and inputSampleCount accordingly\r\n"
"    // 2. Set outputChannelPointers to a user maintained buffer where output audio should be written by Bungee.\r\n"
"    // ...\r\n"
"\r\n"
"    // Set these control variables as desired.\r\n"
"    const double speed=1., pitch=1.;\r\n"
"\r\n"
"    const double outputFrameCountIdeal = (inputSampleCount * sampleRates.output) / (speed * sampleRates.input);\r\n"
"\r\n"
"    // This call does the stretching.\r\n"
"    const auto outputFrameCountActual = stream.process(inputChannelPointers.data(), outputChannelPointers.data(), inputSampleCount, outputFrameCountIdeal, pitch);\r\n"
"\r\n"
"    // ...\r\n"
"    // Place code to handle output of the time-stretched / pitch-shifted audio.\r\n"
"    // The processed audio resides in memory at the buffer indicated by outputChannelPointers \r\n"
"    // and each channel will have outputFrameCountActual samples of new audio.\r\n"
"    // ...\r\n"
"}\r\n"
"```\r\n"
"### Streaming Notes\r\n"
"* The caller specifies its desired output audio speed (tempo) by the value of `outputFrameCountIdeal` above. Because the stretcher cannot output a fractional number of audio frames, `outputFrameCountActual` will be returned as one of the two closest "
"integral values to `outputFrameCountIdeal`.\r\n"
"\r\n"
"\r\n"
"## General Bungee C++ API Notes\r\n"
"\r\n"
"* In Bungee code and API, a \"frame\" refers to a single time-aligned set of audio samples\xe2\x80\x94one sample from each channel at a specific point in time. For example, in stereo audio, a frame consists of one left and one right sample occurring "
"simultaneously.\r\n"
"\r\n"
"* Bungee is most commonly used for stereo and mono operation at sample rates of 44.1kHz and 48kHz. In principle, though, any practical sample rate and number of audio channels are supported and results should be similar.\r\n"
"\r\n"
"* Bungee works with 32-bit floating point audio samples and expects sample values in the range -1 to +1 on both input and output. The algorithm performs no clipping.\r\n"
"\r\n"
"* When configured for 1x speed and no pitch adjustment, the difference between input and output signals should be small: minor windowing discrepencies only.\r\n"
"\r\n"
"* Any special or non-numeric float values such as NaN or infinity within the input audio may disrupt or cause loss of output audio.\r\n"
"\r\n"
"* It is strongly recommended to enable Bungee's internal instrumentation whem working on the integration of the Bungee API. The instrumentation is particuarly helpful for the granular mode of operation because it can detect common usage errors.\r\n"
"\r\n"
"## Bungee's Dependencies\r\n"
"\r\n"
"The Bungee library gratefully depends on:\r\n"
"* The Eigen C++ library for buffer management and mathematical operations on vectors and arrays\r\n"
"* The PFFFT library for Fast Fourier Transforms\r\n"
"\r\n"
"The sample `bungee` command-line utility also uses:\r\n"
"* cxxopts library for parsing command-line options\r\n"
"\r\n"
"See this repo's [.gitmodules](.gitmodules) file for versioned links to these projects.\r\n"
"\r\n"
"## Bungee License\r\n"
"\r\n"
"Bungee is permissively licensed under the Mozilla Public License Version 2.0. \r\n"
"\r\n"
"## Bungee Support\r\n"
"\r\n"
"Bungee's goal is to be the _best open source audio timescale manipulation library_ available. User feedback is invaluable: please use Github issues or contact the team directly to report anything that could be improved.\r\n"
"\r\n"
"> # Bungee Pro\r\n"
"> \r\n"
"> Bungee Pro is a commercial product providing an upgrade path from the open-source Bungee audio time stretcher. It uses proprietary new algorithms for sharp and clear professional-grade audio and runs at least as fast as Bungee, thanks to platform-s"
"pecific performance optimisations.\r\n"
"> \r\n"
"> Whilst open-source Bungee aims to be the best open-source audio time-stretch algorithm, the goal of Bungee Pro is to be the _best commercially-available audio time-stretch and pitch-adjustment technology_.\r\n"
"> \r\n"
"> * Novel processing techniques that deliver crisp transients and preserve vocal and instrumental timbre\r\n"
"> * Adaptive to all genres of speech, music and sound with subjective transparency up to infinite time stretch\r\n"
"> * Performance optimisations for:\r\n"
">    * Web AudioWorklet with SIMD128 WebAssembly\r\n"
">    * Arm NEON for Android, iOS and MacOS\r\n"
">    * x86-64 SIMD for Linux, Windows and MacOS\r\n"
"> * A ready-to-use Web Audio implementation \r\n"
"> * Professional support\r\n"
">\r\n"
"> Bungee Pro is today deployed in a wide variety of applications including movie post production software, educational apps and popular musicians' tools. \r\n"
">\r\n"
"> Check out an [extensive evaluation](https://bungee.parabolaresearch.com/compare-audio-stretch-tempo-pitch-change.html) of Bungee and Bungee Pro against state-of-the-art techniques.\r\n"
">\r\n"
"> | ![Bungee waveform animation: audio time-stretching and pitch-shifting demo](./README.md-waveform.png) | Try the [WebAssembly demo](https://bungee.parabolaresearch.com/change-audio-speed-pitch.html)  of Bungee Pro in your browser.|\r\n"
"> |--|--|\r\n"
">\r\n";

const char* README_md = (const char*) temp_binary_data_4;

//================== README.md-waveform.png ==================
static const unsigned char temp_binary_data_5[] =
{ 137,80,78,71,13,10,26,10,0,0,0,13,73,72,68,82,0,0,0,32,0,0,0,32,8,6,0,0,0,115,122,122,244,0,0,0,9,112,72,89,115,0,0,0,0,0,0,0,1,0,132,121,23,115,0,0,0,8,97,99,84,76,0,0,0,30,0,0,0,0,86,157,233,243,0,0,0,26,102,99,84,76,0,0,0,0,0,0,0,32,0,0,0,32,0,0,0,
0,0,0,0,0,0,1,0,25,0,0,132,71,62,195,0,0,2,32,73,68,65,84,120,156,205,87,205,46,67,65,20,158,210,106,163,22,36,90,79,96,193,27,240,44,136,8,186,34,218,39,152,29,43,181,82,54,126,30,64,19,22,44,186,36,196,67,144,86,45,26,30,1,169,115,210,111,244,152,204,
213,233,189,244,90,124,55,115,102,206,249,206,119,207,252,220,185,74,107,173,226,68,47,135,4,97,40,66,130,33,112,132,18,144,8,104,251,194,43,190,87,112,134,48,29,161,2,211,224,8,20,209,75,192,57,225,157,176,12,123,216,35,169,241,89,70,236,121,191,2,140,
227,24,161,69,104,19,142,209,151,244,16,96,124,142,16,219,2,151,83,196,79,2,70,9,117,144,84,66,8,216,71,108,29,92,94,2,216,33,37,4,52,64,114,16,66,64,5,177,13,33,32,101,139,112,189,185,65,214,33,32,173,59,115,236,154,207,4,198,210,14,1,89,135,239,55,
1,166,35,79,88,36,140,19,70,8,79,32,57,12,72,24,36,94,10,120,2,215,4,184,167,100,140,113,54,43,247,12,65,39,176,159,45,1,219,240,201,11,18,147,60,71,168,194,71,161,106,109,112,176,125,10,187,42,115,114,35,169,187,243,118,79,248,32,212,96,55,17,180,135,
55,104,3,27,24,207,232,238,62,223,20,227,236,91,70,187,9,145,53,112,223,235,238,90,73,218,101,187,65,208,165,37,160,140,55,124,3,73,201,81,242,18,198,222,224,187,43,4,40,112,182,145,227,43,142,31,5,221,153,27,110,223,194,233,202,81,129,28,18,176,189,
37,146,22,209,46,98,140,125,38,173,10,40,112,178,125,7,123,129,176,174,208,249,106,85,160,151,128,85,194,140,40,57,183,215,132,0,87,5,140,0,83,129,23,182,21,2,30,209,121,237,41,96,133,48,7,155,49,143,62,31,1,215,176,31,216,247,95,8,248,141,41,152,13,
49,5,175,102,10,162,44,66,94,120,37,29,126,17,22,148,246,223,134,124,248,152,109,88,180,226,148,142,176,13,255,197,65,100,238,125,85,4,157,234,254,143,226,60,226,119,180,251,40,62,129,125,166,173,163,88,9,18,254,80,44,233,191,249,24,49,231,162,37,94,
5,17,50,6,250,57,150,3,177,93,72,108,117,177,92,201,164,83,108,151,82,233,24,245,90,206,219,238,34,40,185,143,128,216,126,76,236,128,129,255,154,201,192,216,126,78,7,130,79,120,200,8,112,8,222,54,155,0,0,0,26,102,99,84,76,0,0,0,1,0,0,0,32,0,0,0,30,0,
0,0,0,0,0,0,1,0,1,0,25,0,0,152,151,102,7,0,0,2,65,102,100,65,84,0,0,0,2,120,156,197,151,55,78,67,65,16,134,159,201,73,72,72,38,20,112,1,90,162,40,184,0,150,160,133,14,104,72,13,65,136,114,107,10,130,144,8,5,62,2,29,80,1,5,65,164,26,168,136,6,11,137,27,
16,204,140,252,175,60,90,227,245,243,62,192,197,39,109,152,217,253,61,59,111,118,237,41,165,188,124,146,205,160,128,40,12,176,1,251,134,92,5,88,29,115,36,227,90,217,28,154,136,72,128,40,180,18,53,54,17,217,212,158,19,9,98,22,253,34,31,155,106,155,49,
248,30,216,236,109,2,170,136,103,226,147,136,58,8,216,132,128,56,214,226,177,180,156,176,9,168,32,238,177,200,26,198,74,177,129,45,63,180,128,85,248,242,26,149,25,246,72,19,80,0,180,128,7,44,178,110,17,42,225,95,88,130,246,26,124,31,137,50,140,181,16,
197,210,223,182,96,165,16,176,129,177,25,180,171,127,240,49,253,181,128,24,250,243,70,52,11,181,128,144,74,101,121,63,113,70,244,162,31,131,211,50,54,77,128,17,204,23,27,27,119,19,205,104,111,192,246,9,253,125,244,47,69,180,67,166,250,11,24,237,25,2,
22,137,58,226,157,248,32,166,196,34,250,200,34,176,125,67,127,197,16,176,131,254,145,140,148,12,153,135,201,79,24,123,112,102,167,37,162,22,115,220,159,196,124,185,74,230,10,183,231,68,132,234,137,5,67,192,46,250,39,194,183,156,27,199,196,22,6,79,96,
180,155,69,192,132,74,102,251,53,224,35,28,199,28,71,40,140,168,217,4,112,148,175,60,12,190,98,240,208,167,128,33,162,83,252,226,46,140,37,96,83,107,137,0,239,193,71,254,194,125,158,248,34,110,29,4,180,195,151,233,32,134,125,10,208,57,192,123,126,5,17,
208,17,80,192,157,22,224,114,4,131,8,123,144,35,136,235,35,112,77,66,78,188,43,226,70,37,19,210,57,9,61,149,170,3,182,207,48,44,4,232,58,144,233,51,108,176,68,32,237,51,148,2,116,33,218,87,254,10,17,71,193,111,33,218,86,25,10,145,44,197,3,196,41,209,
103,8,48,75,241,168,250,229,82,236,41,127,151,209,180,74,222,140,65,46,163,85,17,189,180,82,252,151,215,49,219,91,175,99,115,225,188,60,72,228,100,208,39,89,84,57,62,201,36,250,81,58,227,32,64,215,133,156,31,165,50,10,141,68,143,74,229,69,174,180,41,
135,103,185,41,226,55,200,249,143,137,38,175,127,205,254,133,111,136,173,167,253,31,73,85,220,0,0,0,26,102,99,84,76,0,0,0,3,0,0,0,32,0,0,0,28,0,0,0,0,0,0,0,2,0,1,0,25,0,0,236,111,30,226,0,0,2,72,102,100,65,84,0,0,0,4,120,156,197,87,205,78,20,65,16,94,
216,13,16,48,17,17,225,66,184,200,51,184,42,137,55,15,62,131,146,24,137,112,4,92,228,194,165,244,226,13,140,137,34,42,7,124,7,225,100,52,89,13,137,209,39,48,146,101,119,185,248,243,2,34,59,84,101,190,206,212,246,204,246,204,246,36,238,225,219,217,234,
173,170,254,230,171,238,234,222,2,17,21,122,137,52,135,126,70,137,209,231,57,65,17,57,188,8,216,147,250,146,112,198,186,222,92,158,215,24,107,140,81,15,18,146,227,22,99,74,197,198,226,93,108,69,190,31,140,128,241,4,99,131,148,94,146,18,158,171,136,253,
98,229,109,139,117,17,56,199,168,51,254,49,94,59,252,58,17,120,195,104,49,142,145,75,198,198,210,20,232,83,9,134,25,71,120,139,109,140,221,101,60,98,12,57,72,152,248,23,136,109,192,94,102,252,97,172,83,164,112,27,1,59,217,136,34,240,12,118,0,204,91,147,
153,120,169,251,0,236,45,248,54,97,127,128,253,77,207,103,152,20,41,146,253,38,133,181,22,212,17,180,201,152,96,156,80,88,146,10,252,135,16,155,164,196,75,75,129,119,176,63,41,242,37,59,104,23,78,207,97,55,97,63,101,140,99,242,0,114,218,177,211,120,203,
87,150,2,134,192,62,236,207,58,78,62,110,48,174,98,224,43,133,11,231,61,236,134,34,112,137,113,10,123,5,191,223,97,204,225,251,3,138,74,116,17,170,37,17,56,128,45,113,139,5,12,214,49,88,133,189,151,66,224,62,227,178,154,112,134,177,128,223,255,194,119,
163,3,1,83,130,159,98,27,2,53,10,235,104,8,236,167,16,184,7,213,90,192,44,198,2,248,184,8,84,97,75,143,105,105,2,90,129,44,4,174,40,5,202,20,238,140,44,4,140,2,53,91,129,110,9,148,61,9,24,5,98,4,186,45,193,245,156,37,56,212,37,240,89,132,51,74,1,189,
8,79,50,150,224,151,81,32,207,54,156,163,104,27,86,20,161,44,219,240,182,144,46,80,123,51,121,75,249,26,209,71,242,104,68,89,91,241,36,69,173,120,149,252,91,177,89,3,177,86,220,179,195,200,38,97,146,118,58,142,31,147,223,113,188,196,248,77,142,227,216,
86,34,239,133,100,135,226,23,146,11,182,191,139,128,200,249,157,252,175,100,15,201,243,74,102,38,151,167,116,56,217,94,231,83,222,58,9,34,177,190,148,246,39,197,187,18,244,244,90,174,149,72,147,60,77,5,239,63,38,255,5,103,136,229,72,216,131,82,23,36,
0,0,0,26,102,99,84,76,0,0,0,5,0,0,0,32,0,0,0,26,0,0,0,0,0,0,0,3,0,1,0,25,0,0,133,40,179,222,0,0,2,56,102,100,65,84,0,0,0,6,120,156,205,150,77,47,67,65,20,134,111,63,80,237,86,195,82,172,248,1,210,46,217,218,168,4,137,4,9,22,54,154,136,176,36,243,7,168,
32,68,36,22,126,3,154,16,54,213,38,146,110,117,73,169,176,177,180,236,135,51,250,142,156,78,238,103,219,96,241,228,222,51,119,206,57,239,156,153,185,51,134,16,194,248,75,156,58,4,128,191,137,224,62,34,232,228,235,20,64,183,3,8,234,38,185,110,251,217,
211,81,128,234,52,67,156,17,3,30,71,46,159,33,98,142,24,178,19,104,23,160,147,120,35,106,196,33,218,198,137,21,84,194,74,128,170,208,38,124,11,176,39,137,60,68,25,42,134,157,128,8,81,36,202,196,62,70,84,69,80,21,196,108,58,84,219,9,81,193,32,164,125,
3,223,188,96,85,214,157,253,108,116,97,226,25,78,41,162,23,98,36,235,232,211,161,249,7,80,57,3,85,147,190,47,176,47,33,232,142,229,242,41,39,181,64,120,176,8,19,176,75,244,32,185,180,87,181,209,234,190,146,35,244,45,193,78,195,206,242,126,186,211,24,
113,78,140,192,46,105,2,42,176,215,44,18,39,136,56,222,143,45,4,228,88,133,195,242,229,148,216,65,227,61,58,93,193,126,101,2,162,76,64,18,223,115,64,10,153,192,183,79,84,117,207,65,192,45,81,48,208,248,129,198,12,146,164,77,42,192,5,44,18,49,188,215,
48,234,101,124,151,11,181,23,131,50,19,144,129,224,239,29,102,192,233,145,9,168,185,16,176,68,12,35,89,5,98,22,240,173,140,233,74,89,8,80,139,80,230,172,170,10,20,61,10,208,43,16,131,168,26,250,68,109,42,160,4,20,85,5,218,33,32,142,54,55,2,50,186,128,
102,166,64,9,104,101,10,158,248,20,52,179,8,227,90,5,248,34,236,115,168,128,92,132,239,170,2,114,27,110,139,198,109,120,45,220,111,195,44,2,38,132,183,109,40,115,60,24,194,252,71,52,234,80,129,118,252,136,186,136,144,33,254,217,175,216,207,130,218,29,
70,27,194,251,97,116,33,44,14,35,29,187,227,88,77,193,188,86,1,78,75,199,49,23,192,47,36,7,104,147,23,146,164,112,119,33,217,18,141,23,146,41,36,159,117,18,240,243,145,152,22,245,93,210,111,147,208,106,0,221,162,126,113,25,180,233,99,41,160,161,19,179,
127,237,82,170,80,9,205,86,185,27,17,65,61,161,142,215,160,109,231,11,176,4,232,192,248,51,123,232,0,0,0,26,102,99,84,76,0,0,0,7,0,0,0,32,0,0,0,24,0,0,0,0,0,0,0,4,0,1,0,25,1,0,28,132,222,105,0,0,2,42,102,100,65,84,0,0,0,8,120,156,205,150,187,75,92,65,
20,198,119,55,138,137,6,180,48,22,6,211,91,105,17,92,31,16,11,45,252,11,148,52,66,140,15,236,162,121,96,35,76,37,169,84,52,24,177,182,76,189,34,138,69,140,4,196,74,107,223,86,43,118,177,210,205,230,59,238,119,220,227,245,222,236,189,171,136,197,143,59,
103,56,103,230,187,103,102,206,76,204,57,23,139,192,19,80,18,49,70,73,48,62,97,251,195,4,197,205,55,202,132,113,138,245,139,189,182,163,254,69,11,232,9,57,185,183,175,25,44,130,118,243,115,129,2,52,77,227,96,11,188,6,21,224,28,100,65,183,203,47,73,208,
228,149,224,19,104,165,189,202,216,141,66,2,116,128,103,224,148,65,179,160,6,252,5,25,240,153,62,126,251,65,251,38,24,187,75,123,25,92,26,1,113,21,96,215,40,110,254,170,28,236,115,194,41,80,205,1,100,208,15,244,41,243,100,65,215,93,218,11,244,63,225,
28,41,79,6,196,175,196,47,237,138,164,252,144,65,94,1,35,62,89,211,159,40,229,119,142,190,199,180,151,60,2,98,154,129,58,80,107,130,27,216,126,10,142,24,52,77,1,25,218,163,244,233,2,157,238,246,50,8,243,1,2,126,211,238,5,195,210,56,3,219,236,252,70,167,
175,180,79,140,128,23,70,192,32,120,197,182,80,15,94,130,29,240,131,177,223,3,4,252,162,125,181,191,98,198,73,82,184,73,123,141,78,199,1,2,250,92,238,72,170,128,54,48,96,108,241,157,12,16,176,78,91,54,103,70,5,28,176,243,39,237,84,1,1,239,93,238,104,
234,132,73,138,146,83,114,81,64,128,102,224,192,102,64,5,172,211,94,10,145,129,164,17,208,204,190,44,125,30,181,0,93,2,95,1,97,151,64,38,107,42,114,9,124,5,68,221,132,239,92,110,227,169,0,41,183,81,55,225,158,8,150,70,49,199,112,200,221,253,24,166,53,
3,222,66,212,232,252,11,145,21,96,11,81,135,43,174,16,189,5,253,54,160,80,41,182,2,238,181,20,7,93,70,34,224,65,47,35,59,136,124,229,58,78,51,104,198,221,188,142,191,152,65,188,241,145,175,99,63,116,57,198,24,32,251,226,57,248,227,194,63,72,170,192,71,
151,127,144,172,120,50,240,223,23,81,16,82,112,238,250,36,123,19,69,192,163,123,148,38,220,61,63,203,255,1,155,216,137,182,84,58,64,136,0,0,0,26,102,99,84,76,0,0,0,9,0,0,0,32,0,0,0,26,0,0,0,0,0,0,0,3,0,1,0,25,0,1,242,202,97,253,0,0,2,64,102,100,65,84,
0,0,0,10,120,156,205,87,75,43,68,97,24,62,102,68,161,68,132,157,5,11,150,138,193,150,114,41,252,7,11,178,17,66,150,239,142,141,219,70,89,240,19,76,146,91,148,50,200,222,198,202,165,145,91,252,2,151,241,190,205,243,229,157,207,204,185,140,73,166,158,206,
121,191,121,159,247,60,231,249,174,199,113,2,252,136,40,196,8,7,225,88,220,124,185,218,127,248,69,94,134,251,160,220,148,216,47,57,132,251,70,70,71,150,15,175,101,204,48,234,16,135,188,4,216,170,203,24,207,140,4,163,31,109,97,15,190,88,94,128,120,3,220,
61,63,2,244,195,203,113,109,96,188,49,62,25,211,104,203,247,41,94,112,200,120,103,156,235,28,47,1,107,140,23,70,55,163,26,2,228,45,198,92,4,24,174,228,207,129,43,241,1,184,39,202,129,60,83,36,156,166,64,49,125,91,190,194,168,96,124,32,30,71,78,129,41,
164,248,70,212,60,114,239,16,239,35,62,213,130,109,245,33,85,160,136,113,13,210,2,163,18,22,74,60,145,225,205,133,91,136,120,21,249,113,252,183,11,238,153,170,95,44,55,147,140,161,52,5,75,24,183,32,45,89,14,140,34,103,139,17,133,91,54,127,5,185,113,196,
123,150,128,35,198,165,131,198,23,52,182,81,178,223,155,224,70,92,9,168,84,2,6,25,45,184,23,116,129,63,194,232,81,14,104,1,198,129,24,28,185,151,216,65,209,43,36,29,35,105,7,241,157,139,128,102,196,130,118,74,78,205,4,108,151,110,88,206,32,192,12,66,
121,230,167,113,224,6,141,49,20,48,115,213,205,129,102,229,64,132,146,221,248,142,156,42,74,142,27,55,1,55,198,1,91,64,2,201,94,2,34,74,64,43,218,140,3,50,94,22,255,171,128,152,151,0,191,93,160,5,4,233,130,31,2,132,112,77,169,131,112,155,188,7,97,132,
82,7,97,159,114,32,240,32,124,69,163,88,185,78,191,155,134,189,228,111,26,62,24,7,166,24,195,228,190,16,45,90,2,244,66,180,73,254,22,34,123,37,148,189,225,194,38,121,45,197,70,64,54,75,241,142,37,64,242,10,29,250,187,205,200,44,197,174,155,145,45,66,
222,226,145,209,201,168,161,224,219,241,44,249,216,142,189,80,138,107,35,253,225,129,36,93,17,57,146,61,225,45,6,208,22,228,72,22,5,119,95,57,224,42,64,23,50,98,114,113,40,173,15,42,32,157,35,185,59,150,103,241,113,145,211,15,147,47,222,164,153,187,117,
2,39,92,0,0,0,26,102,99,84,76,0,0,0,11,0,0,0,10,0,0,0,7,0,0,0,17,0,0,0,19,0,1,0,25,0,0,131,0,133,100,0,0,0,101,102,100,65,84,0,0,0,12,120,156,99,104,104,104,240,0,98,6,32,206,4,98,47,40,123,38,16,255,7,226,199,80,254,118,16,193,13,229,32,227,105,216,
20,130,48,35,16,179,0,49,59,146,137,127,160,10,65,114,219,96,138,96,26,88,160,116,47,212,196,39,80,254,14,116,43,97,154,36,128,184,29,201,253,187,209,21,162,219,0,195,123,176,41,68,118,51,27,148,191,14,0,151,163,121,233,131,19,3,61,0,0,0,26,102,99,84,
76,0,0,0,13,0,0,0,32,0,0,0,30,0,0,0,0,0,0,0,1,0,1,0,25,2,0,170,68,230,48,0,0,2,131,102,100,65,84,0,0,0,14,120,156,205,87,61,79,148,65,16,126,239,64,32,64,97,33,212,168,124,196,143,206,16,160,176,193,24,11,109,44,236,160,65,27,109,64,99,180,211,41,132,
146,64,2,193,6,162,191,64,11,19,81,105,144,143,10,170,235,72,48,39,159,5,63,64,140,30,58,147,123,54,55,183,204,221,189,251,30,33,20,79,110,103,246,158,221,231,102,102,103,247,34,34,138,2,144,98,164,3,57,26,199,184,161,155,91,227,170,16,186,249,121,198,
197,42,68,116,249,188,144,205,27,25,25,198,33,227,38,124,53,49,248,238,59,111,24,71,140,113,237,143,35,192,229,237,10,227,31,240,2,190,218,0,254,34,184,107,250,135,133,8,232,96,252,194,34,195,9,4,204,131,187,28,34,64,200,117,74,192,33,22,121,154,64,192,
87,112,87,148,63,37,131,26,178,115,233,23,89,39,227,183,39,160,30,92,171,32,211,152,59,87,66,64,228,71,32,69,199,85,75,213,14,98,124,217,16,80,138,111,9,114,2,86,97,55,49,154,101,112,151,209,175,136,154,156,1,233,57,227,2,227,47,21,215,192,123,198,156,
250,149,186,81,93,103,124,98,60,134,189,224,9,144,162,220,136,224,220,81,155,187,156,55,195,159,99,76,65,64,14,223,127,200,184,65,133,83,113,155,10,41,169,199,248,45,230,14,168,184,8,151,176,207,158,216,78,192,38,163,193,11,153,132,40,139,121,57,187,
45,74,192,16,163,7,118,14,81,244,67,62,131,185,45,108,248,153,138,79,193,15,198,145,19,144,133,243,42,99,148,209,78,249,2,218,198,252,132,33,160,91,69,224,14,248,175,24,3,94,4,182,97,251,2,178,58,2,91,112,126,131,253,17,246,78,76,1,125,140,7,202,150,
174,57,25,34,192,69,64,38,165,208,230,97,151,139,64,143,218,176,151,241,8,220,63,140,86,202,167,237,76,10,88,138,147,130,15,49,82,160,5,248,41,104,42,147,2,83,192,79,42,20,225,24,197,43,66,45,192,21,225,107,170,92,132,166,0,57,18,161,199,176,151,78,240,
24,238,146,221,136,118,177,200,52,133,55,162,25,42,223,136,246,93,4,238,49,110,145,221,138,215,169,208,122,117,4,92,43,126,199,152,37,187,21,95,163,124,43,126,66,118,43,150,122,203,232,144,89,151,73,27,227,62,198,82,23,238,50,122,102,132,188,210,101,
244,197,19,32,145,106,144,193,105,93,199,78,64,201,235,216,66,90,45,96,9,168,173,192,119,107,200,103,201,7,73,220,5,244,147,108,36,129,0,93,132,17,37,120,19,234,71,233,203,4,2,190,131,187,30,42,192,127,150,75,26,146,62,203,229,20,5,63,203,181,8,249,99,
114,201,243,133,160,211,231,133,144,173,55,99,213,8,37,156,248,159,211,255,156,124,173,63,12,32,199,115,0,0,0,26,102,99,84,76,0,0,0,15,0,0,0,32,0,0,0,28,0,0,0,0,0,0,0,2,0,1,0,25,2,0,222,188,158,213,0,0,2,129,102,100,65,84,0,0,0,16,120,156,181,151,75,
79,20,65,16,199,119,22,137,175,40,17,31,23,53,241,34,134,128,193,104,64,188,17,141,30,52,129,207,32,146,144,200,65,94,49,225,86,71,18,137,66,8,23,15,30,252,0,222,0,31,49,106,48,18,131,159,1,208,229,160,242,5,32,102,193,42,246,95,76,209,206,206,116,15,
235,225,183,51,221,211,85,253,239,234,234,199,22,136,168,16,64,145,169,11,180,81,34,216,70,182,62,212,65,158,142,147,108,119,203,161,14,90,153,59,57,59,175,103,58,152,131,182,62,196,65,35,179,206,108,51,61,168,243,153,14,109,51,9,219,231,182,222,71,64,
17,207,102,230,15,179,197,60,70,221,129,0,251,143,16,176,100,6,22,169,146,162,135,131,139,204,6,156,60,66,221,33,15,17,106,255,26,182,159,77,125,100,27,38,37,153,205,250,38,102,19,78,134,60,70,174,131,83,129,111,97,251,197,182,145,159,78,230,90,138,8,
229,146,137,192,32,234,38,152,241,140,8,42,174,128,151,204,188,188,148,153,101,103,212,234,112,140,89,100,46,51,231,168,146,3,226,228,1,211,134,119,225,38,197,57,161,131,144,231,45,230,44,202,239,208,118,1,223,118,18,186,128,202,21,138,151,135,114,152,
249,141,239,211,204,73,136,149,114,47,34,87,6,247,76,167,58,101,195,104,251,213,137,128,230,128,12,186,172,2,164,80,143,15,13,120,30,129,48,233,224,25,115,218,17,208,97,34,160,2,142,83,60,231,47,168,178,98,126,34,162,243,142,128,85,27,129,31,168,28,101,
126,49,15,81,94,195,247,36,1,237,70,64,23,115,129,41,49,239,97,59,227,248,118,87,193,30,1,223,81,185,132,242,7,71,192,100,134,0,137,70,191,41,159,97,158,226,189,4,95,169,17,88,69,229,39,148,231,80,46,165,8,184,110,58,148,124,184,143,144,75,162,158,66,
212,114,11,152,253,143,2,22,106,53,5,86,64,200,20,36,10,112,147,112,128,178,147,208,10,232,162,236,36,76,21,32,203,205,93,134,71,41,125,25,90,1,119,97,115,140,178,151,97,85,1,238,70,36,7,141,110,68,83,244,239,70,116,131,106,180,17,109,65,128,118,108,
183,226,17,170,36,166,28,197,231,41,222,138,251,152,43,38,2,161,91,177,148,119,183,98,201,224,171,198,168,80,133,164,195,232,9,249,31,70,111,96,187,136,178,92,76,94,217,6,213,142,99,157,83,123,28,15,123,116,40,120,29,199,121,46,36,26,129,253,92,72,118,
250,245,25,69,173,174,100,186,201,125,163,56,226,81,150,177,54,148,231,9,138,87,69,183,25,69,150,253,190,47,165,86,68,11,115,219,211,198,181,205,125,45,119,29,185,239,161,182,123,202,33,78,132,154,255,53,251,11,46,141,78,159,29,102,211,186,0,0,0,26,102,
99,84,76,0,0,0,17,0,0,0,32,0,0,0,26,0,0,0,0,0,0,0,3,0,1,0,25,0,0,132,6,148,1,0,0,2,94,102,100,65,84,0,0,0,18,120,156,205,87,207,107,83,65,16,206,179,177,189,20,188,84,173,66,123,49,22,193,179,169,61,216,155,160,244,199,159,208,67,181,133,64,161,65,170,
130,130,204,165,71,173,30,236,69,175,138,247,66,181,69,16,250,35,7,253,3,60,69,18,61,216,67,115,83,80,210,54,206,144,111,218,121,155,247,146,125,73,14,30,62,178,179,251,102,246,219,111,118,119,54,41,34,74,37,64,15,35,157,208,71,17,192,63,176,253,73,3,
180,51,113,148,239,177,157,52,192,52,35,111,84,240,33,165,223,244,51,38,24,103,108,191,52,78,1,113,1,116,236,34,163,202,168,49,102,208,215,71,173,83,210,131,223,87,240,125,11,251,180,140,53,147,201,37,112,133,241,135,113,192,88,242,84,206,250,127,98,
28,50,62,219,113,13,124,41,134,68,0,166,210,190,204,248,139,85,228,209,247,128,113,207,147,192,7,248,238,194,126,194,120,42,141,95,140,175,17,74,184,100,70,160,128,4,185,203,184,138,182,96,156,194,114,235,196,18,67,83,180,137,111,183,97,87,196,78,161,
179,76,245,124,166,176,98,13,52,200,184,137,118,198,40,48,203,24,131,164,130,73,58,217,19,13,71,45,134,64,81,124,149,64,209,16,176,40,96,60,199,56,75,245,252,43,129,172,81,224,118,132,111,22,114,63,130,253,17,223,238,192,46,89,5,74,232,28,98,44,98,229,
189,140,159,140,35,198,75,198,0,86,219,140,64,206,180,95,99,108,159,194,123,32,146,64,25,157,107,176,223,193,254,1,251,25,20,80,2,119,24,215,12,1,73,199,20,218,85,168,249,2,223,107,236,247,62,10,20,32,179,228,43,48,4,158,183,32,48,202,152,135,175,124,
115,30,164,107,136,225,77,96,11,246,186,163,128,75,96,22,147,42,129,235,232,171,129,132,164,107,229,127,37,160,167,160,163,20,184,4,146,164,32,146,192,119,74,182,9,93,2,178,9,39,201,111,19,54,85,96,152,194,199,112,15,227,171,212,120,12,45,129,91,20,127,
12,43,62,4,190,81,244,69,164,123,98,142,113,142,194,167,192,247,34,122,76,30,23,81,220,85,44,171,214,123,222,22,163,174,94,197,191,201,191,24,41,1,81,196,22,163,27,212,186,24,109,56,10,28,23,35,41,199,153,152,73,221,114,172,213,176,27,229,248,33,99,217,
157,172,89,0,251,32,185,223,98,210,40,127,125,144,124,177,227,250,129,207,147,236,2,157,164,160,147,39,217,27,216,114,202,210,190,171,80,117,228,81,185,64,225,92,251,250,198,62,74,147,6,106,7,29,63,203,21,93,255,99,242,15,104,76,240,65,28,66,150,50,0,
0,0,26,102,99,84,76,0,0,0,19,0,0,0,32,0,0,0,26,0,0,0,0,0,0,0,3,0,1,0,25,0,0,105,144,71,232,0,0,2,73,102,100,65,84,0,0,0,20,120,156,205,150,59,75,92,81,16,199,119,93,19,59,17,124,64,154,16,11,245,19,248,192,210,46,136,85,32,69,36,138,198,7,104,99,145,
206,102,190,128,15,176,72,147,54,105,52,69,16,98,98,162,226,163,16,37,149,54,54,186,174,32,168,31,192,136,186,58,195,253,31,118,246,114,238,217,115,119,87,54,197,207,187,115,238,204,185,127,231,156,153,115,18,68,148,168,36,113,3,82,76,53,147,44,226,99,
73,91,172,252,169,42,97,66,35,200,199,215,22,155,114,57,217,222,125,100,62,51,117,49,133,202,179,145,25,100,94,132,51,32,3,77,14,17,85,120,190,98,30,192,36,198,62,96,82,151,128,20,158,95,17,251,29,246,59,137,151,31,23,204,95,199,4,70,64,27,115,205,220,
49,99,76,171,18,212,21,250,152,45,126,13,177,187,176,47,37,54,129,9,206,152,26,75,22,100,194,103,248,221,194,252,131,255,16,211,205,220,131,62,248,232,253,96,54,157,25,251,133,216,45,216,199,76,214,8,56,86,31,210,170,53,109,74,192,48,211,161,50,240,90,
9,78,146,125,41,87,225,187,3,59,173,51,32,2,158,91,210,40,169,94,102,154,153,151,204,109,132,128,94,75,6,36,163,111,41,88,42,177,255,184,4,156,98,112,148,57,98,6,96,95,225,253,28,83,143,116,219,4,244,80,176,145,15,153,37,196,78,227,221,129,79,6,210,24,
220,131,189,1,59,131,143,206,83,80,70,70,128,236,254,118,37,160,19,226,141,221,192,44,192,255,156,130,37,93,241,17,176,201,100,153,31,176,207,84,6,92,2,186,144,149,44,150,73,124,103,240,46,131,185,126,250,8,216,134,189,18,18,16,206,192,48,254,235,176,
128,7,248,136,239,44,229,42,44,161,50,176,253,95,11,240,93,130,40,1,102,9,26,28,75,96,21,96,170,96,31,246,58,185,55,97,88,128,84,196,136,178,93,155,208,42,192,168,148,186,151,50,124,79,249,101,56,131,73,163,4,232,50,92,36,119,25,90,5,156,80,174,17,233,
102,34,45,247,27,5,77,40,220,136,180,0,211,136,116,19,11,55,162,223,84,160,19,250,180,226,27,202,149,97,220,86,108,206,2,107,6,226,30,70,146,129,178,29,70,114,44,198,61,142,199,169,244,227,248,194,100,160,152,11,201,4,198,100,231,251,94,72,190,80,254,
133,228,13,211,175,29,125,174,100,83,204,39,166,182,192,71,109,177,145,87,178,168,77,227,51,113,89,47,165,62,60,201,181,188,162,60,2,78,177,241,198,207,151,167,164,0,0,0,26,102,99,84,76,0,0,0,21,0,0,0,32,0,0,0,24,0,0,0,0,0,0,0,4,0,1,0,25,0,0,233,123,
186,141,0,0,2,85,102,100,65,84,0,0,0,22,120,156,189,150,61,107,84,65,20,134,119,55,43,33,4,21,140,38,101,10,53,77,68,65,19,149,124,116,177,112,197,70,11,65,72,145,13,248,15,180,62,189,24,44,140,141,157,165,160,165,155,24,139,144,132,248,23,44,212,108,
54,88,40,216,88,136,194,230,227,61,236,59,236,217,201,76,238,228,46,88,60,151,57,51,231,204,125,231,220,51,115,167,32,34,69,82,200,65,15,201,19,91,210,88,219,145,37,162,200,160,162,28,22,157,178,0,245,41,251,177,250,56,5,78,102,76,20,235,191,3,42,9,34,
66,99,227,96,82,27,95,192,90,194,10,148,87,96,19,156,3,151,192,62,185,42,237,180,198,94,62,12,158,128,243,180,27,26,91,224,4,223,65,111,68,173,155,244,162,121,225,60,152,0,123,228,174,180,107,194,23,224,250,222,49,246,61,237,109,39,64,39,248,6,78,112,
192,125,39,39,166,204,246,8,248,3,118,65,21,92,55,130,110,211,167,215,203,66,209,216,31,65,147,25,84,187,110,51,176,101,50,224,175,220,161,25,248,75,127,95,64,69,14,167,221,197,187,5,44,211,119,61,36,160,206,160,1,240,0,156,161,147,22,231,21,35,224,95,
68,128,203,192,61,48,22,89,196,7,250,110,132,4,108,179,243,13,237,215,38,109,106,207,130,33,105,165,63,36,96,18,220,98,251,55,232,3,83,224,51,120,234,205,21,20,80,103,231,39,190,100,133,234,127,112,252,37,56,107,4,104,17,142,27,1,55,192,35,142,107,77,
13,130,23,28,251,197,185,151,82,50,176,38,157,149,218,160,189,32,173,173,23,19,112,19,204,177,221,164,216,103,20,227,230,174,165,100,96,157,118,141,246,14,237,231,158,128,42,87,109,5,84,217,222,165,239,2,237,157,255,37,96,62,81,64,112,23,28,247,19,132,
4,164,126,130,232,54,212,182,95,132,63,37,92,132,190,128,148,34,60,82,64,67,194,219,208,29,30,15,165,181,13,155,17,1,186,13,103,164,115,27,78,75,231,54,92,201,202,128,61,136,6,232,212,15,70,37,124,16,89,1,238,32,186,15,174,73,142,131,40,229,40,30,57,
66,64,87,71,113,158,159,145,86,124,183,63,163,45,155,129,148,223,241,5,243,66,205,192,4,219,169,191,227,183,18,216,97,218,248,106,210,146,197,34,88,149,86,141,216,11,137,251,238,89,23,146,199,210,190,144,104,214,155,218,56,45,217,87,178,24,21,201,127,
37,187,172,194,179,156,252,241,146,116,94,76,83,99,157,79,217,143,45,4,38,59,14,221,94,203,75,7,235,154,147,166,178,121,69,43,0,0,0,26,102,99,84,76,0,0,0,23,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,25,0,1,68,211,3,141,0,0,0,15,102,100,65,84,0,0,0,24,120,
156,99,96,0,2,0,0,5,0,1,26,208,99,61,0,0,0,26,102,99,84,76,0,0,0,25,0,0,0,32,0,0,0,26,0,0,0,0,0,0,0,3,0,1,0,25,0,0,132,191,215,39,0,0,2,80,102,100,65,84,0,0,0,26,120,156,197,151,77,75,85,81,20,134,239,189,222,20,39,70,164,66,224,224,10,69,17,230,40,187,
142,108,208,72,5,33,9,27,171,131,134,253,128,38,123,154,81,82,228,36,250,25,130,249,69,248,17,161,72,127,64,36,237,42,58,112,30,125,104,189,139,251,46,88,119,115,206,62,231,120,20,7,15,247,172,189,246,90,231,221,107,127,157,91,112,206,21,73,225,12,52,
145,179,196,202,59,75,126,67,214,4,185,99,253,81,36,37,42,186,198,138,245,147,44,34,180,223,13,208,37,15,91,96,54,69,18,223,215,3,254,145,123,108,43,5,226,197,87,54,125,190,129,227,2,19,28,130,150,128,8,109,147,74,93,227,243,136,17,48,98,252,105,196,
183,130,31,18,43,198,41,216,1,87,98,58,171,45,254,207,224,8,220,4,3,70,192,96,64,128,142,248,46,120,5,122,105,239,170,0,73,240,29,52,155,128,82,68,130,59,230,133,207,192,3,99,15,25,145,254,52,168,168,89,246,93,166,189,23,39,192,142,188,100,218,111,129,
159,236,63,14,170,70,192,112,196,200,37,190,76,196,94,4,127,193,23,250,26,42,176,199,78,79,193,87,48,26,145,240,54,248,197,254,19,94,5,30,129,171,96,5,188,143,136,21,230,217,119,205,69,76,193,46,27,55,104,175,210,30,3,31,65,39,168,128,63,49,2,170,108,
83,187,194,145,63,7,247,153,107,137,190,245,144,0,25,193,9,152,163,125,72,255,75,208,78,159,216,147,160,207,188,176,159,2,196,255,155,125,95,208,183,205,92,11,33,1,58,5,107,180,69,128,204,83,205,213,231,237,45,232,8,8,176,21,56,161,128,119,140,61,112,
245,181,52,151,166,2,86,64,129,2,196,158,246,4,76,184,198,69,168,21,80,1,210,247,13,237,26,115,125,186,104,1,147,158,128,215,49,2,34,23,97,214,41,72,170,64,104,10,130,187,32,237,34,244,5,200,243,184,11,47,194,224,54,212,10,248,219,240,9,248,192,132,21,
215,184,13,125,1,118,27,118,187,248,109,24,20,160,7,209,99,151,124,16,89,1,114,16,181,177,130,51,17,177,137,21,200,114,20,159,186,11,56,138,243,94,70,122,27,234,101,100,111,212,196,203,72,175,99,21,16,119,29,151,89,198,125,87,95,15,15,35,4,36,93,199,
83,46,230,58,78,251,65,34,191,109,238,124,62,72,106,42,224,178,62,201,54,193,129,170,206,243,81,90,77,25,235,15,228,58,232,8,141,48,109,162,92,177,118,84,89,18,40,121,255,152,20,255,3,238,18,245,254,5,12,4,150,0,0,0,26,102,99,84,76,0,0,0,27,0,0,0,32,
0,0,0,28,0,0,0,0,0,0,0,2,0,1,0,25,0,0,237,164,219,136,0,0,2,128,102,100,65,84,0,0,0,28,120,156,205,87,203,106,20,81,16,29,147,121,64,68,20,162,160,160,203,68,212,141,46,226,8,209,69,32,1,29,240,241,9,49,89,232,103,212,15,232,206,140,160,32,145,100,99,
192,157,12,142,89,68,18,66,86,217,186,81,156,201,66,35,186,84,124,197,25,171,102,78,165,107,174,119,236,219,221,4,178,56,116,213,237,122,156,174,91,247,209,57,34,202,101,192,0,144,198,247,128,96,87,72,25,192,18,73,229,155,246,203,53,192,105,192,37,20,
226,155,23,136,80,103,44,38,8,162,95,59,202,248,14,140,38,168,132,230,120,193,216,20,161,205,248,196,40,5,144,144,119,69,200,55,224,219,134,44,99,131,129,201,37,215,71,241,21,229,15,227,157,9,220,143,128,59,126,213,16,184,22,64,64,170,147,135,92,64,206,
150,86,224,189,33,144,247,36,83,253,56,227,60,228,138,33,80,193,88,145,252,211,224,198,43,33,103,219,18,40,245,113,210,231,33,198,91,216,95,100,92,246,16,240,37,84,66,101,198,60,99,28,122,211,18,104,192,112,136,49,133,167,6,210,178,157,161,238,116,137,
253,93,144,112,9,76,80,212,144,186,188,117,90,234,176,93,245,17,104,98,240,9,244,135,14,123,193,8,227,7,222,223,118,8,72,53,174,64,150,230,58,98,252,44,129,29,198,26,136,53,220,41,16,121,131,209,98,172,80,212,44,167,40,90,118,63,97,63,227,16,144,242,
222,129,252,27,213,18,159,195,134,136,91,129,30,2,13,12,190,134,254,18,250,18,227,27,227,22,117,27,112,7,239,103,25,99,134,192,37,198,52,228,95,140,19,140,73,198,54,227,49,98,45,227,253,154,143,128,78,193,42,244,26,202,244,25,122,149,113,148,162,30,112,
9,148,81,149,54,108,196,246,1,244,47,136,85,251,31,1,173,128,37,32,250,22,244,251,140,99,134,192,12,146,218,10,88,2,98,123,207,249,184,61,39,48,27,72,192,219,3,73,167,192,37,224,78,193,48,99,206,76,65,44,1,173,128,54,97,29,250,51,198,87,198,77,234,109,
66,31,129,105,138,154,80,108,101,63,145,38,124,132,88,175,66,8,248,150,225,73,242,47,67,151,128,93,134,103,41,225,50,220,162,222,141,168,74,241,27,145,37,96,55,162,15,78,226,160,141,168,65,97,91,113,139,226,183,226,17,227,27,188,21,135,28,70,7,25,111,
168,219,100,23,204,23,39,57,140,158,82,159,195,40,244,56,150,149,112,142,254,61,142,245,62,144,234,56,222,23,23,146,36,87,178,2,228,235,134,64,154,43,217,182,86,64,154,99,33,32,185,253,18,121,102,189,148,62,103,172,199,25,199,5,201,114,45,239,64,7,178,
254,152,36,245,207,252,99,162,200,242,107,214,33,242,23,3,143,88,175,50,118,35,141,0,0,0,26,102,99,84,76,0,0,0,29,0,0,0,32,0,0,0,30,0,0,0,0,0,0,0,1,0,1,0,25,2,0,171,54,96,124,0,0,2,103,102,100,65,84,0,0,0,30,120,156,197,87,59,111,19,65,16,14,182,28,23,
129,10,40,82,37,78,193,163,162,226,149,54,9,138,19,65,157,14,197,41,248,27,35,76,139,4,18,212,212,116,84,68,81,18,75,16,148,252,137,68,121,184,195,184,137,4,226,101,96,70,247,77,60,108,214,119,123,123,137,92,124,246,204,237,206,206,183,51,115,179,123,
35,68,52,82,0,23,128,232,53,228,167,4,228,53,46,13,144,243,216,151,138,236,92,254,199,1,251,44,119,4,222,50,94,231,88,68,119,59,201,232,50,190,64,14,141,132,250,120,37,190,69,248,203,232,48,70,3,73,148,241,255,16,182,130,71,206,88,150,115,241,245,89,
108,69,233,49,246,34,8,204,27,2,245,8,2,187,226,91,35,176,31,72,64,66,92,133,92,55,4,22,34,8,236,107,4,92,2,101,242,231,210,37,230,35,48,154,66,162,100,198,188,4,170,52,216,161,18,186,203,88,162,211,41,88,12,220,185,162,234,18,56,52,187,122,207,152,49,
142,213,248,42,227,24,243,31,48,238,27,2,115,88,244,29,227,153,227,84,201,207,98,237,121,232,135,150,192,1,30,110,67,111,65,175,80,63,53,55,24,63,41,41,218,39,140,59,134,128,68,230,177,209,167,76,168,43,144,91,24,219,73,35,240,17,14,214,60,97,188,198,
248,142,249,203,14,129,123,140,6,108,191,50,174,123,236,215,48,190,5,253,96,16,1,209,215,161,75,42,154,140,49,70,13,17,144,241,21,198,109,39,2,203,144,127,96,238,69,164,99,22,107,109,96,220,75,64,107,96,11,186,70,224,8,250,83,198,21,236,96,16,129,6,228,
30,230,54,161,31,153,8,136,254,41,45,2,74,96,149,146,34,106,51,126,51,94,82,82,132,74,160,1,167,110,10,148,128,204,125,1,219,54,214,90,61,111,2,43,129,4,162,82,208,116,82,224,18,112,83,112,57,37,5,65,69,184,65,253,34,148,66,146,130,178,69,232,35,96,139,
112,146,113,137,114,20,161,18,248,64,225,175,161,47,2,98,251,141,146,158,225,218,167,190,134,154,2,109,68,155,116,186,17,221,100,252,98,252,161,236,70,84,163,156,141,200,109,197,26,54,219,138,37,175,93,204,151,241,105,227,208,182,226,38,249,91,241,28,
214,214,131,235,63,2,89,135,145,202,183,168,127,249,176,167,97,225,195,168,232,113,172,23,146,66,199,113,232,133,68,231,249,8,68,93,72,134,117,37,19,159,39,87,178,97,92,74,59,26,129,216,107,249,4,37,87,242,46,100,59,22,66,226,57,227,77,214,228,172,69,
206,228,195,100,152,159,102,229,216,8,216,72,196,56,63,193,63,106,184,187,89,136,209,63,83,0,0,0,26,102,99,84,76,0,0,0,31,0,0,0,32,0,0,0,28,0,0,0,0,0,0,0,2,0,1,0,25,0,0,237,248,122,27,0,0,2,83,102,100,65,84,0,0,0,32,120,156,213,151,207,78,83,65,20,198,
219,10,52,81,19,22,192,130,93,19,66,251,4,82,227,18,144,208,26,121,0,89,217,190,0,143,48,47,160,113,35,24,187,80,18,124,4,211,216,110,128,178,241,33,76,91,54,128,233,90,77,160,92,207,200,119,210,207,201,180,247,246,222,66,194,226,107,231,116,102,206,
249,205,153,191,77,25,99,82,9,148,129,98,251,176,31,105,104,220,206,233,33,229,113,250,167,227,146,107,192,188,168,144,0,226,95,6,154,162,47,99,56,209,148,219,224,191,161,188,83,23,5,254,64,212,176,133,64,116,33,202,70,132,120,128,239,45,244,13,80,230,
186,176,224,89,196,12,172,209,23,253,16,77,163,114,42,100,36,26,100,147,0,74,228,120,20,132,2,204,32,102,95,51,208,166,12,184,141,217,206,16,104,137,0,94,132,140,92,251,79,17,64,91,51,96,29,116,81,241,76,180,47,42,154,240,57,45,19,192,6,126,251,40,218,
241,12,192,29,76,118,24,192,17,236,111,102,144,110,134,216,19,181,68,179,162,85,2,120,42,218,38,59,71,253,53,248,67,209,115,124,91,159,29,6,104,163,209,177,232,74,212,240,100,96,153,2,84,69,43,14,64,21,125,237,174,40,80,63,77,251,7,180,253,12,251,148,
1,58,4,16,16,64,10,163,77,193,169,117,110,23,109,197,3,240,26,229,63,102,176,45,103,201,207,161,232,90,244,29,246,127,25,80,128,22,236,38,236,154,232,92,180,38,90,196,8,3,0,60,33,128,34,126,179,229,75,180,93,71,223,26,124,53,80,127,236,3,208,53,160,0,
117,216,61,216,187,162,121,140,94,167,96,24,64,31,109,223,195,238,193,87,29,246,73,148,12,40,64,23,246,91,209,2,1,84,16,148,167,128,1,108,219,55,206,224,110,29,160,26,17,160,53,137,41,112,1,220,41,152,67,31,223,20,120,1,220,12,232,34,180,7,203,153,241,
47,66,23,64,119,65,172,69,168,0,81,183,97,117,4,64,226,109,200,7,17,95,44,75,20,208,61,7,138,102,112,16,253,50,49,14,34,93,3,154,1,62,138,249,28,127,103,110,166,231,177,185,153,22,94,132,175,200,206,121,250,219,35,216,222,25,143,140,231,40,118,47,163,
21,115,199,151,81,148,235,88,129,124,215,113,121,4,40,251,243,94,199,147,120,144,108,210,200,98,61,72,226,60,201,94,18,64,156,39,217,79,205,128,93,241,73,31,165,5,167,46,10,196,39,209,215,176,198,97,78,10,102,2,207,242,123,249,199,68,149,248,175,217,
95,101,166,87,148,251,53,127,185,0,0,0,26,102,99,84,76,0,0,0,33,0,0,0,32,0,0,0,28,0,0,0,0,0,0,0,2,0,1,0,25,0,0,3,28,193,147,0,0,2,67,102,100,65,84,0,0,0,34,120,156,197,87,59,47,68,81,16,94,75,150,146,132,78,67,129,8,42,207,160,208,8,18,132,68,84,10,175,
68,69,79,51,133,70,67,194,15,209,144,37,86,131,68,8,191,64,4,17,225,31,32,193,154,179,190,201,142,227,220,235,236,93,178,197,183,57,115,206,157,153,111,30,231,177,49,34,138,21,18,230,167,8,136,98,160,24,136,162,155,241,107,79,228,106,32,111,93,59,10,
95,67,242,93,39,163,43,162,110,198,175,25,92,50,118,213,100,9,35,30,98,64,214,154,25,105,160,9,115,9,250,189,36,66,96,199,248,142,193,192,35,163,44,40,77,22,196,193,176,34,48,234,169,43,243,165,240,153,54,194,7,227,70,69,181,198,104,180,162,213,209,39,
48,30,80,4,250,49,183,202,152,10,33,33,115,198,198,181,241,45,25,184,195,66,10,242,142,21,173,203,224,160,34,96,250,96,2,99,19,80,181,35,128,184,146,19,8,58,45,4,110,177,112,204,120,99,28,64,46,161,239,61,81,199,232,115,16,48,205,56,7,221,103,70,189,
114,20,119,144,47,13,34,112,4,121,223,145,190,10,66,221,24,189,140,110,139,192,52,198,47,32,106,235,143,51,78,25,147,144,239,194,8,72,6,90,25,75,244,85,10,99,244,29,235,11,140,118,139,192,12,198,175,140,90,100,110,17,54,180,237,51,200,183,65,37,208,25,
184,130,188,204,168,68,138,211,136,182,77,17,232,80,4,222,240,237,50,228,43,216,218,67,0,71,46,2,210,132,66,32,73,95,181,123,128,193,45,70,149,202,192,108,8,129,119,124,187,9,221,7,216,74,98,253,196,39,3,73,200,247,144,55,44,2,51,112,234,42,129,16,88,
135,124,175,50,240,175,4,102,61,9,28,255,69,9,108,2,118,9,42,67,74,224,36,96,103,192,167,9,109,2,178,13,165,9,87,40,135,38,20,2,178,85,82,148,221,134,102,43,253,182,13,53,1,123,27,182,89,182,207,125,8,184,14,162,114,202,246,132,57,132,122,20,1,159,131,
104,140,60,14,162,19,10,63,138,107,224,220,140,135,172,12,204,83,246,40,110,160,240,163,248,199,93,32,77,120,72,209,46,35,147,129,200,151,145,190,142,91,168,64,215,113,190,15,146,145,128,111,131,8,152,219,240,73,50,112,65,223,83,174,107,238,130,235,73,
214,172,34,243,125,146,109,51,78,197,105,62,143,210,142,136,186,25,4,46,228,104,40,175,103,121,161,254,152,100,124,71,85,252,51,124,2,137,244,84,161,160,234,160,254,0,0,0,26,102,99,84,76,0,0,0,35,0,0,0,9,0,0,0,12,0,0,0,20,0,0,0,12,0,1,0,25,0,0,28,63,
170,232,0,0,0,152,102,100,65,84,0,0,0,36,120,156,99,104,104,104,248,9,196,74,64,204,2,196,121,64,108,2,196,12,64,124,8,136,255,3,241,41,16,231,15,16,139,0,113,21,84,240,54,84,209,14,32,254,11,82,204,0,101,136,2,241,36,168,134,167,64,204,4,196,219,161,
154,142,32,43,234,131,10,62,70,50,137,104,69,135,97,138,68,240,88,119,24,217,225,213,248,28,142,30,4,166,216,130,224,7,16,171,65,37,144,113,32,16,31,7,226,112,16,231,59,16,107,64,37,216,160,238,97,68,214,0,34,254,1,177,12,84,128,9,73,146,9,198,7,113,
98,160,130,40,186,145,197,0,178,23,211,125,74,202,123,232,0,0,0,26,102,99,84,76,0,0,0,37,0,0,0,32,0,0,0,26,0,0,0,0,0,0,0,3,0,1,0,25,0,0,135,205,191,70,0,0,2,45,102,100,65,84,0,0,0,38,120,156,205,150,75,47,67,65,20,199,111,41,77,8,18,175,16,11,11,17,214,
196,99,99,71,34,196,158,13,161,137,173,149,157,197,196,210,115,227,35,72,44,196,146,134,86,68,75,226,35,180,11,180,105,196,134,189,71,171,206,209,255,184,99,204,109,111,47,81,139,95,51,103,166,115,206,127,206,204,61,51,150,16,194,42,39,252,227,3,94,28,
84,2,47,115,63,226,126,235,32,252,46,5,249,12,109,191,75,65,159,115,249,167,129,168,43,18,192,105,108,18,120,153,203,49,235,185,113,77,92,160,179,139,88,38,58,11,56,146,43,236,39,114,160,15,125,75,138,160,98,89,140,113,108,11,14,238,209,121,8,251,64,
11,102,18,48,69,188,129,17,216,60,247,153,104,119,16,33,237,0,113,199,255,183,224,224,22,3,151,68,134,56,133,93,161,57,225,224,213,104,143,43,25,24,34,22,49,247,137,232,53,44,64,158,47,110,87,17,55,28,91,102,32,137,129,115,216,199,194,62,84,82,136,158,
137,9,69,192,48,49,143,54,11,232,86,130,154,190,178,0,22,157,211,5,196,96,159,24,82,206,172,138,252,246,112,22,70,53,1,11,138,128,30,109,1,76,35,49,67,52,65,80,210,36,32,10,59,12,123,141,72,32,64,155,18,112,142,24,116,16,240,66,116,136,252,182,196,137,
117,248,218,197,248,62,236,84,161,12,132,96,63,192,222,33,154,137,87,34,75,4,137,1,241,245,12,72,1,89,172,114,7,246,3,124,69,48,118,5,251,203,22,164,28,4,112,63,31,210,45,162,5,14,114,8,86,72,0,255,119,19,115,165,239,35,140,199,96,27,183,64,23,144,134,
189,109,16,48,228,176,5,82,192,22,236,52,124,133,96,203,154,243,235,2,130,46,5,24,51,224,101,11,84,1,165,108,65,180,148,12,60,10,251,16,178,83,62,132,25,172,86,23,32,235,0,143,155,14,97,88,216,135,176,232,103,24,17,246,103,24,71,138,91,149,128,179,5,
4,176,200,14,204,225,185,27,194,195,103,168,22,34,181,10,174,16,123,34,95,96,198,20,1,110,11,209,180,112,89,136,254,180,20,155,46,35,185,5,110,47,35,174,138,63,186,140,228,117,44,79,234,111,93,199,122,230,140,215,113,169,15,18,233,212,235,131,68,246,
159,17,9,110,212,139,242,60,201,106,136,90,125,160,44,143,210,127,243,44,47,11,239,174,126,241,31,111,35,166,246,0,0,0,26,102,99,84,76,0,0,0,39,0,0,0,32,0,0,0,24,0,0,0,0,0,0,0,4,0,1,0,25,0,0,7,122,227,176,0,0,2,74,102,100,65,84,0,0,0,40,120,156,197,86,
75,47,67,65,20,110,171,30,63,192,123,235,17,18,43,239,231,30,177,245,216,105,53,132,37,43,203,249,3,30,9,127,193,222,138,32,33,90,11,34,72,44,137,103,69,232,146,13,162,56,39,253,142,142,201,157,246,182,94,139,175,157,239,206,156,115,190,123,206,220,51,
227,81,74,121,52,120,9,126,252,123,178,0,219,230,100,98,195,63,62,4,52,131,186,17,97,11,232,198,150,215,248,204,135,165,132,97,66,81,6,142,116,12,18,218,93,216,126,206,241,79,25,192,227,101,194,59,97,9,60,93,58,89,108,8,227,126,216,62,166,121,1,121,86,
204,113,121,112,79,56,194,195,93,194,43,97,19,220,231,224,64,68,181,34,32,163,154,48,65,136,19,158,9,53,41,236,5,7,132,152,7,14,110,160,108,27,124,77,37,107,172,111,74,254,207,197,184,15,1,25,29,132,32,108,159,8,85,88,147,107,136,16,63,249,132,40,175,
23,1,23,152,8,131,175,59,40,54,223,166,91,203,64,11,97,68,19,80,109,172,245,26,246,121,132,115,93,192,37,38,34,224,27,224,236,104,0,138,153,115,221,234,48,238,209,4,180,106,2,184,4,21,88,51,68,168,212,2,251,53,1,23,78,2,36,3,82,130,99,240,105,240,51,
194,27,161,129,208,105,17,192,123,136,55,225,36,248,177,74,110,216,19,194,40,248,85,170,12,172,32,101,183,42,81,227,5,149,248,68,37,224,56,161,209,82,2,22,80,72,88,132,237,45,74,176,133,249,125,196,186,212,5,92,25,2,86,193,175,193,103,225,244,21,156,
131,53,89,4,196,145,129,25,240,107,248,90,65,246,194,78,2,204,12,136,128,40,248,60,156,198,53,1,45,150,18,136,128,57,240,40,124,173,130,239,252,150,128,144,33,96,214,34,32,242,19,37,8,26,2,204,18,20,254,68,9,210,109,194,102,67,128,52,34,217,132,11,42,
131,77,40,2,204,70,100,126,134,167,8,80,79,232,74,33,128,75,48,165,190,126,134,1,149,248,12,199,244,236,218,50,160,55,34,62,100,10,192,249,205,164,207,247,106,2,108,141,136,79,71,87,141,72,90,177,8,248,243,86,44,135,145,217,9,255,228,48,138,17,14,49,
177,167,178,59,142,57,160,28,199,47,132,218,20,246,2,222,140,119,60,40,87,217,95,72,2,42,121,33,25,128,237,131,114,119,33,225,53,37,230,228,119,175,100,124,250,181,185,176,253,114,37,251,207,75,169,215,233,161,223,165,131,76,4,89,241,1,73,48,142,139,
134,116,0,82,0,0,0,26,102,99,84,76,0,0,0,41,0,0,0,32,0,0,0,26,0,0,0,0,0,0,0,3,0,1,0,25,0,0,135,40,93,243,0,0,2,87,102,100,65,84,0,0,0,42,120,156,197,151,203,75,85,81,20,198,207,189,41,77,162,8,45,16,44,16,202,204,156,150,37,216,168,4,9,154,235,44,115,
156,154,96,217,104,255,5,169,8,77,108,26,52,79,208,108,16,248,40,234,15,40,71,234,181,81,143,161,66,62,110,183,111,193,183,188,171,205,62,231,158,115,148,28,252,116,239,115,246,90,235,59,107,237,215,141,156,115,145,161,0,78,240,127,148,3,177,45,102,177,
241,131,39,245,107,81,200,99,235,27,156,1,247,192,169,156,34,238,128,118,182,83,101,66,7,214,241,193,43,80,1,51,174,154,210,36,7,98,119,146,237,251,180,253,14,206,166,248,0,137,91,244,31,126,2,101,240,62,203,87,144,49,240,7,236,129,171,53,236,15,132,
201,159,54,112,137,15,150,249,21,111,83,10,24,5,79,216,30,162,237,111,112,57,193,94,131,75,204,54,105,108,129,85,79,192,130,171,166,184,232,57,210,178,116,115,172,112,13,12,6,4,248,171,194,150,228,43,216,142,104,180,201,151,139,158,0,95,185,56,212,154,
203,100,45,147,46,48,96,4,92,137,177,175,103,91,124,148,100,188,10,88,231,139,37,246,223,177,63,14,86,192,245,128,195,94,147,129,78,35,64,230,64,51,232,0,31,192,211,128,173,8,88,179,2,54,248,66,51,48,199,254,47,246,95,178,63,2,94,176,125,215,8,184,105,
4,236,131,6,48,197,254,79,102,174,9,12,131,11,180,223,8,9,208,12,168,128,18,83,60,9,78,155,128,253,224,70,76,6,68,192,57,240,156,182,155,244,245,154,239,223,24,223,7,2,74,49,2,190,177,63,1,206,51,189,18,96,144,101,9,9,40,27,1,21,250,144,250,47,208,246,
35,125,175,167,201,128,10,144,12,52,210,121,133,193,58,99,74,160,2,38,140,128,136,62,43,140,145,186,4,89,4,60,76,200,64,77,1,121,74,96,5,248,37,104,172,81,130,66,218,12,196,77,194,190,128,128,7,174,58,9,85,64,104,18,206,186,192,36,84,1,186,12,231,221,
191,203,80,15,167,71,96,154,237,158,4,1,73,203,240,98,168,4,113,27,209,51,151,125,35,218,117,57,54,34,221,138,85,64,214,173,248,150,59,196,86,188,237,170,135,209,138,39,160,142,134,161,195,232,182,201,128,61,140,118,64,171,25,27,119,162,126,1,91,210,
144,179,91,79,175,172,199,241,99,151,255,56,110,17,161,254,203,207,238,24,46,36,71,125,37,251,225,114,92,201,116,160,172,245,163,186,148,166,178,13,166,37,103,240,67,93,203,173,225,127,253,97,242,23,146,193,236,43,2,241,180,119,0,0,0,26,102,99,84,76,
0,0,0,43,0,0,0,32,0,0,0,28,0,0,0,0,0,0,0,2,0,1,0,25,0,0,238,51,81,92,0,0,2,108,102,100,65,84,0,0,0,44,120,156,197,87,77,79,83,81,16,109,169,6,22,18,55,40,70,88,34,137,59,81,2,104,130,9,159,137,252,139,202,66,77,76,128,133,174,103,9,9,34,11,54,110,252,
25,149,232,166,65,3,38,10,63,129,143,2,49,44,89,129,209,130,51,233,25,222,244,242,250,222,189,109,131,139,211,123,231,189,119,230,158,59,51,247,163,25,34,202,24,100,25,57,180,153,58,208,2,120,115,220,193,147,236,52,100,235,225,186,132,86,198,0,227,122,
160,35,253,174,143,209,29,194,213,78,14,237,7,198,57,99,217,121,158,4,253,102,2,220,29,70,187,175,8,119,6,63,224,164,72,81,78,211,4,92,67,251,22,220,50,227,190,47,95,103,160,179,248,10,39,171,158,14,100,240,54,244,103,192,61,97,220,243,224,203,187,156,
251,240,27,156,124,166,40,188,62,105,16,204,129,251,219,8,144,90,138,75,195,197,51,249,121,204,232,199,131,117,71,64,18,100,6,243,140,69,216,179,224,158,50,122,107,13,104,250,143,100,108,233,156,49,118,157,8,124,129,125,151,49,102,72,210,106,206,71,240,
173,224,1,99,218,68,160,135,162,194,188,99,184,54,37,82,172,103,25,144,84,192,154,19,129,239,176,231,98,102,50,69,149,130,43,35,138,121,124,251,151,113,155,241,2,246,186,137,152,114,91,33,224,92,5,236,56,2,10,32,252,66,132,62,226,125,59,162,34,253,103,
38,2,131,140,231,70,64,7,99,5,220,67,198,13,112,110,82,84,27,219,86,128,70,64,87,193,39,216,123,176,87,96,111,49,142,169,178,204,134,83,4,188,131,93,2,247,53,227,136,241,198,250,86,1,123,53,4,236,195,126,207,232,52,3,190,164,74,225,198,9,144,148,220,
2,71,236,3,248,42,194,254,9,123,215,39,2,42,96,25,179,250,3,59,143,65,85,192,80,130,128,125,248,42,192,94,107,150,128,33,71,128,174,2,21,176,20,34,32,52,5,82,225,3,9,41,232,240,72,65,85,13,212,138,64,137,170,139,112,147,162,34,124,234,8,176,203,208,167,
8,75,113,2,116,25,138,128,180,101,56,149,34,32,109,25,86,237,3,34,32,107,34,224,110,68,179,20,182,17,73,13,188,130,189,17,195,189,180,17,105,4,66,182,226,81,19,1,119,43,214,195,104,156,170,183,98,43,226,98,43,126,66,245,31,70,11,116,249,48,18,1,62,135,
209,67,198,160,235,180,89,199,177,10,240,58,142,27,185,144,8,207,189,144,200,113,28,124,33,249,175,87,50,157,137,180,141,92,74,39,169,9,151,210,70,175,229,178,26,186,66,184,113,78,106,217,190,34,130,184,113,78,174,244,175,217,63,135,199,74,14,107,116,
171,84,0,0,0,26,102,99,84,76,0,0,0,45,0,0,0,32,0,0,0,30,0,0,0,0,0,0,0,1,0,1,0,25,2,0,168,161,234,168,0,0,2,114,102,100,65,84,0,0,0,46,120,156,213,151,59,79,84,81,16,199,119,93,16,34,22,38,128,165,9,68,22,181,37,81,26,42,80,19,67,73,71,133,64,208,10,109,
44,201,36,98,169,70,27,165,32,4,190,0,22,26,136,90,16,94,141,118,214,60,150,135,17,190,0,248,128,117,38,252,143,59,59,57,247,238,61,119,183,177,248,237,222,57,247,206,204,255,206,121,222,12,17,101,12,231,60,109,73,17,223,108,136,79,218,68,62,178,17,215,
65,2,196,177,179,138,228,109,204,165,16,17,238,34,135,255,231,204,41,243,212,180,199,225,158,233,97,126,50,223,152,11,73,69,216,55,248,194,20,153,37,74,62,30,234,240,255,4,190,194,181,164,254,86,192,10,2,44,166,16,48,14,223,35,166,35,173,128,85,4,249,
152,66,192,99,248,74,55,228,67,4,228,84,16,43,160,30,247,125,129,178,184,215,224,17,208,97,252,125,201,165,61,103,27,215,140,0,155,208,119,237,112,2,142,169,242,76,250,231,47,63,253,76,31,26,214,17,228,51,236,135,204,123,230,6,149,74,234,156,207,51,211,
204,44,149,143,129,95,204,21,166,29,190,99,202,87,39,151,156,253,25,56,237,147,127,16,30,194,126,3,187,129,74,37,191,77,165,81,223,197,220,199,245,9,211,76,103,83,90,236,31,202,167,30,2,178,200,89,116,2,54,241,192,50,236,5,60,84,64,192,183,158,50,222,
195,61,161,91,9,248,195,180,50,47,112,79,98,95,52,190,141,204,134,22,176,109,42,176,0,123,7,246,20,236,65,102,194,83,129,91,70,64,11,4,20,17,67,6,220,85,230,25,149,186,115,91,11,40,68,8,216,133,253,154,105,82,9,7,152,155,17,2,78,80,129,151,176,247,16,
235,29,236,79,176,11,73,42,224,4,72,176,203,204,111,188,225,40,146,58,1,186,11,172,0,137,33,221,185,8,223,85,95,5,66,5,140,120,4,12,27,1,174,11,18,9,168,212,5,175,232,108,131,209,93,208,29,211,5,45,158,46,152,167,242,41,190,19,82,1,223,32,188,107,4,12,
81,21,131,112,139,226,167,161,91,7,52,118,26,106,1,193,211,240,59,149,239,5,174,2,113,11,209,29,85,1,189,16,137,128,102,85,129,3,170,176,16,197,45,197,15,40,126,41,158,97,230,40,122,41,254,64,209,75,113,47,97,41,214,212,98,51,146,221,48,104,51,210,219,
177,21,16,178,29,63,82,2,242,198,223,39,162,108,59,174,197,129,196,39,224,255,59,146,125,69,144,229,20,2,244,161,244,122,168,0,125,44,151,185,59,105,218,227,168,201,177,92,87,34,95,201,201,67,213,31,38,181,64,151,59,245,167,153,13,148,70,68,208,199,233,
95,146,83,167,241,27,55,177,255,0,0,0,26,102,99,84,76,0,0,0,47,0,0,0,32,0,0,0,24,0,0,0,0,0,0,0,4,0,1,0,25,0,0,7,195,160,150,0,0,2,108,102,100,65,84,0,0,0,48,120,156,197,150,187,79,84,65,20,198,175,47,136,9,62,18,65,37,106,92,11,98,148,70,163,65,10,8,
21,177,49,88,170,37,154,104,41,88,152,216,157,104,103,130,75,52,241,17,11,105,180,133,10,209,96,54,89,95,241,241,55,40,138,198,229,15,80,1,5,252,70,191,195,61,119,184,59,220,203,146,88,252,246,206,153,157,51,243,205,153,57,51,19,137,72,4,214,240,187,
21,244,128,77,94,253,114,104,187,195,96,119,30,95,45,172,227,247,17,88,0,247,189,250,16,218,166,155,190,31,243,76,192,159,193,27,48,7,74,180,215,102,16,176,158,223,203,20,224,252,15,100,245,247,5,60,103,39,79,104,111,224,0,161,153,168,128,62,250,254,
4,45,198,63,24,69,29,92,149,190,96,39,79,83,26,167,137,112,126,245,44,247,211,119,26,236,207,224,251,183,222,111,240,146,157,140,211,62,13,30,128,130,25,176,90,167,42,96,22,236,5,59,192,16,56,21,242,85,195,23,48,70,251,27,237,91,18,135,212,182,63,2,142,
177,124,73,226,61,176,13,92,167,253,21,212,25,17,9,225,238,231,53,24,241,4,60,102,195,207,224,55,184,39,75,179,226,32,152,103,251,102,112,129,101,215,190,9,20,89,118,89,209,144,50,251,97,55,118,68,167,10,43,203,70,64,68,1,206,190,43,241,134,211,20,235,
225,127,142,14,208,107,4,52,130,1,218,19,96,35,125,246,240,91,199,49,23,34,206,226,131,36,179,64,5,76,210,190,67,251,25,235,246,129,78,35,192,45,195,89,79,64,145,246,23,250,94,1,63,192,53,218,46,50,243,26,129,79,203,8,112,157,109,55,3,186,112,31,173,
34,96,206,44,129,21,80,162,253,142,246,132,70,64,195,20,18,48,200,89,253,98,196,122,57,168,10,104,15,8,152,100,95,163,180,203,171,37,160,221,19,112,206,19,112,35,143,128,188,75,112,30,180,5,150,32,109,15,232,18,188,247,5,100,217,132,183,37,185,9,11,160,
203,8,104,147,165,155,80,35,96,55,225,119,112,213,8,88,220,132,83,242,47,63,179,164,225,102,150,79,26,1,126,26,186,37,72,75,67,189,170,19,105,104,15,162,87,116,26,149,228,65,164,2,236,65,212,42,241,65,180,83,170,31,68,78,64,240,32,178,149,254,81,92,161,
125,83,242,29,197,110,9,50,31,197,105,2,244,50,58,35,43,191,140,92,84,134,36,227,101,164,127,170,128,90,174,227,25,169,225,58,174,229,65,114,81,226,247,64,174,7,137,21,240,86,254,211,147,76,85,62,148,149,63,74,143,203,42,60,74,183,128,19,18,167,77,222,
103,249,33,176,43,143,239,31,255,237,134,163,9,232,177,83,0,0,0,26,102,99,84,76,0,0,0,49,0,0,0,32,0,0,0,28,0,0,0,0,0,0,0,2,0,1,0,25,0,0,2,110,71,223,0,0,2,105,102,100,65,84,0,0,0,50,120,156,197,151,203,74,28,81,16,134,123,156,209,44,132,72,48,226,46,
8,226,198,77,64,208,232,94,188,44,226,38,201,82,69,3,209,141,152,64,34,46,107,161,24,33,94,112,35,70,240,13,132,64,76,162,232,198,75,226,91,120,153,113,163,111,32,26,59,117,240,47,167,230,120,250,50,61,97,92,124,246,84,119,87,213,223,117,234,92,244,136,
200,123,72,236,27,21,76,6,215,36,1,211,197,250,106,35,101,61,180,237,40,82,73,124,245,151,155,107,19,51,201,52,36,20,209,201,52,23,227,107,11,216,98,124,102,29,118,21,221,14,73,88,176,52,174,125,240,189,96,158,224,94,165,122,30,42,64,18,252,97,174,153,
29,199,203,65,34,50,184,78,48,55,204,149,170,66,148,239,61,1,251,248,138,109,216,221,204,103,166,62,36,144,8,120,15,223,75,186,29,194,26,102,150,233,162,194,42,223,19,144,81,65,126,35,200,22,236,28,236,57,43,153,136,49,65,171,96,127,192,187,166,130,181,
204,20,236,83,229,167,63,192,12,77,218,86,116,0,167,95,8,158,67,192,175,120,254,136,130,123,66,11,168,99,22,241,251,132,169,166,124,79,84,104,127,243,167,159,121,67,249,30,16,1,186,2,203,142,132,38,232,55,230,59,236,49,37,224,41,170,230,91,2,52,175,152,
1,15,47,157,83,97,15,216,2,86,96,247,48,163,148,239,15,31,188,96,134,45,1,243,176,179,248,234,22,102,141,233,128,191,153,45,190,249,97,58,247,8,55,247,2,4,44,161,252,87,176,95,34,233,95,208,238,16,176,0,251,12,177,126,194,222,133,109,114,222,72,5,78,
34,42,96,130,213,35,153,73,48,194,180,6,84,192,188,83,167,4,152,24,102,204,55,225,123,128,216,199,82,129,56,2,22,241,85,215,176,135,145,84,4,232,10,184,4,120,136,233,35,135,135,156,137,5,12,57,4,188,181,4,72,15,252,23,1,246,16,188,99,218,66,134,64,247,
64,208,16,220,9,72,218,132,29,84,216,132,67,228,158,5,210,132,63,96,239,81,190,7,238,154,240,34,162,2,50,13,123,201,61,13,219,44,1,122,8,100,26,62,103,86,33,214,35,53,13,7,153,215,228,94,136,178,20,189,16,109,80,137,11,145,70,47,197,41,42,211,82,28,103,
51,250,66,241,55,35,105,194,105,42,98,51,146,7,82,1,189,29,207,80,188,237,120,156,10,183,227,199,20,115,59,214,129,15,41,249,129,228,19,149,112,32,17,117,178,88,148,253,72,38,2,26,153,143,204,179,40,229,1,116,82,194,67,169,203,161,172,199,114,93,137,
168,146,135,81,210,63,38,15,194,63,240,221,70,54,27,150,160,161,0,0,0,26,102,99,84,76,0,0,0,51,0,0,0,32,0,0,0,26,0,0,0,0,0,0,0,3,0,1,0,25,0,0,107,117,75,112,0,0,2,63,102,100,65,84,0,0,0,52,120,156,197,150,59,47,132,81,16,134,191,101,5,75,34,17,162,80,
168,69,163,113,151,40,40,252,2,180,174,53,65,69,113,26,84,46,33,66,162,81,40,213,68,226,22,150,66,73,161,16,118,93,194,31,208,177,152,225,61,76,198,119,219,37,20,207,238,55,231,156,57,243,158,57,87,199,24,227,252,39,186,32,139,200,198,127,38,29,70,225,
159,145,128,136,170,140,64,72,212,165,46,136,8,136,6,13,70,142,156,255,91,136,53,162,209,163,211,160,192,157,68,67,58,190,90,192,17,241,74,236,192,230,206,134,137,34,159,142,108,202,59,224,251,72,20,19,49,98,148,168,83,49,92,5,216,142,227,196,51,177,
5,251,18,157,78,154,175,57,214,157,216,50,14,150,2,101,196,24,124,47,68,240,111,3,176,133,58,3,155,40,187,131,160,21,17,76,118,194,163,207,197,247,32,124,185,125,9,49,143,239,27,162,80,180,183,254,239,235,68,143,38,46,4,56,112,102,123,9,118,142,116,86,
190,67,66,64,41,49,3,59,73,20,168,182,159,190,252,19,3,58,3,108,223,194,94,214,169,3,173,68,187,139,128,18,33,224,154,200,67,155,106,49,136,124,142,203,31,231,196,110,128,0,155,129,117,226,148,40,39,42,81,199,84,16,3,30,2,110,225,59,5,123,17,246,62,199,
118,80,248,128,180,28,120,8,152,69,90,109,192,126,162,94,216,77,68,183,18,48,171,4,236,194,62,65,172,123,182,185,226,133,72,160,209,161,135,128,57,8,120,66,251,30,162,70,8,168,67,25,127,167,208,86,11,216,128,125,0,251,138,251,178,25,72,134,20,144,130,
221,131,160,86,64,125,8,1,155,176,227,176,147,54,3,191,37,160,87,9,208,107,192,83,64,152,41,176,107,64,78,65,173,207,20,184,173,1,61,5,9,57,5,233,46,194,62,243,113,95,248,45,66,157,1,185,8,249,144,251,92,132,188,13,247,76,248,109,120,102,130,183,161,
219,20,76,192,94,48,106,27,202,131,232,216,67,128,215,65,212,102,210,59,136,170,204,215,221,241,30,87,119,248,155,71,241,180,9,121,20,203,203,200,10,216,64,249,159,93,70,182,240,200,252,252,58,230,93,194,215,241,184,9,121,29,59,46,25,216,134,205,43,61,
232,65,98,5,232,7,9,95,54,35,38,228,131,196,86,54,19,171,194,73,18,230,73,214,101,210,124,206,249,53,250,211,71,169,204,68,160,147,15,236,155,241,179,252,95,120,3,94,177,229,57,234,118,107,91,0,0,0,26,102,99,84,76,0,0,0,53,0,0,0,32,0,0,0,24,0,0,0,0,0,
0,0,4,0,1,0,25,0,0,235,158,182,21,0,0,2,45,102,100,65,84,0,0,0,54,120,156,205,86,203,46,68,65,16,189,119,60,226,181,52,225,19,252,128,215,70,108,108,108,136,88,216,144,32,204,134,4,177,166,127,128,145,136,32,241,15,22,146,145,72,216,120,71,172,176,52,
153,24,177,178,99,105,140,42,78,209,122,186,239,189,131,153,88,156,153,156,238,174,170,83,85,253,184,158,82,202,11,64,140,80,73,240,67,214,217,224,195,54,22,180,206,22,80,254,205,160,81,68,112,192,10,135,152,72,2,76,180,16,134,9,181,69,136,16,212,192,
182,197,72,206,42,64,38,217,224,146,48,8,126,67,200,19,22,180,12,93,1,57,243,105,66,31,248,2,108,175,130,42,97,10,184,128,209,1,248,3,33,71,216,10,16,32,99,35,176,125,69,246,107,176,205,18,26,194,4,200,196,33,28,164,192,239,224,116,29,188,90,21,246,184,
10,255,243,132,23,160,137,176,4,219,12,161,78,19,251,173,21,50,40,89,28,193,104,23,60,11,190,97,201,220,87,223,43,48,131,181,44,160,145,144,212,4,212,91,108,57,145,74,211,169,75,192,38,120,7,161,223,33,100,214,16,176,12,158,197,124,55,97,135,208,107,
86,96,142,48,129,129,19,135,128,85,40,126,6,239,67,224,99,216,240,218,169,16,1,123,224,231,224,9,142,237,97,240,81,125,237,1,155,0,46,103,179,250,216,31,57,24,183,97,142,209,73,24,117,180,32,11,177,41,216,30,194,55,199,204,123,24,76,135,8,88,129,211,
23,240,49,66,43,108,25,237,24,203,131,199,13,1,30,124,230,53,1,183,188,86,42,144,137,32,32,14,231,204,199,17,84,42,208,81,132,128,35,240,140,84,224,39,2,198,44,2,198,13,1,230,30,112,10,136,210,130,164,209,130,81,8,112,181,192,220,3,182,22,164,245,22,
132,109,66,206,134,47,23,217,132,147,200,58,104,19,234,21,240,225,51,167,85,224,115,19,242,49,76,96,240,216,33,64,142,225,147,250,58,134,124,163,157,40,251,49,180,181,64,142,225,25,56,39,241,126,12,117,184,4,252,246,34,226,53,93,132,109,66,143,110,207,
63,165,186,138,69,64,70,69,184,138,197,25,11,224,62,149,245,49,242,84,225,115,188,175,254,238,57,190,87,17,158,99,17,48,68,56,37,12,128,255,230,131,100,17,182,215,218,26,167,0,235,164,42,227,39,153,94,9,95,253,163,143,210,146,127,150,191,1,91,197,132,
235,107,201,189,114,0,0,0,26,102,99,84,76,0,0,0,55,0,0,0,32,0,0,0,26,0,0,0,0,0,0,0,3,0,1,0,25,0,0,107,41,234,227,0,0,2,94,102,100,65,84,0,0,0,56,120,156,189,151,57,78,67,49,16,134,95,194,190,72,72,64,66,3,29,92,1,16,20,84,20,220,1,10,214,134,6,4,162,
162,48,28,0,144,16,98,17,52,220,129,165,0,129,4,20,108,103,96,13,5,18,23,96,11,51,228,31,197,113,108,191,151,176,20,127,236,241,243,216,159,199,243,236,151,64,41,21,120,20,39,149,132,244,241,137,125,99,190,62,62,103,175,99,129,114,142,229,234,28,71,189,
153,212,167,217,133,40,14,223,102,31,132,139,84,202,115,82,154,52,13,187,52,100,149,252,188,2,246,20,124,207,125,160,182,198,122,148,181,164,20,233,147,180,21,2,96,91,221,38,124,83,24,203,218,79,42,146,104,179,164,23,210,4,236,7,172,98,213,3,32,131,86,
145,230,72,131,176,87,225,123,75,170,214,252,115,32,204,65,174,225,116,108,0,172,193,46,87,153,189,213,7,17,168,17,244,77,99,197,75,168,223,145,106,92,17,11,48,160,36,217,9,156,118,12,128,117,199,202,57,114,149,42,187,231,239,164,55,82,146,180,160,1,
84,64,189,42,187,29,223,11,49,7,61,133,211,158,35,2,27,164,35,82,139,5,104,2,125,25,162,81,3,120,196,243,21,216,219,186,95,0,218,4,26,206,28,0,139,164,6,45,196,147,120,222,79,26,64,125,210,1,112,143,104,29,168,76,82,94,162,63,207,153,228,202,147,214,
232,3,96,135,87,210,7,105,140,212,170,1,181,145,70,13,128,69,216,15,24,107,23,246,41,236,43,158,59,64,99,10,148,146,3,38,192,18,0,62,96,15,145,58,177,34,110,235,70,91,26,118,194,2,176,15,251,4,115,241,214,164,5,224,70,229,38,97,24,192,48,169,93,139,64,
7,218,124,0,123,70,4,110,126,2,48,132,73,125,0,146,3,145,0,194,182,64,114,64,0,248,176,233,194,22,124,90,182,192,150,3,2,32,91,144,18,128,98,146,144,19,174,77,139,0,215,229,32,50,223,2,87,18,242,156,223,73,152,132,67,24,128,235,53,236,87,249,175,161,
190,5,247,120,126,136,104,93,193,230,57,19,129,202,61,76,92,0,114,16,113,89,236,65,180,12,123,75,247,227,159,40,71,241,154,202,159,208,119,20,55,169,252,163,184,140,212,163,50,151,150,204,27,211,7,227,82,46,163,35,7,64,212,203,136,47,159,200,151,81,160,
178,215,241,12,233,153,52,110,0,68,189,142,231,85,145,215,177,174,58,148,255,250,65,98,14,36,229,165,250,249,39,217,133,199,199,26,129,152,6,240,239,31,165,182,104,252,134,10,250,44,55,87,241,167,127,76,190,0,136,211,229,1,49,80,191,22,0,0,0,26,102,99,
84,76,0,0,0,57,0,0,0,32,0,0,0,28,0,0,0,0,0,0,0,2,0,1,0,25,0,0,2,215,4,249,0,0,2,120,102,100,65,84,0,0,0,58,120,156,197,87,187,78,27,65,20,93,240,154,71,130,64,72,128,242,11,105,104,130,131,64,130,15,8,69,42,26,58,160,2,170,72,72,17,169,110,19,197,164,
192,72,230,97,144,146,191,72,160,0,91,2,4,2,210,83,241,10,16,36,16,63,64,72,150,59,112,134,29,143,103,118,215,94,1,197,177,247,206,220,199,153,59,119,239,204,58,68,228,4,160,138,145,8,209,9,66,2,62,172,58,97,193,43,13,28,217,87,152,65,51,163,35,70,224,
14,248,176,146,8,115,144,103,120,140,81,242,83,26,102,35,117,70,96,187,26,164,111,90,185,116,208,192,248,3,39,223,49,230,70,32,32,117,190,193,246,12,190,140,89,208,131,171,242,11,198,33,156,204,69,32,80,133,249,90,200,179,176,61,130,175,64,2,114,34,201,
120,3,185,142,113,12,39,57,204,215,144,121,27,76,251,59,15,219,99,133,64,53,80,66,32,161,25,125,133,124,170,17,48,5,148,207,141,208,27,135,156,83,8,188,180,217,235,3,187,48,202,67,62,129,188,8,249,53,163,71,115,148,164,226,162,243,64,102,26,207,39,152,
127,207,216,102,12,40,217,184,35,224,146,191,183,235,48,250,161,17,152,129,124,1,185,207,144,210,15,140,27,198,53,163,141,49,165,17,88,129,188,67,126,61,185,106,90,4,54,160,180,164,17,16,206,94,41,43,252,72,126,161,214,43,4,60,144,104,81,8,252,198,188,
88,212,63,196,120,136,41,126,190,48,38,48,176,105,33,144,129,211,27,200,99,88,193,30,224,98,76,37,144,209,50,176,4,121,11,242,39,70,218,193,224,149,182,5,58,1,177,159,173,88,129,144,135,24,93,74,70,186,49,230,65,167,213,64,96,25,178,204,128,136,233,57,
48,56,40,147,192,48,227,45,227,63,208,137,177,32,2,50,3,146,192,190,208,173,148,192,16,130,6,17,208,139,80,39,112,32,9,68,217,130,140,70,96,16,105,183,109,65,80,13,148,108,65,154,238,11,66,60,135,21,225,95,242,15,167,176,34,180,101,64,22,161,40,252,73,
135,226,191,134,178,205,134,189,134,63,201,242,26,70,105,68,89,200,151,84,220,136,68,39,140,218,136,86,33,239,146,127,238,184,142,226,72,252,255,34,115,43,94,32,191,21,247,42,43,176,181,226,38,42,173,129,119,140,53,70,63,105,173,88,64,30,70,89,24,125,
166,202,14,35,65,52,214,97,36,136,180,227,249,49,142,227,4,89,142,99,147,19,97,116,68,79,116,33,81,157,168,87,178,115,138,127,37,59,167,136,87,50,19,10,84,124,41,45,135,192,40,108,11,65,250,182,9,245,90,158,138,16,212,134,20,197,184,150,63,235,135,137,
106,248,168,159,102,183,27,32,69,42,7,35,133,44,0,0,0,0,73,69,78,68,174,66,96,130,0,0 };

const char* README_mdwaveform_png = (const char*) temp_binary_data_5;

//================== Makefile.am ==================
static const unsigned char temp_binary_data_6[] =
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

const char* Makefile_am = (const char*) temp_binary_data_6;

//================== soundtouch_config.h.in ==================
static const unsigned char temp_binary_data_7[] =
"/* Use Float as Sample type */\n"
"#undef SOUNDTOUCH_FLOAT_SAMPLES\n"
"\n"
"/* Use Integer as Sample type */\n"
"#undef SOUNDTOUCH_INTEGER_SAMPLES\n"
"\n"
"/* Use ARM NEON extension */\n"
"#undef SOUNDTOUCH_USE_NEON\n";

const char* soundtouch_config_h_in = (const char*) temp_binary_data_7;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes);
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x90e15cf5:  numBytes = 4243; return CMakeLists_txt;
        case 0xf1c33844:  numBytes = 4381; return CMakePresets_json;
        case 0xfb707ae3:  numBytes = 237; return libbungee_pc_in;
        case 0x34bc1021:  numBytes = 17097; return LICENSE;
        case 0x64791dc8:  numBytes = 13256; return README_md;
        case 0xd86927ef:  numBytes = 17945; return README_mdwaveform_png;
        case 0x1a187401:  numBytes = 1074; return Makefile_am;
        case 0x6fff950a:  numBytes = 188; return soundtouch_config_h_in;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "CMakeLists_txt",
    "CMakePresets_json",
    "libbungee_pc_in",
    "LICENSE",
    "README_md",
    "README_mdwaveform_png",
    "Makefile_am",
    "soundtouch_config_h_in"
};

const char* originalFilenames[] =
{
    "CMakeLists.txt",
    "CMakePresets.json",
    "libbungee.pc.in",
    "LICENSE",
    "README.md",
    "README.md-waveform.png",
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
