
project(gsync)

set(${PROJECT_NAME}_PRJ_DIR ${PROJECT_SOURCE_DIR})

set(${PROJECT_NAME}_SRC
	gatomic.c
	grefcount.c
)
set(${PROJECT_NAME}_SRC
	${${PROJECT_NAME}_SRC}
	gthread.c
	# TODO auto-choose
	gthread-posix.c
	# gthread-win32.c
)

add_library(${PROJECT_NAME} OBJECT
	${${PROJECT_NAME}_SRC}
)
add_library(fgobject::gsync ALIAS ${PROJECT_NAME})

message("${PROJECT_SOURCE_DIR}")
target_include_directories(${PROJECT_NAME}
	PUBLIC ${${PROJECT_NAME}_PRJ_DIR}
)

# target_compile_definitions(${PROJECT_NAME}

# )

target_link_libraries(${PROJECT_NAME}
	PUBLIC fgobject::gutil
	PUBLIC Threads::Threads
)
find_package(Threads REQUIRED)
