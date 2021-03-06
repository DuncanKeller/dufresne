# Install script for directory: C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/SDL2")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/build/Debug/SDL2.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/build/Release/SDL2.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/build/MinSizeRel/SDL2.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/build/RelWithDebInfo/SDL2.lib")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/build/Debug/SDL2.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/build/Release/SDL2.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/build/MinSizeRel/SDL2.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/build/RelWithDebInfo/SDL2.lib")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/build/Debug/SDL2main.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/build/Release/SDL2main.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/build/MinSizeRel/SDL2main.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/build/RelWithDebInfo/SDL2main.lib")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL2" TYPE FILE FILES
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/begin_code.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/close_code.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_assert.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_atomic.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_audio.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_bits.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_blendmode.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_clipboard.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_config_android.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_config_iphoneos.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_config_macosx.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_config_minimal.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_config_pandora.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_config_psp.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_config_windows.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_config_winrt.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_config_wiz.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_copying.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_cpuinfo.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_egl.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_endian.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_error.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_events.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_filesystem.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_gamecontroller.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_gesture.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_haptic.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_hints.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_joystick.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_keyboard.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_keycode.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_loadso.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_log.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_main.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_messagebox.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_mouse.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_mutex.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_name.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_opengl.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_opengles.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_opengles2.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_pixels.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_platform.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_power.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_quit.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_rect.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_render.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_revision.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_rwops.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_scancode.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_shape.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_stdinc.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_surface.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_system.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_syswm.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_test.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_test_assert.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_test_common.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_test_compare.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_test_crc32.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_test_font.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_test_fuzzer.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_test_harness.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_test_images.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_test_log.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_test_md5.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_test_random.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_thread.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_timer.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_touch.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_types.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_version.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/include/SDL_video.h"
    "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/build/include/SDL_config.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/build/Debug/SDL2.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/build/Release/SDL2.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/build/MinSizeRel/SDL2.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/build/RelWithDebInfo/SDL2.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/Duncan/Downloads/SDL2-2.0.3/SDL2-2.0.3/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
