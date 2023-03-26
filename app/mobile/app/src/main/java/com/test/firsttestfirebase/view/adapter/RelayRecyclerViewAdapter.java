package com.test.firsttestfirebase.view.adapter;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;
import com.test.firsttestfirebase.R;
import com.test.firsttestfirebase.model.Relay;
import com.test.firsttestfirebase.view.viewHolder.RelayViewHolder;
import java.util.List;

public class RelayRecyclerViewAdapter extends RecyclerView.Adapter<RelayViewHolder> {
    private List<Relay> relayList;

    public RelayRecyclerViewAdapter(List<Relay> relayList) {
        this.relayList = relayList;
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
