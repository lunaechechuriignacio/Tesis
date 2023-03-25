package com.test.firsttestfirebase.view.adapter;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Switch;
import android.widget.TextView;
import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;
import com.test.firsttestfirebase.R;
import com.test.firsttestfirebase.mapper.DataMapper;
import com.test.firsttestfirebase.model.Relay;
import com.test.firsttestfirebase.service.FirebaseService;
import java.util.List;

public class RelayRecyclerViewAdapter extends RecyclerView.Adapter<RelayRecyclerViewAdapter.RelayViewHolder> {
    private List<Relay> relayList;

    public RelayRecyclerViewAdapter(List<Relay> relayList) {
        this.relayList = relayList;
    }

    public class RelayViewHolder extends RecyclerView.ViewHolder {
        private TextView tvRelay;
        private Switch swRelayAutomatic;
        private Switch swRelayLight;

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

    @NonNull
    @Override
    public RelayViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        LayoutInflater layoutInflater = LayoutInflater.from(parent.getContext());
        View view = layoutInflater.inflate(R.layout.relay_row, parent, false); // el false es para que no se adjunte tan rapido (previene errores)

        return new RelayViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull RelayViewHolder holder, int position) {
        holder.bind(this.relayList.get(position));
    }

    @Override
    public int getItemCount() {
        return this.relayList.size();
    }
}
