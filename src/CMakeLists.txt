add_library(timer_observer src/timer_observer.c)
target_include_directories(timer_observer PUBLIC include)
target_include_directories(timer_observer PRIVATE src)

add_library(timer_source src/timer_source.c)
target_include_directories(timer_source PUBLIC include)
target_include_directories(timer_source PRIVATE src)
target_include_directories(timer_source PRIVATE ${CMAKE_BINARY_DIR}/list-install/include)
target_link_libraries(timer_source ${CMAKE_BINARY_DIR}/list-install/lib/list.a)

if(${REPLACE_MALLOC})
    target_compile_options(timer_observer PRIVATE -include  /usr/local/include/CppUTest/MemoryLeakDetectorMallocMacros.h)
    target_link_libraries(timer_observer CppUTest CppUTestExt)
    target_compile_options(timer_source PRIVATE -include  /usr/local/include/CppUTest/MemoryLeakDetectorMallocMacros.h)
    target_link_libraries(timer_source CppUTest CppUTestExt)
endif()

install(TARGETS timer_observer DESTINATION ${CMAKE_SOURCE_DIR}/lib)
install(FILES include/timer/timer_observer.h DESTINATION ${CMAKE_SOURCE_DIR}/include/timer)
