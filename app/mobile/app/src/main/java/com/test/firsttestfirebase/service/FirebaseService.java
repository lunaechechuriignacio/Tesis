package com.test.firsttestfirebase.service;

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

    public Object getPirSensorPropertyValue(String property) {
        return this.firebaseRepository.getPirSensorPropertyData(property).getValue();
    }

    public void setPirSensorPropertyValue(String property, Object value) {
        this.firebaseRepository.setPirSensorPropertyData(property, value);
    }

    public Object getRelayPropertyValue(Integer relayNumber, String property) {
        return this.firebaseRepository.getRelayPropertyData(relayNumber, property).getValue();
    }

    public void setRelayPropertyValue(Integer relayNumber, String property, Object value) {
        this.firebaseRepository.setRelayPropertyData(relayNumber, property, value);
    }

    public List<Component> getComponentList() {
        return ComponentMapper.toComponentList(this.firebaseRepository.getAllData());
    }
}