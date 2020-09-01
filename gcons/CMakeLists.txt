
project(gcons)

set(${PROJECT_NAME}_PRJ_DIR ${PROJECT_SOURCE_DIR})

set(${PROJECT_NAME}_SRC
	gonce.c
)

set(${PROJECT_NAME}_SRC
	${${PROJECT_NAME}_SRC}
)

add_library(${PROJECT_NAME} OBJECT
	${${PROJECT_NAME}_SRC}
)
add_library(fgobject::gcons ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
	PUBLIC ${${PROJECT_NAME}_PRJ_DIR}
)

# target_compile_definitions(${PROJECT_NAME}

# )

target_link_libraries(${PROJECT_NAME}
	PUBLIC fgobject::gutil
	PUBLIC fgobject::gsync
	PUBLIC fgobject::gstor
)
