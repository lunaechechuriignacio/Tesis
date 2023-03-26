package com.test.firsttestfirebase.repository;

import androidx.annotation.NonNull;
import com.google.android.gms.tasks.Task;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

public class FirebaseRepository {
    private static FirebaseRepository instance;
    private final FirebaseDatabase database;

    private static final String PIR_SENSOR_PATH = "pir_sensor";
    private static final String RELAY_PATH = "relays";
    private static final String RELAY_PARTIAL_ALIAS = "relay_";

    private FirebaseRepository() {
        this.database = FirebaseDatabase.getInstance();
    }

    public static FirebaseRepository getInstance() {
        if (instance == null) instance = new FirebaseRepository();
        return instance;
    }

    public DatabaseReference getPirSensorPropertyReference(String property) {
        return this.database.getReference(PIR_SENSOR_PATH)
                .child(property);
    }

    public DataSnapshot getPirSensorPropertyData(String property) {
        Task<DataSnapshot> dataSnapshotTask = this.database.getReference(PIR_SENSOR_PATH)
                .child(property)
                .get();
        this.await(dataSnapshotTask);

        return dataSnapshotTask.getResult();
    }

    public void setPirSensorPropertyData(String property, Object value) {
        this.database.getReference(PIR_SENSOR_PATH)
                .child(property)
                .setValue(value);
    }

    public DatabaseReference getRelayPropertyReference(Integer relayNumber, String property) {
        return this.database.getReference(RELAY_PATH)
                .child(RELAY_PARTIAL_ALIAS + relayNumber)
                .child(property);
    }

    public DataSnapshot getRelayPropertyData(Integer relayNumber, String property) {
        Task<DataSnapshot> dataSnapshotTask = this.database.getReference(RELAY_PATH)
                .child(RELAY_PARTIAL_ALIAS + relayNumber)
                .child(property)
                .get();
        this.await(dataSnapshotTask);

        return dataSnapshotTask.getResult();
    }

    public void setRelayPropertyData(Integer relayNumber, String property, Object value) {
        this.database.getReference(RELAY_PATH)
                .child(RELAY_PARTIAL_ALIAS + relayNumber)
                .child(property)
                .setValue(value);
    }

    public DataSnapshot getAllData() {
        Task<DataSnapshot> dataSnapshotTask = this.database.getReference().get();
        this.await(dataSnapshotTask);

        return dataSnapshotTask.getResult();
    }

    private void await(@NonNull Task<DataSnapshot> dataSnapshotTask) {
        while(!dataSnapshotTask.isComplete()) {}
    }
}
