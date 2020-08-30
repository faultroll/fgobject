
project(gstor)

set(${PROJECT_NAME}_PRJ_DIR ${PROJECT_SOURCE_DIR})

set(${PROJECT_NAME}_SRC
	gmem.c
	gslice.c
	gstrfuncs.c
)

set(${PROJECT_NAME}_SRC
	${${PROJECT_NAME}_SRC}
	ghash.c
	gquark.c
)

set(${PROJECT_NAME}_SRC
	${${PROJECT_NAME}_SRC}
	gslist.c
	gatomicarray.c
)

set(${PROJECT_NAME}_SRC
	gonce.c
)

add_library(${PROJECT_NAME} OBJECT
	${${PROJECT_NAME}_SRC}
)
add_library(fgobject::gstor ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
	PUBLIC ${${PROJECT_NAME}_PRJ_DIR}
)

# target_compile_definitions(${PROJECT_NAME}

# )

target_link_libraries(${PROJECT_NAME}
	PUBLIC fgobject::gutil
	PUBLIC fgobject::gsync
)

