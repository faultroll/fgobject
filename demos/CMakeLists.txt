cmake_minimum_required(VERSION 3.5)

project(demos)

set(CMAKE_BUILD_TYPE MinSizeRel)

set(${PROJECT_NAME}_PRJ_DIR ${PROJECT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${${PROJECT_NAME}_PRJ_DIR}/../dist/include/fgobject)
LINK_DIRECTORIES(${${PROJECT_NAME}_PRJ_DIR}/../dist/lib)

set(${PROJECT_NAME}_SRC
	base.c
	derived.c
)

set(${PROJECT_NAME}_SRC
	${${PROJECT_NAME}_SRC}
	main.c
)

add_executable(${PROJECT_NAME}
	${${PROJECT_NAME}_SRC}
)

target_include_directories(${PROJECT_NAME}
	PRIVATE ${${PROJECT_NAME}_PRJ_DIR}
)

# target_compile_definitions(${PROJECT_NAME}

# )

target_link_libraries(${PROJECT_NAME}
	# PRIVATE fgobject::fgobject # TODO cannot use this
	PRIVATE fgobject
)
