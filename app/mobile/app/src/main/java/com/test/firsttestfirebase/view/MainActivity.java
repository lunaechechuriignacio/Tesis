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
import com.test.firsttestfirebase.service.FirebaseService;

public class MainActivity extends AppCompatActivity {
    private static final FirebaseService firebaseService = FirebaseService.getInstance();
    private static final String PIR_SENSOR_PATH = "pir_sensor";
    private static final String PIR_SENSOR_PROPERTY_AUTOMATIC = "automatic";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //getdataRelay=new GetDataFirebaseRelay("relays");
        //getdataRelay.getDAtaRelays(relays=new ArrayList<>());
        final TextView dataStringTextView = findViewById(R.id.textTest);
        final TextView dataIntTextView = findViewById(R.id.dataInt);
        final Switch manualSwitch = findViewById(R.id.switchOn_OffRelay_1);
        final Switch automaticSwitch = findViewById(R.id.switchAutomaticoRelay_1);
        final Button buttonRelay_1 = findViewById(R.id.buttonRelay_1);
        final Button buttonEncendidoRelay_1 = findViewById(R.id.buttonEncendidoRelay_1);
        final EditText tiempoAutomatico = findViewById(R.id.editTextTimeswitchAutomaticoRelay_1);
        FirebaseDatabase database = FirebaseDatabase.getInstance();
        final DatabaseReference reference = database.getReference(PIR_SENSOR_PATH).child(PIR_SENSOR_PROPERTY_AUTOMATIC);

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
            FirebaseDatabase database1 = FirebaseDatabase.getInstance();
            final DatabaseReference reference1 = database1.getReference(PIR_SENSOR_PATH).child("time_seconds");
            int tiempo = Integer.parseInt(tiempoAutomatico.getText().toString());
            reference1.setValue(tiempo * 60);
        });

        automaticSwitch.setOnClickListener(view -> {
            FirebaseDatabase database12 = FirebaseDatabase.getInstance();
            final DatabaseReference reference12 = database12.getReference(PIR_SENSOR_PATH).child("automatic");
            if (automaticSwitch.isChecked()) {
                manualSwitch.setChecked(false);
                manualSwitch.setEnabled(false);
                reference12.setValue(0);
            } else {
                manualSwitch.setEnabled(true);
                reference12.setValue(1);
            }
        });

        manualSwitch.setOnClickListener(view -> {
            if (manualSwitch.isChecked())
                firebaseService.setRelayPropertyValue(1, "status", 0);
            else
                firebaseService.setRelayPropertyValue(1, "status", 1);
        });
    }
}