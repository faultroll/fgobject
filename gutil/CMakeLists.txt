
project(gutil)

set(${PROJECT_NAME}_PRJ_DIR ${PROJECT_SOURCE_DIR})

set(${PROJECT_NAME}_SRC
	gmessages.c
)

add_library(${PROJECT_NAME} OBJECT
	${${PROJECT_NAME}_SRC}
)
add_library(fgobject::gutil ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
	PUBLIC ${${PROJECT_NAME}_PRJ_DIR}
)

# target_compile_definitions(${PROJECT_NAME}

# )

# target_link_libraries(${PROJECT_NAME}

# )

# include(CheckIncludeFiles)
# include(CheckFunctionExists)

# check_include_files(alloca.h GLIB_HAVE_ALLOCA_H)
# check_function_exists(vsnprintf GLIB_USING_SYSTEM_PRINTF)
# option (GLIB_STATIC_COMPILATION "glib static compile" OFF)
# option (GOBJECT_STATIC_COMPILATION "gobject static compile" OFF)
# option (G_HAVE_GROWING_STACK "growing stack" OFF)
# option (G_HAVE_GNUC_VISIBILITY "gunc visibility" ON)
# option (G_ATOMIC_LOCK_FREE "atomic lock free" ON)
# set (gint16 "short")
# configure_file(glibconfig.h.in glibconfig.h @ONLY)

# check_function_exists(vsnprintf HAVE_C99_VSNPRINTF)
# configure_file(config.h.in config.h @ONLY)
