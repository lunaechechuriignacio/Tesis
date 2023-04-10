package com.test.firsttestfirebase.mapper;

import com.test.firsttestfirebase.model.RelayStatus;

public class DataMapper {
    public static Boolean toBoolean(RelayStatus relayStatus) {
        return relayStatus == RelayStatus.ON;
    }

    public static Boolean toBoolean(Integer value) {
        return (value == 1 ? Boolean.TRUE : Boolean.FALSE);
    }

    public static Integer toInteger(Boolean on) {
        return (on ? 1 : 0);
    }

    public static String toCleanComponentAlias(String alias) {
        return alias.replace("_", " ").toUpperCase();
    }
}
