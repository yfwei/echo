project(echo)

add_compile_options(-std=c99 -Wall -Werror)

include_directories(${PROJECT_SOURCE_DIR}/../include)

set(sources 
    PingClient.c
    TimeService.c
    Socket.c
    Hal.c
    StateMachine.c
    Gpio.c
    LedDriver.c
    AdcDriver.c
    Button.c
    BatteryMonitor.c)

add_library(${APP_LIB_NAME} ${sources})    
set_property(TARGET ${APP_LIB_NAME} PROPERTY C_STANDARD 99)

add_executable(${APP_NAME} main.c)
target_link_libraries(${APP_NAME} ${APP_LIB_NAME})
set_property(TARGET ${APP_NAME} PROPERTY C_STANDARD 99)

# Only for testing
add_executable(echo_server server.c)
set_property(TARGET echo_server PROPERTY C_STANDARD 99)
