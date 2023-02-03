# NRC7292 HaLow Playground Project

This is a playground project for the [NRC7292](https://newracom.com/products/nrc7292) chip by NEWRACOM,  
and the [TD-XPAH](https://teledatics.io/products/td-xpah-802-11ah-wi-fi-development-kit) development board.  

The root project folder is the `standalone` package located in the official SDK.  
Additionally we include some scripts that make life easier:

* `firmware-tool.sh` (to run firmware update tool)
* `picocom-console.sh` (to run picocom with correct settings on `/dev/ttyUSB3`)

## Selecting and Building Applications

### Selecting application to build
To select application in `sdk/apps/` and run `make` from the project root:

```
make select target=nrc7292.sdk.release APP_NAME=hello_world
```

### Building selected application
To build the application simply run `make` the result binaries will be in `out/nrc7292/standalone_xip/`