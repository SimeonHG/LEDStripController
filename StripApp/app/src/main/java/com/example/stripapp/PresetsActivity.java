package com.example.stripapp;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.StringRequest;
import com.android.volley.toolbox.Volley;
import com.firebase.ui.database.FirebaseRecyclerAdapter;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.Query;
import com.google.firebase.database.ValueEventListener;

public class PresetsActivity extends AppCompatActivity {

    private RecyclerView presetsRecycler;
    private DatabaseReference dbRef;
    private DatabaseReference presetsRef;
    private String dbUrl;
    private String currentUserID;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_presets);

        presetsRecycler = findViewById(R.id.preset_recycler);
        presetsRecycler.setHasFixedSize(true);
        presetsRecycler.setLayoutManager(new LinearLayoutManager(this));

        currentUserID = FirebaseAuth.getInstance().getCurrentUser().getUid();

        dbRef = FirebaseDatabase.getInstance().getReference();
        presetsRef = FirebaseDatabase.getInstance().getReference().child("Presets").child(currentUserID);
        displayPresets();



        dbRef.addListenerForSingleValueEvent(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
                dbUrl = dataSnapshot.child("Settings").child(currentUserID).child("url").getValue().toString();
            }

            @Override
            public void onCancelled(@NonNull DatabaseError databaseError) {

            }
        });

    }

    private void displayPresets() {
        Query presetQuery = presetsRef.orderByKey();
        FirebaseRecyclerAdapter<Preset, PresetsViewHolder> firebaseRecyclerAdapter = new FirebaseRecyclerAdapter<Preset, PresetsViewHolder>
                (
                        Preset.class, R.layout.all_presets_display_layout, PresetsViewHolder.class, presetQuery
                ) {
            @Override
            protected void populateViewHolder(final PresetsViewHolder presetsViewHolder, final Preset preset, final int position) {

                presetsViewHolder.displayPresets(preset);
                presetsViewHolder.mView.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View view) {
                        sendRequest(dbUrl +  preset.args);
                    }
                });
//                friendlistRef.addListenerForSingleValueEvent(new ValueEventListener() {
//                    @Override
//                    public void onDataChange(@NonNull DataSnapshot dataSnapshot) {
//                        if (dataSnapshot.hasChild(preset.uid)) {
//                            presetsViewHolder.displayPreset(preset);
//                            presetsViewHolder.mView.setOnClickListener(new View.OnClickListener() {
//                                @Override
//                                public void onClick(View view) {
//                                    String visit_user_id = getRef(position).getKey();
//
//                                    //Intent profileIntent = new Intent(PresetsActivity.this, PersonProfileActivity.class);
//                                    //profileIntent.putExtra("visit_user_id", visit_user_id);
//                                    //startActivity(profileIntent);
//                                }
//                            });
//                        }
//                        else {
//                            presetsViewHolder.vanish();
//                        }
//                    }

//                    @Override
//                    public void onCancelled(@NonNull DatabaseError databaseError) {
//
//                    }
//                });


            }
        };
        presetsRecycler.setAdapter(firebaseRecyclerAdapter);
    }

    public static class PresetsViewHolder extends RecyclerView.ViewHolder{
        private View mView;

        private TextView name;
        private TextView request;



        public PresetsViewHolder(@NonNull View itemView) {
            super(itemView);
            mView = itemView;

        }


        void displayPresets(Preset preset) {
            name = itemView.findViewById(R.id.all_presets_name);
            request = itemView.findViewById(R.id.all_preset_req);

            name.setText(preset.name);
            request.setText(preset.request);

        }

        void vanish(){
            mView.findViewById(R.id.presetsViewHolderLayout).setVisibility(View.GONE);
            mView.findViewById(R.id.all_presets_name).setVisibility(View.GONE);
            mView.findViewById(R.id.all_preset_req).setVisibility(View.GONE);


        }
    }

    public void sendRequest(String request){
        RequestQueue queue = Volley.newRequestQueue(PresetsActivity.this);
        //String url ="http://192.168.43.100/bounce?r=0&g=255&b=100";
        String url = request;
        StringRequest stringRequest = new StringRequest(Request.Method.GET, url,
                new Response.Listener<String>() {
                    @Override
                    public void onResponse(String response) {
                        // Display the first 500 characters of the response string.


                    }
                }, new Response.ErrorListener() {
            @Override
            public void onErrorResponse(VolleyError error) {

            }
        });
        queue.add(stringRequest);
    }



}
