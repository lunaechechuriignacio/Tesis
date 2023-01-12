package com.test.firsttestfirebase;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Switch;
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
    private static final String path = "pir_sensor";
    private static final String pathTestString = "automatic";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final TextView dataStringTextView = findViewById(R.id.textTest);
        final TextView dataIntTextView = findViewById(R.id.dataInt);
        final Switch manualSwitch = findViewById(R.id.switchOn_OffRelay_1);
        final Switch automaticSwitch = findViewById(R.id.switchAutomaticoRelay_1);
        final Button buttonRelay_1 = findViewById(R.id.buttonRelay_1);
        final Button buttonEncendidoRelay_1 = findViewById(R.id.buttonEncendidoRelay_1);
        final EditText tiempoAutomatico = findViewById(R.id.editTextTimeswitchAutomaticoRelay_1);
        FirebaseDatabase database = FirebaseDatabase.getInstance();
        final DatabaseReference reference = database.getReference(path).child(pathTestString);
        reference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                String value = snapshot.getValue(Integer.class).toString();
                dataIntTextView.setText(value);

                // value=snapshot.getValue(String.class);
                //  dataStringTextView.setText(value);
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
                Toast.makeText(MainActivity.this, "Fail to get data.", Toast.LENGTH_SHORT).show();
            }
        });

        buttonRelay_1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                FirebaseDatabase database = FirebaseDatabase.getInstance();
                final DatabaseReference reference = database.getReference(path).child("time_seconds");
                int tiempo = Integer.valueOf(tiempoAutomatico.getText().toString());
                reference.setValue(tiempo * 60);
            }
        });


        automaticSwitch.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                FirebaseDatabase database = FirebaseDatabase.getInstance();
                final DatabaseReference reference = database.getReference(path).child("automatic");
                if (automaticSwitch.isChecked()) {
                    manualSwitch.setChecked(false);
                    manualSwitch.setEnabled(false);
                    reference.setValue(1);
                } else {
                    manualSwitch.setEnabled(true);
                    reference.setValue(0);
                }
            }
        });

        manualSwitch.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                FirebaseDatabase database = FirebaseDatabase.getInstance();
                final DatabaseReference reference = database.getReference(path).child("status");
                if (manualSwitch.isChecked())
                    reference.setValue(1);
                else
                    reference.setValue(0);
            }

        });


    }

}