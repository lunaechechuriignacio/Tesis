package com.test.firsttestfirebase.service;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.test.firsttestfirebase.model.Component;
import com.test.firsttestfirebase.model.ComponentStatus;
import com.test.firsttestfirebase.model.PirSensor;
import com.test.firsttestfirebase.model.Relay;
import java.util.ArrayList;
import java.util.List;

public class FirebaseService {
    private static FirebaseService instance;
    private final FirebaseDatabase database;

    private static final String PIR_SENSOR_ACCESS_PARTIAL_KEY = "PIR_SENSOR";
    private static final String RELAY_ACCESS_PARTIAL_KEY = "RELAY";

    private static final String PIR_SENSOR_PATH = "pir_sensor";
    private static final String RELAY_PATH = "relays";
    private static final String RELAY_PARTIAL_ALIAS = "relay_";

    private FirebaseService() {
        this.database = FirebaseDatabase.getInstance();
    }

    public static FirebaseService getInstance() {
        if (instance == null) instance = new FirebaseService();
        return instance;
    }

    public Object getPirSensorPropertyValue(String property) {
        // TODO: es asincronico. Se sigue investigando...
        return "";
    }

    public void setPirSensorPropertyValue(String property, Object value) {
        this.database.getReference(PIR_SENSOR_PATH)
                .child(property)
                .setValue(value);
    }

    public Object getRelayPropertyValue(Integer relayNumber, String property) {
        // TODO: es asincronico. Se sigue investigando...
        return "";
    }

    public void setRelayPropertyValue(Integer relayNumber, String property, Object value) {
        this.database.getReference(RELAY_PATH)
                .child(RELAY_PARTIAL_ALIAS + relayNumber)
                .child(property)
                .setValue(value);
    }

    /*
    public List<Component> testGetData() {
        List<Component> componentList = new ArrayList<>();

        database.getReference("pir_sensor").get().addOnSuccessListener(result -> {
            PirSensor pirSensor = new PirSensor();
            pirSensor.setAutomatic(result.child("automatic").getValue(Integer.class) == 1);
            pirSensor.setTimeSeconds(result.child("time_seconds").getValue(Integer.class));

            componentList.add(pirSensor);
        });

        database.getReference("relays").child("relay_1").get().addOnSuccessListener(result -> {
            Relay relay1 = new Relay(1);
            relay1.setComponentStatus(result.child("status").getValue(Integer.class) == 1 ? ComponentStatus.ON : ComponentStatus.OFF);

            componentList.add(relay1);
        });

        return componentList;
    }
    */

    /*
    public void getDataRelays() {
        Relay relay=new Relay();
        for (int indice = 1; indice <= 8; indice++) {
            String path = "relay_" + String.valueOf(indice);
            int finalIndice = indice;
            reference.child(path).addValueEventListener(new ValueEventListener() {
                @Override
                public void onDataChange(@NonNull DataSnapshot snapshot) {
                    relay.setAutomatic(Boolean.TRUE.equals(snapshot.child("automatic").getValue(boolean.class)));
                    relay.setRelayNumber(finalIndice);
                  //  relay.setStatus(snapshot.child("status").getValue(Integer.class));
                    relay.setStartTime(snapshot.child("start_time").getValue(String.class));
                    relay.setEndTime(snapshot.child("end_time").getValue(String.class));
                    relays.add(finalIndice, relay);
                }

                @Override
                public void onCancelled(@NonNull DatabaseError error) {
                    //  Toast.makeText(MainActivity.this, "Fail to get data.", Toast.LENGTH_SHORT).show();
                }
            });
        }
    }
    */
}