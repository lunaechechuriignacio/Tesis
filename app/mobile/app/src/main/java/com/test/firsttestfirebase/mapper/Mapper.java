package com.test.firsttestfirebase.mapper;

import com.google.firebase.database.DataSnapshot;
import com.test.firsttestfirebase.model.Component;
import com.test.firsttestfirebase.model.PirSensor;
import com.test.firsttestfirebase.model.Relay;
import com.test.firsttestfirebase.model.RelayStatus;
import java.util.ArrayList;
import java.util.List;

public class Mapper {
    private static final String PIR_SENSOR_ACCESS_PARTIAL_KEY = "PIR_SENSOR";
    private static final String RELAY_ACCESS_PARTIAL_KEY = "RELAY";

    private static final String PIR_SENSOR_PATH = "pir_sensor";
    private static final String RELAY_PATH = "relays";
    private static final String RELAY_PARTIAL_ALIAS = "relay_";

    public static List<Component> toComponentList(DataSnapshot dataSnapshot) {
        List<Component> componentList = new ArrayList<>();

        PirSensor pirSensor = toPirSensor(dataSnapshot.child(PIR_SENSOR_PATH));
        componentList.add(pirSensor);

        for (int i = 0; i < 8; i++) {
            componentList.add(
                    toRelay(
                            i+1,
                            dataSnapshot.child(RELAY_PATH).child(RELAY_PARTIAL_ALIAS + (i+1))
                    )
            );
        }

        return componentList;
    }

    public static Boolean toBoolean(RelayStatus relayStatus) {
        return relayStatus == RelayStatus.ON;
    }

    private static PirSensor toPirSensor(DataSnapshot dataSnapshot) {
        Boolean isAutomatic = dataSnapshot.child("automatic").getValue(Integer.class) == 1;
        Integer timeSeconds = dataSnapshot.child("time_seconds").getValue(Integer.class);

        return new PirSensor(isAutomatic, timeSeconds);
    }

    private static Relay toRelay(Integer number, DataSnapshot dataSnapshot) {
        Boolean isAutomatic = dataSnapshot.child("automatic").getValue(Boolean.class);
        RelayStatus relayStatus = toRelayStatus(dataSnapshot.child("status").getValue(Integer.class));

        return new Relay(number, isAutomatic, relayStatus);
    }

    private static RelayStatus toRelayStatus(Integer value) {
        if (value == 1) return RelayStatus.ON;
        return RelayStatus.OFF;
    }
}
