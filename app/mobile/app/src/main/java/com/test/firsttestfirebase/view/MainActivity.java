package com.test.firsttestfirebase.view;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.DividerItemDecoration;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import android.os.Bundle;
import com.test.firsttestfirebase.R;
import com.test.firsttestfirebase.model.Component;
import com.test.firsttestfirebase.model.PirSensor;
import com.test.firsttestfirebase.model.Relay;
import com.test.firsttestfirebase.service.FirebaseService;
import com.test.firsttestfirebase.view.adapter.RelayRecyclerViewAdapter;
import com.test.firsttestfirebase.view.viewHolder.PirSensorViewHolder;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {
    private static final FirebaseService firebaseService = FirebaseService.getInstance();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        List<Component> componentInitialList = firebaseService.getComponentList();
        this.bindPirSensor(getPirSensor(componentInitialList));
        this.bindRelayList(getRelayList(componentInitialList));
    }

    private void bindPirSensor(PirSensor pirSensor) {
        PirSensorViewHolder pirSensorViewHolder = new PirSensorViewHolder(findViewById(R.id.cv_sensor));
        pirSensorViewHolder.bind(pirSensor);
    }

    private void bindRelayList(List<Relay> relayList) {
        RecyclerView rvRelays = findViewById(R.id.rv_relays);
        rvRelays.addItemDecoration(new DividerItemDecoration(this, DividerItemDecoration.VERTICAL));
        rvRelays.setLayoutManager(new LinearLayoutManager(this));
        rvRelays.setAdapter(new RelayRecyclerViewAdapter(relayList));
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