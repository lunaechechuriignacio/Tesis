package com.test.firsttestfirebase.view.adapter;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Switch;
import android.widget.TextView;
import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;
import com.test.firsttestfirebase.R;
import com.test.firsttestfirebase.mapper.Mapper;
import com.test.firsttestfirebase.model.Component;
import com.test.firsttestfirebase.model.Relay;
import com.test.firsttestfirebase.service.FirebaseService;

import java.util.List;

public class RecyclerViewAdapter extends RecyclerView.Adapter<RecyclerViewAdapter.ComponentViewHolder> {
    private List<Component> componentList;

    public RecyclerViewAdapter(List<Component> componentList) {
        this.componentList = componentList;
    }

    public class ComponentViewHolder extends RecyclerView.ViewHolder {
        private TextView tvComponent;
        private Switch swAutomatic;
        private Switch swLight;

        public ComponentViewHolder(@NonNull View itemView) {
            super(itemView);
            this.tvComponent = itemView.findViewById(R.id.tv_component);
            this.swAutomatic = itemView.findViewById(R.id.sw_automatic);
            this.swLight = itemView.findViewById(R.id.sw_light);
        }

        public void bind(Component component) {
            String alias = component.getAlias().replace("_", " ").toUpperCase();
            this.tvComponent.setText(alias);

            if(component instanceof Relay) {
                Relay relay = ((Relay)component);

                this.swAutomatic.setChecked(relay.isAutomatic());
                this.swAutomatic.setOnClickListener(view -> {
                    FirebaseService.getInstance().setRelayPropertyValue(relay.getNumber(), "automatic", swAutomatic.isChecked());
                });

                this.swLight.setChecked(Mapper.toBoolean(relay.getRelayStatus()));
                this.swLight.setOnClickListener(view -> {
                    FirebaseService.getInstance().setRelayPropertyValue(relay.getNumber(), "status", Mapper.toInteger(swLight.isChecked()));
                });
            }
        }
    }

    @NonNull
    @Override
    public ComponentViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        LayoutInflater layoutInflater = LayoutInflater.from(parent.getContext());
        View view = layoutInflater.inflate(R.layout.component_row, parent, false); // el false es para que no se adjunte tan rapido (previene errores)

        ComponentViewHolder componentViewHolder = new ComponentViewHolder(view);
        return componentViewHolder;
    }

    @Override
    public void onBindViewHolder(@NonNull ComponentViewHolder holder, int position) {
        holder.bind(this.componentList.get(position));
    }

    @Override
    public int getItemCount() {
        return this.componentList.size();
    }
}
