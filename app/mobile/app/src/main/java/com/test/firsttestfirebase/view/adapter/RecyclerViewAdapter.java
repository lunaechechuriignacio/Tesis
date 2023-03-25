package com.test.firsttestfirebase.view.adapter;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;
import com.test.firsttestfirebase.R;
import com.test.firsttestfirebase.model.Component;
import java.util.List;

public class RecyclerViewAdapter extends RecyclerView.Adapter<RecyclerViewAdapter.ComponentViewHolder> {
    private List<Component> componentList;

    public RecyclerViewAdapter(List<Component> componentList) {
        this.componentList = componentList;
    }

    public class ComponentViewHolder extends RecyclerView.ViewHolder {
        private TextView tvComponent;

        public ComponentViewHolder(@NonNull View itemView) {
            super(itemView);
            this.tvComponent = itemView.findViewById(R.id.tv_component_list);
        }

        public void bind(Component component) {
            String alias = component.getAlias().replace("_", " ").toUpperCase();
            this.tvComponent.setText(alias);
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
