if(DEFINED ENV{CPPUTEST_HOME})
    message(STATUS "Using CppUTest home: $ENV{CPPUTEST_HOME}")
    set(CPPUTEST_INCLUDE_DIRS $ENV{CPPUTEST_HOME}/include)
    set(CPPUTEST_LIBRARIES $ENV{CPPUTEST_HOME}/lib)
    set(CPPUTEST_LDFLAGS CppUTest CppUTestExt)
else()
    find_package(PkgConfig REQUIRED)
    pkg_search_module(CPPUTEST REQUIRED cpputest>=3.8)
    message(STATUS "Found CppUTest version ${CPPUTEST_VERSION}")
endif()

include_directories(${CPPUTEST_INCLUDE_DIRS} ../include/)
link_directories(${CPPUTEST_LIBRARIES})

# The test cases run off the target
set(TEST_APP_NAME ${APP_NAME}_tests)
set(TEST_SOURCES
    StateMachineTest.cpp
    PingClientTest.cpp
    HalTest.cpp
    BatteryMonitorTest.cpp
    LedDriverTest.cpp
    ButtonTest.cpp
    GpioSpyTest.cpp
    GpioSpy.c
    FakeAdcDriver.c
    FakeSocket.c
    FakeTimeService.c
    main.cpp
)
add_executable(${TEST_APP_NAME} ${TEST_SOURCES})
target_link_libraries(${TEST_APP_NAME} ${APP_LIB_NAME} ${CPPUTEST_LDFLAGS})

#The test cases run on the target
set(TEST_PLATFORM_NAME ${APP_NAME}_platform_tests)
set(TEST_PLATFORM_SOURCES
    TimeServiceTest.cpp
    SocketTest.cpp
    GpioTest.cpp
    AdcDriverTest.cpp
    main.cpp
)
add_executable(${TEST_PLATFORM_NAME} ${TEST_PLATFORM_SOURCES})
target_link_libraries(${TEST_PLATFORM_NAME} ${APP_LIB_NAME} ${CPPUTEST_LDFLAGS})

# Run the tests after building
add_custom_command(TARGET ${TEST_APP_NAME} COMMAND ../bin/${TEST_APP_NAME} POST_BUILD)
add_custom_command(TARGET ${TEST_PLATFORM_NAME} COMMAND ../bin/${TEST_PLATFORM_NAME} POST_BUILD)
