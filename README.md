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
## Inherited APIs
The bGPSSensor is a [bSensor](https://github.com/diy365-mgos/bsensor) instance, so it inherits APIs from:
- [bThing](https://github.com/diy365-mgos/bthing)
- [bSensor](https://github.com/diy365-mgos/bsensor)
### Remarks on: mgos_bthing_get_state()
The [mgos_bthing_get_state()](https://github.com/diy365-mgos/bthing#mgos_bthing_get_state) returns a [bVariantDictionary](https://github.com/diy365-mgos/bvar-dic) having following keys:
|Key|Type||
|--|--|--|
|accuracy|decimal|The accuracy of the estimated location, in meters. This represents the radius of a circle around the given location.|
|location|[bVariantDictionary](https://github.com/diy365-mgos/bvar-dic)|A [GPS location dictionary](#gps_location_dictionary).|
#### GPS location dictionary
|Key|Type||
|--|--|--|
|lat|decimal|The latitude value, in degrees (e.g.: 37.421875199999995).|
|lng|decimal|The longitude value, in degrees (e.g.: -122.0851173).|
## C/C++ APIs Reference
### mgos_bgpssens_get
```c
mgos_bsensor_t mgos_bgpssens_get();
```
Gets the GPS sensor instance. Returns `NULL` if error.
## To Do
- Implement javascript APIs for [Mongoose OS MJS](https://github.com/mongoose-os-libs/mjs).