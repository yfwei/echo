# Echo

An embedded C application sends counter to a remote server and expects the server to return the same counter value. It is designed and implemented with the following peripherals in mind:
* A white LED controlled by GPIO to indicate the application is communicating with a remote server
* A red LED controlled by GPIO to indicate the low battery
* A button used to start the communication
* A battery monitor to read battery voltage

