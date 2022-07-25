# bGPSSensor Library
## Overview
A bGPSSensor allows you to easily manage a GPS sensor based on [bGPS Library](https://github.com/diy365-mgos/bgps).
## GET STARTED
## Configuration
The library adds a `bgpssens` configuration entry which contains configuration settings.
```javascript
"bgpssens": {
  "sensor_id": "gps",     // Sensor ID
  "sensor_dom": ""        // Sensor domain
}
```
## C/C++ APIs Reference
### mgos_bgps_get_position
```c
bool mgos_bgps_get_position(struct mgos_bgps_position *position);
```
Reads the current GPS position. Returns `false` if error, or `true` otherwise.

|Parameter||
|--|--|
|position|The current [GPS position](#mgos_bgps_position).|

**Remarks**

This function is automatically invoked if the auto-update is enabled and properly [configured](#configuration).
## To Do
- Implement javascript APIs for [Mongoose OS MJS](https://github.com/mongoose-os-libs/mjs).