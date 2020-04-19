cmake_minimum_required(VERSION 3.2)

project(test_ip)

find_package(GTest REQUIRED)
find_package(Threads)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${LIB_DIR})

add_executable(test_tools test_tools.cpp)
add_executable(test_ipv4 test_ipv4.cpp)
add_executable(test_database test_database.cpp)

set_target_properties(test_tools test_ipv4 test_database PROPERTIES
	CXX_STANDART 14
	CXX_STANDART_REQUIRED ON
)

target_link_libraries(test_tools PRIVATE tools ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(test_ipv4 PRIVATE ipv4 ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(test_database PRIVATE ipv4 tools database ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

if(MSVC)
	target_compile_options(test_tools PRIVATE
		/W4
	)
	target_compile_options(test_ipv4 PRIVATE
		/W4
	)
	target_compile_options(test_database PRIVATE
		/W4
	)
else()
	target_compile_options(test_tools PRIVATE
		-Wall -Wextra -pedantic -Werror
	)
	target_compile_options(test_ipv4 PRIVATE
		-Wall -Wextra -pedantic -Werror
	)
	target_compile_options(test_database PRIVATE
		-Wall -Wextra -pedantic -Werror
	)
endif()

enable_testing()

add_test(test_tools test_tools)
add_test(test_ipv4 test_ipv4)
add_test(test_database test_database)