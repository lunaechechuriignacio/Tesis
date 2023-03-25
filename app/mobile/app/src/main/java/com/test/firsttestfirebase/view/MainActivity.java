package com.test.firsttestfirebase.view;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.DividerItemDecoration;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import android.os.Bundle;
import android.widget.TextView;
import android.widget.Toast;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;
import com.test.firsttestfirebase.R;
import com.test.firsttestfirebase.model.Component;
import com.test.firsttestfirebase.service.FirebaseService;
import com.test.firsttestfirebase.view.adapter.RecyclerViewAdapter;

import java.util.List;

public class MainActivity extends AppCompatActivity {
    private static final FirebaseService firebaseService = FirebaseService.getInstance();
    private RecyclerView rvComponents;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        this.rvComponents = findViewById(R.id.rvComponents);
        this.rvComponents.addItemDecoration(new DividerItemDecoration(this, DividerItemDecoration.VERTICAL));
        this.rvComponents.setLayoutManager(new LinearLayoutManager(this));

        List<Component> componentList = firebaseService.getComponentList();
        RecyclerViewAdapter recyclerViewAdapter = new RecyclerViewAdapter(componentList);
        this.rvComponents.setAdapter(recyclerViewAdapter);
    }

    private void buildListenerForPirSensorAutomatic(TextView textView) {
        final DatabaseReference reference = FirebaseDatabase.getInstance().getReference("pir_sensor").child("automatic");
        reference.addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                String value = FirebaseService.getInstance().getPirSensorPropertyValue("automatic").toString();
                textView.setText(value);
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {
                Toast.makeText(MainActivity.this, "Fail to get data.", Toast.LENGTH_SHORT).show();
            }
        });
    }
}