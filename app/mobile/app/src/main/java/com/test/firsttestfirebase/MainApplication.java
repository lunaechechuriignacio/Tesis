package com.test.firsttestfirebase;

import com.google.firebase.database.FirebaseDatabase;

public class MainApplication extends android.app.Application {
    @Override
    public void onCreate() {
        super.onCreate();
        FirebaseDatabase.getInstance().setPersistenceEnabled(true);
    }
}
