find_package(CppUTest REQUIRED)

add_library(timer_test EXCLUDE_FROM_ALL timer_test.cpp)
target_include_directories(timer_test PRIVATE ${CMAKE_SOURCE_DIR}/src/include)
target_link_libraries(timer_test timer_source timer_observer)
target_link_libraries(timer_test CppUTest CppUTestExt)

add_executable(run_all_tests EXCLUDE_FROM_ALL run_all_tests.cpp)

target_link_libraries(run_all_tests timer_test)

add_custom_target(check DEPENDS run_all_tests)
add_custom_command(TARGET check POST_BUILD WORKING_DIRECTORY ${CMAKE_BINARY_DIR} COMMAND run_all_tests)
