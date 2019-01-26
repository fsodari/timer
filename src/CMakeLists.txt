find_package(list REQUIRED)

add_library(source src/source.c)
target_include_directories(source PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/timer>
        )
target_include_directories(source PRIVATE src)
target_link_libraries(source list)

add_library(observer src/observer.c)
target_include_directories(observer PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/timer>
        )
target_include_directories(observer PRIVATE src)

add_library(timer src/timer.c)
target_include_directories(timer PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/timer>
        )
target_include_directories(timer PRIVATE src)

if(${REPLACE_MALLOC})
    target_compile_options(observer PRIVATE -include  /usr/local/include/CppUTest/MemoryLeakDetectorMallocMacros.h)
    target_link_libraries(observer CppUTest CppUTestExt)
    target_compile_options(source PRIVATE -include  /usr/local/include/CppUTest/MemoryLeakDetectorMallocMacros.h)
    target_link_libraries(source CppUTest CppUTestExt)
    target_compile_options(timer PRIVATE -include  /usr/local/include/CppUTest/MemoryLeakDetectorMallocMacros.h)
    target_link_libraries(timer CppUTest CppUTestExt)
endif()

install(TARGETS source
        EXPORT source-targets
        PUBLIC_HEADER DESTINATION include/timer
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
install(EXPORT source-targets
        FILE source-config.cmake
        DESTINATION lib/cmake/timer)

install(TARGETS observer
        EXPORT observer-targets
        PUBLIC_HEADER DESTINATION include/timer
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
install(EXPORT observer-targets
        FILE observer-config.cmake
        DESTINATION lib/cmake/timer)

install(TARGETS timer
        EXPORT timer-targets
        PUBLIC_HEADER DESTINATION include/timer
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
install(EXPORT timer-targets
        FILE timer-config.cmake
        DESTINATION lib/cmake/timer)
