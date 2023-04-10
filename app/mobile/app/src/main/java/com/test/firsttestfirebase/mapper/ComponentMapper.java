package com.test.firsttestfirebase.mapper;

import com.google.firebase.database.DataSnapshot;
import com.test.firsttestfirebase.model.Component;
import com.test.firsttestfirebase.model.PirSensor;
import com.test.firsttestfirebase.model.Relay;
import com.test.firsttestfirebase.model.RelayStatus;
import java.util.ArrayList;
import java.util.List;

public class ComponentMapper {
    private static final String PIR_SENSOR_ACCESS_PARTIAL_KEY = "PIR_SENSOR";
    private static final String RELAY_ACCESS_PARTIAL_KEY = "RELAY";

    private static final String PIR_SENSOR_PATH = "pir_sensor";
    private static final String RELAY_PATH = "relays";
    private static final String RELAY_PARTIAL_ALIAS = "relay_";
    private static final Integer RELAYS_COUNT = 8;

    public static List<Component> toComponentList(DataSnapshot dataSnapshot) {
        List<Component> componentList = new ArrayList<>();

        PirSensor pirSensor = toPirSensor(dataSnapshot.child(PIR_SENSOR_PATH));
        componentList.add(pirSensor);

        for (int i = 0; i < RELAYS_COUNT; i++) {
            componentList.add(
                    toRelay(
                            i+1,
                            dataSnapshot.child(RELAY_PATH).child(RELAY_PARTIAL_ALIAS + (i+1))
                    )
            );
        }

        return componentList;
    }

    private static PirSensor toPirSensor(DataSnapshot dataSnapshot) {
        Integer timeSeconds = dataSnapshot.child("time_seconds").getValue(Integer.class);

        return new PirSensor(timeSeconds);
    }

    private static Relay toRelay(Integer number, DataSnapshot dataSnapshot) {
        Boolean isAutomatic = dataSnapshot.child("automatic").getValue(Boolean.class);
        RelayStatus relayStatus = toRelayStatus(dataSnapshot.child("status").getValue(Integer.class));

        return new Relay(number, isAutomatic, relayStatus);
    }

    private static RelayStatus toRelayStatus(Integer value) {
        return (value == 1 ? RelayStatus.ON : RelayStatus.OFF);
    }
}
