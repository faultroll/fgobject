cmake_minimum_required(VERSION 3.5)

include(util.cmake)

project(fgobject)

set(CMAKE_BUILD_TYPE MinSizeRel CACHE STRING "Set Build Type" FORCE)

set(custom_common_compiler_flags
  -Os
  -Wall
  -Wextra
  # -Winvalid-pch
  -D_POSIX_C_SOURCE=200809L
  )
set(custom_c_compiler_flags
  ${custom_common_compiler_flags}
  -std=c11
  -Wpedantic
  )
set(custom_cxx_compiler_flags
  ${custom_common_compiler_flags}
  -std=c++11
  -Weffc++
  )
set_custom_flags("c" "compiler" custom_c_compiler_flags)
set_custom_flags("cxx" "compiler" custom_cxx_compiler_flags)
set(custom_common_linker_flags
  -Wl,--gc-sections
  -Wl,--as-needed
  -rdynamic
  )
set_custom_flags("c" "linker" custom_c_compiler_flags)
set_custom_flags("cxx" "linker" custom_cxx_compiler_flags)

set(${PROJECT_NAME}_PRJ_DIR ${CMAKE_SOURCE_DIR}/../gobject)
# message("${${PROJECT_NAME}_PRJ_DIR}")

add_subdirectory(fgbase)
add_subdirectory(test)

set(${PROJECT_NAME}_SRC
	gobject.c
)
set(${PROJECT_NAME}_SRC
	${${PROJECT_NAME}_SRC}
	gvalue.c
	# gvaluearray.c
	gvaluetransform.c
	gvaluetypes.c
)
set(${PROJECT_NAME}_SRC
	${${PROJECT_NAME}_SRC}
	gtype.c
	gtypemodule.c
	gtypeplugin.c
	gatomicarray.c
)
set(${PROJECT_NAME}_SRC
	${${PROJECT_NAME}_SRC}
	gparam.c
	gparamspecs.c
	genums.c
)
set(${PROJECT_NAME}_SRC
	${${PROJECT_NAME}_SRC}
	# gsignal.c
	# gclosure.c
	# gmarshal.c
	# gboxed.c
	# gbinding.c
	# gsourceclosure.c
)
list_transform_prepend(${PROJECT_NAME}_SRC ${PROJECT_NAME}_PRJ_DIR)
# message("${${PROJECT_NAME}_SRC}")

add_library(${PROJECT_NAME} SHARED
	${${PROJECT_NAME}_SRC}
	$<TARGET_OBJECTS:fgobject::fgbase>
)
add_library(fgobject::fgobject ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
	PRIVATE ${${PROJECT_NAME}_PRJ_DIR}
	# TODO use son's instead
	PUBLIC ${CMAKE_SOURCE_DIR}
	PUBLIC ${CMAKE_SOURCE_DIR}/mbuild
	PUBLIC ${CMAKE_SOURCE_DIR}/mbuild/glib
	PUBLIC ${CMAKE_SOURCE_DIR}/glib
)

target_compile_definitions(${PROJECT_NAME}
	PRIVATE GOBJECT_COMPILATION
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE fgobject::fgbase
)

