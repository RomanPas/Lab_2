cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
	project(ip VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
	project(ip VERSION 0.0.1)
endif()

set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(TESTS_DIR ${CMAKE_SOURCE_DIR}/tests)

add_subdirectory(${LIB_DIR})
add_subdirectory(${TESTS_DIR})

#include_directories(${LIB_DIR})

add_executable(ip_cli main.cpp)

set_target_properties(ip_cli PROPERTIES
	CXX_STANDART 14
	CXX_STANDART_REQUIRED ON
)

target_include_directories(ip_cli PRIVATE ${LIB_DIR})

target_link_libraries(ip_cli PRIVATE tools ipv4 database)

if(MSVC)
	target_compile_options(ip_cli PRIVATE
		/W4
	)
else()
	target_compile_options(ip_cli PRIVATE
		-Wall -Wextra -pedantic -Werror
	)
endif()

install(TARGETS ip_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()