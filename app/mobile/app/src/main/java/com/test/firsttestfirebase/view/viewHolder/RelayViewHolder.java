package com.test.firsttestfirebase.view.viewHolder;

import android.view.View;
import android.widget.Switch;
import android.widget.TextView;
import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.ValueEventListener;
import com.test.firsttestfirebase.R;
import com.test.firsttestfirebase.mapper.DataMapper;
import com.test.firsttestfirebase.model.Relay;
import com.test.firsttestfirebase.service.FirebaseService;

public class RelayViewHolder extends RecyclerView.ViewHolder {
    private final TextView tvRelay;
    private final Switch swRelayAutomatic;
    private final Switch swRelayLight;

    private final String PROPERTY_AUTOMATIC = "automatic";
    private final String PROPERTY_STATUS = "status";

    public RelayViewHolder(@NonNull View itemView) {
        super(itemView);
        this.tvRelay = itemView.findViewById(R.id.tv_relay);
        this.swRelayAutomatic = itemView.findViewById(R.id.sw_relay_automatic);
        this.swRelayLight = itemView.findViewById(R.id.sw_relay_light);
    }

    public void bind(Relay relay) {
        this.tvRelay.setText(DataMapper.toCleanComponentAlias(relay.getAlias()));
        this.swRelayAutomatic.setChecked(relay.isAutomatic()); this.setEnabledSwRelayLight();
        this.swRelayLight.setChecked(DataMapper.toBoolean(relay.getRelayStatus()));

        this.bindComponentViewListeners(relay.getNumber());
        this.bindDatabaseListeners(relay.getNumber());
    }

    public void bindComponentViewListeners(Integer relayNumber) {
        this.swRelayAutomatic.setOnClickListener(view -> {
            FirebaseService.getInstance().setRelayPropertyValue(relayNumber, PROPERTY_AUTOMATIC, this.swRelayAutomatic.isChecked());
            this.setEnabledSwRelayLight();
        });
        this.swRelayLight.setOnClickListener(view -> {
            FirebaseService.getInstance().setRelayPropertyValue(relayNumber, PROPERTY_STATUS, DataMapper.toInteger(this.swRelayLight.isChecked()));
        });
    }

    public void bindDatabaseListeners(Integer relayNumber) {
        DatabaseReference automaticPropertyReference = FirebaseService.getInstance().getRelayPropertyReference(relayNumber, PROPERTY_AUTOMATIC);
        automaticPropertyReference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                Boolean newValue = snapshot.getValue(Boolean.class);
                swRelayAutomatic.setChecked(newValue);
                setEnabledSwRelayLight();
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
                // TODO
            }
        });

        DatabaseReference statusPropertyReference = FirebaseService.getInstance().getRelayPropertyReference(relayNumber, PROPERTY_STATUS);
        statusPropertyReference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                Integer newValue = snapshot.getValue(Integer.class);
                swRelayLight.setChecked(DataMapper.toBoolean(newValue));
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
                // TODO
            }
        });
    }

    private void setEnabledSwRelayLight() {
        this.swRelayLight.setEnabled(!this.swRelayAutomatic.isChecked());
    }
}
