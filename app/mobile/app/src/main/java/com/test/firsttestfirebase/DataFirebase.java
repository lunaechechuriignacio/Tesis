package com.test.firsttestfirebase;

import com.google.firebase.database.FirebaseDatabase;

public class DataFirebase {
    FirebaseDatabase database;
    String pathRelayNodo, automaticNodo="automatic",startTimeNodo="star_time",
            endTimeNodo="end_time",statusNodo="status";

    void DataFirebase(FirebaseDatabase database) {
        this.database = database;
    }


}
