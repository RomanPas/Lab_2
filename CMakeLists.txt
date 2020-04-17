cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
	project(ip VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
	project(ip VERSION 0.0.1)
endif()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(ip_cli main.cpp)
add_library(ip_lib ip_lib.cpp)
add_executable(test_ip test_ip.cpp)

set_target_properties(ip_cli ip_lib test_ip PROPERTIES
	CXX_STANDART 14
	CXX_STANDART_REQUIRED ON
)

target_link_libraries(ip_cli PRIVATE ip_lib)
target_link_libraries(test_ip PRIVATE GTest::gtest GTest::gtest_main GTest::gmock GTest::gmock_main ip_lib)

if(MSVC)
	target_compile_options(ip_cli PRIVATE
		/W4
	)
	target_compile_options(ip_lib PRIVATE
		/W4
	)
		target_compile_options(test_ip PRIVATE
		/W4
	)
else()
	target_compile_options(ip_cli PRIVATE
		-Wall -Wextra -pedantic -Werror
	)
	target_compile_options(ip_lib PRIVATE
		-Wall -Wextra -pedantic -Werror
	)
		target_compile_options(test_ip PRIVATE
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

add_test(test_ip test_ip)
