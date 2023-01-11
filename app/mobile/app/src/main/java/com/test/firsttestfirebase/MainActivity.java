package com.test.firsttestfirebase;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {
    private static final String  path="Test";
    private static final String  pathTestString="TestString";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final TextView tv= findViewById(R.id.textTest);
        FirebaseDatabase database=FirebaseDatabase.getInstance();
        final DatabaseReference reference= database.getReference(path).child(pathTestString);
        reference.addValueEventListener(new ValueEventListener() {
             @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                tv.setText(snapshot.getValue(String.class));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });

    }
}