#include "mgos.h"
#include "mgos_bgpssens.h"
#include "mgos_bgps.h"
#include "mgos_bvar.h"
#include "mgos_bvar_dic.h"

#ifdef MGOS_HAVE_MJS
#include "mjs.h"
#endif /* MGOS_HAVE_MJS */

static mgos_bsensor_t s_sensor = NULL;

#ifdef MGOS_HAVE_MJS

#endif /* MGOS_HAVE_MJS */

static void mg_gps_position_changed(int ev, void *ev_data, void *userdata) {
  struct mgos_bgps_position_changed *data = (struct mgos_bgps_position_changed *)ev_data;

  struct mgos_bthing_updatable_state state;
  if (mgos_bthing_start_update_state(MGOS_BSENSOR_THINGCAST(s_sensor), &state)) {
    // update accuracy
    mgos_bvar_set_key_decimal(state.value, "accuracy", data->cur_pos.accuracy);
    // update latitude and longitude
    mgos_bvar_t location_key = NULL;
    // if (!mgos_bvar_try_get_key(state.value, "location", &location_key)) {
    //   location_key = mgos_bvar_new_dic();
    //   if (!mgos_bvar_add_key(state.value, "location", location_key)){
    //     mgos_bvar_free(location_key);
    //     location_key = NULL;
    //     LOG(LL_ERROR, ("Error adding the 'location' value to the state."));
    //   }
    // }

    if (location_key != NULL) {
      mgos_bvar_set_key_decimal(location_key, "lat", data->cur_pos.location.latitude);
      mgos_bvar_set_key_decimal(location_key, "lng", data->cur_pos.location.longitude);
    }

    LOG(LL_INFO, ("accuracy: %f",  mgos_bvar_get_decimal(mgos_bvar_get_key(state.value, "accuracy"))));

    location_key = NULL;
    if (mgos_bvar_try_get_key(state.value, "location", &location_key)) {
      LOG(LL_INFO, ("lat: %f",  mgos_bvar_get_decimal(mgos_bvar_get_key(location_key, "lat"))));
      LOG(LL_INFO, ("lng: %f",  mgos_bvar_get_decimal(mgos_bvar_get_key(location_key, "lng"))));
    }

    mgos_bthing_end_update_state(state);
  }

  (void) ev;
  (void) userdata;
}

mgos_bsensor_t mgos_bgpssens_get() {
  return s_sensor;
}

bool mgos_bgpssens_init() {
  if (mgos_sys_config_get_bgpssens_sensor_id() != NULL) {
    // create the bGPS sensor
    s_sensor = mgos_bsensor_create(mgos_sys_config_get_bgpssens_sensor_id(),
      mgos_sys_config_get_bgpssens_sensor_dom());
    
    if (s_sensor) {
      // bSensor successfully created
      mgos_event_add_handler(MGOS_EV_BGPS_POSITION_CHANGED, mg_gps_position_changed, NULL);
      LOG(LL_INFO, ("bGPS sensor '%s' successfully created", mgos_sys_config_get_bgpssens_sensor_id()));
      return true;
    }

    LOG(LL_ERROR, ("Error creating bGPS sensor '%s'", mgos_sys_config_get_bgpssens_sensor_id()));
  } else {
    LOG(LL_ERROR, ("Invalid empty ID. Unable to create the bGPS sensor."));
  }

  return false;
}