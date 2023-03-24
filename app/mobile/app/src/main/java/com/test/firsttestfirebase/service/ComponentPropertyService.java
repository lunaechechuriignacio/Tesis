package com.test.firsttestfirebase.service;

import java.util.HashMap;
import java.util.Map;

public class ComponentPropertyService {
    private static final Map<String, Class> propertyMap = new HashMap<String, Class>() {
        {
            put("PIR_SENSOR_AUTOMATIC", Integer.class);
            put("PIR_SENSOR_TIME_SECONDS", Integer.class);
            put("RELAY_AUTOMATIC", Integer.class); // TODO: en la base de datos aparece como Boolean, ¿Dejamos Boolean o Integer como el automatic del sensor pir?
            put("RELAY_END_TIME", String.class);
            put("RELAY_START_TIME", String.class);
            put("RELAY_STATUS", Integer.class);
        }
    };

    public static Class getClassByProperty(String property) {
        return propertyMap.get(property);
    }
}
