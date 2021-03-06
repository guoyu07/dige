cmake_minimum_required (VERSION 2.6)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                      ${CMAKE_SOURCE_DIR}/cmake)

project (dige)

find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
find_package(Boost REQUIRED)

include(${QT_USE_FILE})

SET(CMAKE_VERBOSE_MAKEFILE off)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}
                    $ENV{HOME}/local/include
                    ${Boost_INCLUDE_DIRS})

link_directories($ENV{HOME}/local/lib)

IF(EXISTS $ENV{INSTALL_PREFIX})
  set(CMAKE_INSTALL_PREFIX $ENV{INSTALL_PREFIX} CACHE PATH "Install prefix")
ENDIF(EXISTS $ENV{INSTALL_PREFIX})
message(STATUS "Install prefix: " ${CMAKE_INSTALL_PREFIX})


set(WITH_FFMPEG CACHE BOOL "Enable video recording (need FFmpeg)")
IF(WITH_FFMPEG)
  find_package(FFmpeg)
  if (NOT FFMPEG_FOUND)
    message(FATAL_ERROR "FFmpeg not found")
  endif (NOT FFMPEG_FOUND)
  add_definitions(-D__STDC_CONSTANT_MACROS) # Needed by ffmpeg.
  set(RECORDING_SRC dige/recorder.cpp)
  message(STATUS "Recording enabled")
  include_directories(${FFMPEG_INCLUDE_DIRS})
  message(STATUS "FFMPEG INCLUDE: " ${FFMPEG_INCLUDE_DIRS})
ENDIF(WITH_FFMPEG)


IF (${CMAKE_C_COMPILER_ID} MATCHES GNU)
   add_definitions(-W -Wall -Wextra)
ENDIF()

add_library(dige
  dige/event/or_event.cpp
  dige/event/click.cpp
  dige/event/dblclick.cpp
  dige/event/key_release.cpp
  dige/event/key_press.cpp
  dige/event/event.cpp
  dige/event/event_set.cpp
  dige/event/make_event.cpp
  dige/event/mouse_move.cpp
  dige/event/keycode.cpp
  dige/event/event_queue.cpp
  dige/shortcuts/reset_panzoom.cpp
  dige/shortcuts/shortcuts.cpp
  dige/pause.cpp
  dige/widgets/gl_widget.cpp
  dige/widgets/image_view.cpp
  dige/widgets/label.cpp
  dige/widgets/tracer.cpp
  dige/widgets/tracer_accu.cpp
  dige/widgets/tracer_view.cpp
  dige/widgets/push_button.cpp
  dige/widgets/slider.cpp
  dige/widgets/slider_impl.cpp
  dige/abstract_texture.cpp
  dige/color_picker.cpp
  dige/need_qapp.cpp
  dige/window.cpp
  dige/panzoom.cpp
  dige/process_events.cpp
  dige/ui_layout.cpp
  dige/pick_coords.cpp
  dige/displaylist.cpp
  dige/color_picker_control.cpp
  dige/panzoom_control.cpp
  ${RECORDING_SRC})

install(TARGETS dige DESTINATION lib/)
install(TARGETS dige DESTINATION lib/Debug CONFIGURATIONS Debug)
install(TARGETS dige DESTINATION lib/Release CONFIGURATIONS Release)

install(DIRECTORY dige DESTINATION include
  FILES_MATCHING PATTERN "*.h")
install(DIRECTORY dige DESTINATION include
  FILES_MATCHING PATTERN "*.hpp")
