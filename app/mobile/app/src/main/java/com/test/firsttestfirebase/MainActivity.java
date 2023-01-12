package com.test.firsttestfirebase;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {
   // private static final String  path="Test";
   // private static final String  pathTestString="TestString";
    private static final String  path="pir_sensor";
    private static final String  pathTestString="automatic";
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final TextView dataStringTextView= findViewById(R.id.textTest);
        final TextView dataIntTextView=findViewById(R.id.dataInt);
        FirebaseDatabase database=FirebaseDatabase.getInstance();
        final DatabaseReference reference= database.getReference(path).child(pathTestString);
        reference.addValueEventListener(new ValueEventListener() {
             @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                String value=snapshot.getValue(Integer.class).toString();
                 dataIntTextView.setText(value);

                // value=snapshot.getValue(String.class);
               //  dataStringTextView.setText(value);


            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
                Toast.makeText(MainActivity.this, "Fail to get data.", Toast.LENGTH_SHORT).show();
            }
        });

    }
}