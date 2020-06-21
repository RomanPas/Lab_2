cmake_minimum_required(VERSION 3.2)

project(lib_ip)

add_library(ipv4 ipv4.cpp)
add_library(database database.cpp)
add_library(tools tools.cpp)

set_target_properties(ipv4 database tools PROPERTIES
	CXX_STANDART 14
	CXX_STANDART_REQUIRED ON
)

target_link_libraries(database PRIVATE ipv4 tools)

if(MSVC)
	target_compile_options(ipv4 PRIVATE
		/W4
	)
		target_compile_options(database PRIVATE
		/W4
	)
		target_compile_options(tools PRIVATE
		/W4
	)
else()
	target_compile_options(ipv4 PRIVATE
		-Wall -Wextra -pedantic -Werror
	)
		target_compile_options(database PRIVATE
		-Wall -Wextra -pedantic -Werror
	)
		target_compile_options(tools PRIVATE
		-Wall -Wextra -pedantic -Werror
	)
endif()