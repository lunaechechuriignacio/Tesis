package com.test.firsttestfirebase.view;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.DividerItemDecoration;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import android.os.Bundle;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import com.test.firsttestfirebase.R;
import com.test.firsttestfirebase.mapper.DataMapper;
import com.test.firsttestfirebase.model.Component;
import com.test.firsttestfirebase.model.PirSensor;
import com.test.firsttestfirebase.model.Relay;
import com.test.firsttestfirebase.service.FirebaseService;
import com.test.firsttestfirebase.view.adapter.RelayRecyclerViewAdapter;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {
    private static final FirebaseService firebaseService = FirebaseService.getInstance();
    private RecyclerView rvRelays;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        List<Component> componentList = firebaseService.getComponentList();

        this.renderPirSensor(getPirSensor(componentList));
        this.renderRelayList(getRelayList(componentList));
    }

    private void renderPirSensor(PirSensor pirSensor) {
        TextView tvSensor = findViewById(R.id.tv_sensor);
        EditText etSensorTimeSeconds = findViewById(R.id.et_sensor_time_seconds);
        Button btnSensorConfirmTimeSeconds = findViewById(R.id.btn_sensor_confirm_time_seconds);

        tvSensor.setText(DataMapper.toCleanComponentAlias(pirSensor.getAlias()));
        etSensorTimeSeconds.setText(pirSensor.getTimeSeconds().toString());

        btnSensorConfirmTimeSeconds.setOnClickListener(view -> {
            firebaseService.setPirSensorPropertyValue("time_seconds", Integer.parseInt(etSensorTimeSeconds.getText().toString()));
        });
    }

    private void renderRelayList(List<Relay> relayList) {
        this.rvRelays = findViewById(R.id.rv_relays);
        this.rvRelays.addItemDecoration(new DividerItemDecoration(this, DividerItemDecoration.VERTICAL));
        this.rvRelays.setLayoutManager(new LinearLayoutManager(this));
        this.rvRelays.setAdapter(new RelayRecyclerViewAdapter(relayList));
    }

    private PirSensor getPirSensor(@NonNull List<Component> componentList) {
        PirSensor pirSensor = null;

        int index = 0;
        while(pirSensor == null && index < componentList.size()) {
            Component currentComponent = componentList.get(index);
            if(currentComponent instanceof PirSensor) pirSensor = ((PirSensor)componentList.get(index));

            index++;
        }

        return pirSensor;
    }

    private List<Relay> getRelayList(@NonNull List<Component> componentList) {
        List<Relay> relayList = new ArrayList<>();
        for(Component component: componentList) {
            if(component instanceof Relay) relayList.add((Relay)component);
        }

        return relayList;
    }
}