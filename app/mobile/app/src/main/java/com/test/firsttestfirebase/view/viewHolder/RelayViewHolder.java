package com.test.firsttestfirebase.view.viewHolder;

import android.view.View;
import android.widget.Switch;
import android.widget.TextView;
import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;
import com.test.firsttestfirebase.R;
import com.test.firsttestfirebase.mapper.DataMapper;
import com.test.firsttestfirebase.model.Relay;
import com.test.firsttestfirebase.service.FirebaseService;

public class RelayViewHolder extends RecyclerView.ViewHolder {
    private final TextView tvRelay;
    private final Switch swRelayAutomatic;
    private final Switch swRelayLight;

    public RelayViewHolder(@NonNull View itemView) {
        super(itemView);
        this.tvRelay = itemView.findViewById(R.id.tv_relay);
        this.swRelayAutomatic = itemView.findViewById(R.id.sw_relay_automatic);
        this.swRelayLight = itemView.findViewById(R.id.sw_relay_light);
    }

    public void bind(Relay relay) {
        this.tvRelay.setText(DataMapper.toCleanComponentAlias(relay.getAlias()));

        this.swRelayAutomatic.setChecked(relay.isAutomatic());
        this.setEnabledSwRelayLight();
        this.swRelayAutomatic.setOnClickListener(view -> {
            FirebaseService.getInstance().setRelayPropertyValue(relay.getNumber(), "automatic", swRelayAutomatic.isChecked());
            this.setEnabledSwRelayLight();
        });

        this.swRelayLight.setChecked(DataMapper.toBoolean(relay.getRelayStatus()));
        this.swRelayLight.setOnClickListener(view -> {
            FirebaseService.getInstance().setRelayPropertyValue(relay.getNumber(), "status", DataMapper.toInteger(swRelayLight.isChecked()));
        });
    }

    private void setEnabledSwRelayLight() {
        this.swRelayLight.setEnabled(!this.swRelayAutomatic.isChecked());
    }
}
