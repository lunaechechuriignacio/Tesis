package com.test.firsttestfirebase.view;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
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
import com.test.firsttestfirebase.R;
import com.test.firsttestfirebase.model.Component;
import com.test.firsttestfirebase.service.FirebaseService;
import java.util.List;

public class MainActivity extends AppCompatActivity {
    private static final FirebaseService firebaseService = FirebaseService.getInstance();

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
        final DatabaseReference reference = database.getReference("pir_sensor").child("automatic");

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

        buttonRelay_1.setOnClickListener(view -> {
            int tiempo = Integer.parseInt(tiempoAutomatico.getText().toString());
            firebaseService.setPirSensorPropertyValue("time_seconds", tiempo * 60);
        });

        automaticSwitch.setOnClickListener(view -> {
            if (automaticSwitch.isChecked()) {
                manualSwitch.setChecked(false);
                manualSwitch.setEnabled(false);
                firebaseService.setPirSensorPropertyValue("automatic", 0);
            } else {
                manualSwitch.setEnabled(true);
                firebaseService.setPirSensorPropertyValue("automatic", 1);
            }
        });

        manualSwitch.setOnClickListener(view -> {
            // List<Component> componentList = firebaseService.getComponentList();
            if (manualSwitch.isChecked())
                firebaseService.setRelayPropertyValue(1, "status", 0);
            else
                firebaseService.setRelayPropertyValue(1, "status", 1);
        });
    }
}