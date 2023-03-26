package com.test.firsttestfirebase.view.viewHolder;

import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import androidx.annotation.NonNull;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.ValueEventListener;
import com.test.firsttestfirebase.R;
import com.test.firsttestfirebase.mapper.DataMapper;
import com.test.firsttestfirebase.model.PirSensor;
import com.test.firsttestfirebase.service.FirebaseService;

public class PirSensorViewHolder {
    private final TextView tvSensor;
    private final EditText etSensorTimeSeconds;
    private final Button btnSensorConfirmTimeSeconds;

    private final String PROPERTY_TIME_SECONDS = "time_seconds";

    public PirSensorViewHolder(@NonNull View itemView) {
        this.tvSensor = itemView.findViewById(R.id.tv_sensor);
        this.etSensorTimeSeconds = itemView.findViewById(R.id.et_sensor_time_seconds);
        this.btnSensorConfirmTimeSeconds = itemView.findViewById(R.id.btn_sensor_confirm_time_seconds);
    }

    public void bind(PirSensor pirSensor) {
        this.tvSensor.setText(DataMapper.toCleanComponentAlias(pirSensor.getAlias()));
        this.etSensorTimeSeconds.setText(pirSensor.getTimeSeconds().toString());

        this.bindComponentViewListeners();
        this.bindDatabaseListeners();
    }

    public void bindComponentViewListeners() {
        this.btnSensorConfirmTimeSeconds.setOnClickListener(view -> {
            FirebaseService.getInstance().setPirSensorPropertyValue(PROPERTY_TIME_SECONDS, Integer.parseInt(this.etSensorTimeSeconds.getText().toString()));
        });
    }

    public void bindDatabaseListeners() {
        DatabaseReference timeSecondsPropertyReference = FirebaseService.getInstance().getPirSensorPropertyReference(PROPERTY_TIME_SECONDS);
        timeSecondsPropertyReference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                Integer newValue = snapshot.getValue(Integer.class);
                etSensorTimeSeconds.setText(newValue.toString());
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
                // TODO
            }
        });
    }
}
