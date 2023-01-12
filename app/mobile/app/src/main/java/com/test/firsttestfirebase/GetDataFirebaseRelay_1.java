package com.test.firsttestfirebase;

import androidx.annotation.NonNull;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class GetDataFirebaseRelay_1 {
    FirebaseDatabase database;
    DatabaseReference reference;

    GetDataFirebaseRelay_1(String path) {
        database = FirebaseDatabase.getInstance();
        reference = database.getReference(path);

    }
/*
    public int getValueAutomatic() {
       reference.child("automatic").addValueEventListener(new ValueEventListener() {
           @Override
           public void onDataChange(@NonNull DataSnapshot snapshot) {
               return snapshot.getValue(Integer.class);
           }

           @Override
           public void onCancelled(@NonNull DatabaseError error) {

           }
       });
    }

*/
}