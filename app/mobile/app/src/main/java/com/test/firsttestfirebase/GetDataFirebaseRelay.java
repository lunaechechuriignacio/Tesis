package com.test.firsttestfirebase;

import android.widget.Toast;

import androidx.annotation.NonNull;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.lang.reflect.Array;
import java.util.ArrayList;

public class GetDataFirebaseRelay {
    FirebaseDatabase database;
    DatabaseReference reference;
    String pathRaiz = "Relays";
    //private ArrayList<Relay> relays;


    GetDataFirebaseRelay(String path) {
        database = FirebaseDatabase.getInstance();
        reference = database.getReference(pathRaiz);

    }


    public void getDAtaRelays(ArrayList<Relay> relays) {
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
}