package com.example.stripapp;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;


import android.graphics.Color;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.TextView;


import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;

import yuku.ambilwarna.AmbilWarnaDialog;

public class CustomActivity extends AppCompatActivity implements AdapterView.OnItemSelectedListener {
    int mDefaultColor;
    String hexColor;
    Button mButton;
    TextView colorText;
    Spinner effectSpinner;

    EditText presetName;
    Button savePreset;

    String chosenEffect;


    int red ;
    int green ;
    int blue;
    int alpha;

    private FirebaseAuth mAuth;
    private DatabaseReference dbRef;
    private FirebaseUser currentUser;
    private String currentUserID;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_custom);

        mAuth = FirebaseAuth.getInstance();
        currentUser = mAuth.getCurrentUser();
        currentUserID = mAuth.getCurrentUser().getUid();
        dbRef = FirebaseDatabase.getInstance().getReference();

        mDefaultColor = ContextCompat.getColor(CustomActivity.this, R.color.colorPrimary);
        mButton =  findViewById(R.id.button);
        colorText = findViewById(R.id.colorText);
        presetName = findViewById(R.id.presetName);
        savePreset = findViewById(R.id.savePreset);

        effectSpinner = findViewById(R.id.effectSpinner);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this,
                R.array.effects, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        effectSpinner.setAdapter(adapter);

        effectSpinner.setOnItemSelectedListener(this);



        mButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                openColorPicker();
            }
        });

        savePreset.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String request = genRequest();
                String args = genArgs();
                dbRef.child("Presets").child(currentUserID).child(presetName.getText().toString()).child("request").setValue(request);
                dbRef.child("Presets").child(currentUserID).child(presetName.getText().toString()).child("args").setValue(args);
                dbRef.child("Presets").child(currentUserID).child(presetName.getText().toString()).child("name").setValue(presetName.getText().toString());
            }
        });


    }

    private String genRequest() {
        String eff = chosenEffect.toLowerCase();
        String url = "http://192.168.43.100/";

        if(eff.equals("wipe") || eff.equals("breathe") || eff.equals("bounce")){
            url = url.concat(eff +"?r=" + red +"&g=" + green +"&b=" + blue);
            //colorText.setText(url);
        } else {
            url = url.concat(eff);
           // colorText.setText(url);
        }

        return url;
    }
    private String genArgs(){
        String eff = chosenEffect.toLowerCase();
        if(eff.equals("wipe") || eff.equals("breathe") || eff.equals("bounce")) {
            eff = eff.concat("?r=" + red + "&g=" + green + "&b=" + blue);
            //colorText.setText(url);
        }
        return eff;
    }

    public void openColorPicker() {
        AmbilWarnaDialog colorPicker = new AmbilWarnaDialog(this, mDefaultColor, new AmbilWarnaDialog.OnAmbilWarnaListener() {
            @Override
            public void onCancel(AmbilWarnaDialog dialog) {

            }

            @Override
            public void onOk(AmbilWarnaDialog dialog, int color) {
                mDefaultColor = color;
                hexColor = String.format("#%06X", (0xFFFFFF & mDefaultColor));
                red = Color.red(mDefaultColor);
                green = Color.green(mDefaultColor);
                blue = Color.blue(mDefaultColor);
                alpha = Color.alpha(mDefaultColor);
                colorText.setText(hexColor + " r=" +red + " g=" +green + " b=" +blue);
            }
        });
        colorPicker.show();
    }

    @Override
    public void onItemSelected(AdapterView<?> adapterView, View view, int i, long l) {

        chosenEffect = adapterView.getItemAtPosition(i).toString();

        colorText.setText(chosenEffect);
    }

    @Override
    public void onNothingSelected(AdapterView<?> adapterView) {

    }



}
