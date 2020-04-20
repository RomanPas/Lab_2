cmake_minimum_required(VERSION 3.2)

project(test_ip)

find_package(GTest REQUIRED)
find_package(Threads)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${LIB_DIR})

add_executable(all_tests main_test.cpp test_tools.cpp test_ipv4.cpp test_database.cpp)

set_target_properties(all_tests PROPERTIES
	CXX_STANDART 14
	CXX_STANDART_REQUIRED ON
)

target_link_libraries(all_tests PRIVATE tools ipv4 database ${GTEST_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

if(MSVC)
	target_compile_options(all_tests PRIVATE
		/W4
	)
else()
	target_compile_options(all_tests PRIVATE
		-Wall -Wextra -pedantic -Werror
	)
endif()

enable_testing()

add_test(all_tests all_tests)