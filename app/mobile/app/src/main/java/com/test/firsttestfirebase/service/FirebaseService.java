package com.test.firsttestfirebase.service;

import com.google.firebase.database.DatabaseReference;
import com.test.firsttestfirebase.mapper.ComponentMapper;
import com.test.firsttestfirebase.model.Component;
import com.test.firsttestfirebase.repository.FirebaseRepository;
import java.util.List;

public class FirebaseService {
    private static FirebaseService instance;
    private final FirebaseRepository firebaseRepository;

    private FirebaseService() {
        this.firebaseRepository = FirebaseRepository.getInstance();
    }

    public static FirebaseService getInstance() {
        if (instance == null) instance = new FirebaseService();
        return instance;
    }

    public DatabaseReference getPirSensorPropertyReference(String property) {
        return this.firebaseRepository.getPirSensorPropertyReference(property);
    }

    public void setPirSensorPropertyValue(String property, Object value) {
        this.firebaseRepository.setPirSensorPropertyData(property, value);
    }

    public DatabaseReference getRelayPropertyReference(Integer relayNumber, String property) {
        return this.firebaseRepository.getRelayPropertyReference(relayNumber, property);
    }

    public void setRelayPropertyValue(Integer relayNumber, String property, Object value) {
        this.firebaseRepository.setRelayPropertyData(relayNumber, property, value);
    }

    public List<Component> getComponentList() {
        return ComponentMapper.toComponentList(this.firebaseRepository.getAllData());
    }
}