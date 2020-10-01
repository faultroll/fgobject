
project(shape)

set(${PROJECT_NAME}_PRJ_DIR ${PROJECT_SOURCE_DIR})

set(${PROJECT_NAME}_SRC
	shape.c
	circle.c
	rectangle.c
	drawable.c
	main.c
)

set(${PROJECT_NAME}_SRC
	${${PROJECT_NAME}_SRC}
)

add_executable(${PROJECT_NAME}
	${${PROJECT_NAME}_SRC}
)

target_include_directories(${PROJECT_NAME}
	PUBLIC ${${PROJECT_NAME}_PRJ_DIR}
)

target_compile_definitions(${PROJECT_NAME}
	PRIVATE DEMO_IFACE
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE fgobject
)
