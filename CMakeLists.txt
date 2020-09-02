cmake_minimum_required(VERSION 3.5)

project(fgobject)

set(CMAKE_BUILD_TYPE MinSizeRel)

set(${PROJECT_NAME}_PRJ_DIR ${PROJECT_SOURCE_DIR})

set(CMAKE_MODULE_PATH ${${PROJECT_NAME}_PRJ_DIR}/cmake)
include(util)

set(custom_common_compiler_flags
  -Os
  -Wall
  -Wextra
  # -Winvalid-pch
  -D_POSIX_C_SOURCE=200809L
  -ffunction-sections
  -fdata-sections
  -fPIC
  )
set(custom_common_compiler_flags
  ${custom_common_compiler_flags}
  # for debug
  # -w
  -Wno-unused
  -Wno-sign-compare
  -Wformat=0
  -Wno-cast-function-type
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
  -Wl,--export-dynamic
  )
set_custom_flags("c" "linker" custom_c_compiler_flags)
set_custom_flags("cxx" "linker" custom_cxx_compiler_flags)

add_subdirectory(gutil)
add_subdirectory(gsync)
add_subdirectory(gstor)
add_subdirectory(gcons)
add_subdirectory(gtype)
add_subdirectory(demos)

add_library(${PROJECT_NAME} SHARED
	$<TARGET_OBJECTS:fgobject::gutil>
	$<TARGET_OBJECTS:fgobject::gsync>
  $<TARGET_OBJECTS:fgobject::gstor>
	$<TARGET_OBJECTS:fgobject::gcons>
	$<TARGET_OBJECTS:fgobject::gtype>
)
add_library(fgobject::fgobject ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
  PRIVATE ${${PROJECT_NAME}_PRJ_DIR}
  # TODO install to another dir instead
  PUBLIC ${${PROJECT_NAME}_PRJ_DIR}/gtype
  PUBLIC ${${PROJECT_NAME}_PRJ_DIR}/gcons
  PUBLIC ${${PROJECT_NAME}_PRJ_DIR}/gstor
  PUBLIC ${${PROJECT_NAME}_PRJ_DIR}/gutil
)

# target_compile_definitions(${PROJECT_NAME}

# )

target_link_libraries(${PROJECT_NAME}
	# PRIVATE fgobject::gutil
	# PRIVATE fgobject::gsync
	# PRIVATE fgobject::gstor
	PRIVATE fgobject::gtype # only need gtype, other will be auto link
)

