find_package(list REQUIRED)

add_library(observer src/observer.c)
target_include_directories(observer PUBLIC include)
target_include_directories(observer PRIVATE src)

add_library(source src/source.c)
target_include_directories(source PUBLIC include)
target_include_directories(source PRIVATE src)
target_link_libraries(source list)

add_library(timer src/timer.c)
target_include_directories(timer PUBLIC include)
target_include_directories(timer PRIVATE src)

if(${REPLACE_MALLOC})
    target_compile_options(observer PRIVATE -include  /usr/local/include/CppUTest/MemoryLeakDetectorMallocMacros.h)
    target_link_libraries(observer CppUTest CppUTestExt)
    target_compile_options(source PRIVATE -include  /usr/local/include/CppUTest/MemoryLeakDetectorMallocMacros.h)
    target_link_libraries(source CppUTest CppUTestExt)
    target_compile_options(timer PRIVATE -include  /usr/local/include/CppUTest/MemoryLeakDetectorMallocMacros.h)
    target_link_libraries(timer CppUTest CppUTestExt)
endif()

install(TARGETS observer DESTINATION ${CMAKE_SOURCE_DIR}/lib/timer)
install(FILES include/timer/observer.h DESTINATION ${CMAKE_SOURCE_DIR}/include/timer)
