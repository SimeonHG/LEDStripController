package com.example.stripapp;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

public class SettingsActivity extends AppCompatActivity {
    EditText url;
    Button saveUrl;

    private FirebaseAuth mAuth;
    private DatabaseReference dbRef;
    private FirebaseUser currentUser;
    private String currentUserID;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        url = findViewById(R.id.url);
        saveUrl = findViewById(R.id.saveUrlBtn);

        mAuth = FirebaseAuth.getInstance();
        currentUser = mAuth.getCurrentUser();
        currentUserID = mAuth.getCurrentUser().getUid();
        dbRef = FirebaseDatabase.getInstance().getReference();


        saveUrl.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {


                dbRef.child("Settings").child(currentUserID).child("url").setValue(url.getText().toString());
            }
        });
    }
}
