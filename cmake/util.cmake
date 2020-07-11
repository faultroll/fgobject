cmake_minimum_required(VERSION 3.5)

# functions & macros

# apply custom flags
## usage
## set(custom_c_compiler_flags "-Os -Wall -Wextra -Winvalid-pch -D_POSIX_C_SOURCE=200809L -std=c11 -Wpedantic")
## set_custom_flags("c" "compiler" custom_c_compiler_flags)
## message("${CMAKE_C_FLAGS}")
include(CheckCCompilerFlag)
include(CheckCXXCompilerFlag)
function(set_custom_flags lang module flags)
  set(flaglist "")
  string(TOUPPER ${lang} lang)
  string(TOUPPER ${module} module)
  foreach(flag_raw ${${flags}})
    # remove problematic characters
	string(REGEX REPLACE "[^a-zA-Z0-9]" "" flag_cooked ${flag_raw})
	# CHECK_${lang}_${module}_FLAG(${flag_raw} "FLAG_SUPPORTED_${flag_cooked}")
	if("${module}" STREQUAL "COMPILER")
	  if("${lang}" STREQUAL "C")
	    CHECK_C_COMPILER_FLAG(${flag_raw} "FLAG_SUPPORTED_${flag_cooked}")
	  elseif("${lang}" STREQUAL "CXX")
	    CHECK_CXX_COMPILER_FLAG(${flag_raw} "FLAG_SUPPORTED_${flag_cooked}")
	  endif()
	elseif("${module}" STREQUAL "LINKER")
	  set(FLAG_SUPPORTED_${flag_cooked} TRUE)
	endif()
	if(FLAG_SUPPORTED_${flag_cooked})
	  # list(APPEND flaglist ${flag_raw})
	  set(flaglist "${flaglist} ${flag_raw}")
	endif()
  endforeach()
  # set(CMAKE_${lang}_${module}_FLAGS "${flaglist}" PARENT_SCOPE)
  if("${module}" STREQUAL "COMPILER")
	set(CMAKE_${lang}_FLAGS "${flaglist}" PARENT_SCOPE)
  elseif("${module}" STREQUAL "LINKER")
	set(CMAKE_EXE_${module}_FLAGS "${flaglist}" PARENT_SCOPE)
	# set(CMAKE_MODULE_${module}_FLAGS "${flaglist}" PARENT_SCOPE)
	# set(CMAKE_STATIC_${module}_FLAGS "${flaglist}" PARENT_SCOPE)
	set(CMAKE_SHARED_${module}_FLAGS "${flaglist}" PARENT_SCOPE)
  endif()
endfunction()

# prepend list
## usage
## set(${PROJECT_NAME}_SRC a.c b.c c.c)
## list_transform_prepend(${PROJECT_NAME}_SRC ${PROJECT_NAME}_PRJ_DIR)
## message("${${PROJECT_NAME}_SRC}")
function(list_transform_prepend src prefix)
  set(srclist "")
  foreach(source ${${src}})
    list(APPEND srclist "${prefix}/${source}")
  endforeach()
  set(${src} "{srclist}" PARENT_SCOPE)
endfunction()


