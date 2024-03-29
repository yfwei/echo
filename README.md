# Echo

An embedded C application sends counter to a remote server and expects the server to return the same counter value. It is designed and implemented with the following peripherals in mind:
* A white LED controlled by GPIO to indicate the application is communicating with a remote server
* A red LED controlled by GPIO to indicate the low battery
* A button used to start the communication
* A battery monitor to read battery voltage

[//]: # (Image References)

[image1]: ./images/class_diagram.png "Class Diagram"
[image2]: ./images/state_machine.png "State Machine"


# System Requirements

1. When the user presses the button, turn on the white LED and start sending 2-Byte counter to the remote server every second and the counter value starts with 0.
2. The remote server is expected to return the same counter value. If the returned value is not the same or could not be read in 500 milliseconds, the application must keep sending the same counter value. The counter increments only if the server sends the same counter value back.
3. When the user releases the button, stop the communication, reset the counter and turn off the white LED.
4. If the battery voltage drops to 3.5V, blink the red LED at a frequency of 2Hz with a 25% duty cycle, turn off the write LED, cease any communication and reset the counter.
5. if the battery voltage rises back to 3.5, turn off the red LED and start responding to the button.

# Design

By following Test-Driven Development (TDD), I can test the application without the target hardware and the target OS. As you can see in the following figure, I introduced several interfaces as Operating System Abstraction Layer (OSAL) and Hardware Abstraction Layer (HAL):

![alt text][image1]

#### The HAL interfaces
* GPIO
* AdcDriver

#### The OSAL interfaces
* TimeService
* Socket

### Communication
The communication with the remote server is implemented in the [PingClient](src/PingClient.c) module. It uses the [Socket](include/Socket.h) interface to create/write/read a platform-independent datagram (UDP) socket. Although only the Linux platform is supported at the moment, it should not be hard to support other platforms.

### State Machine
The core logic was implemented in a state machine as depicted below:

![alt text][image2]

The [state machine](src/StateMachine.c) only knows the high-level concepts from the [Hal](src/Hal.c) moudle. It does not need to know any low-level details, such as GPIO or ADC, to do its job.

# How to Build and Run
1. Install cmake and cpputest: `sudo apt install cmake cpputest`
1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run the test server: `./bin/echo_server`
5. Open another terminal to run the client: `./bin/echo_client`

Please note that the above instructions are only verified on my Ubuntu 18.04 machine.
