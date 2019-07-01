package com.example.intelli_tollgate;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;

public class register extends AppCompatActivity {

    EditText registerEmail,registerPass;
    Button signUp;
    private FirebaseAuth mAuth;
    String uname,userpass;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_register);
        registerEmail=(EditText)findViewById(R.id.regEmail);
        registerPass=(EditText)findViewById(R.id.regPass);
        signUp=(Button)findViewById(R.id.buttonReg);
        mAuth = FirebaseAuth.getInstance();

        signUp.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                uname=registerEmail.getText().toString();
                userpass=registerPass.getText().toString();
                mAuth.createUserWithEmailAndPassword(uname, userpass).addOnCompleteListener(register.this, new OnCompleteListener<AuthResult>() {
                    @Override
                    public void onComplete(@NonNull Task<AuthResult> task) {

                        if (task.isSuccessful()) {
                            FirebaseUser user = mAuth.getCurrentUser();
                            Toast.makeText(register.this, "You have been registered successfully", Toast.LENGTH_SHORT).show();
                            startActivity(new Intent(register.this, home.class));
                        } else {

                            Toast.makeText(register.this, "Error in registry", Toast.LENGTH_SHORT).show();

                        }

                    }

                });
            }
        });

    }
}
