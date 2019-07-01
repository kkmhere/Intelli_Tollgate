package com.example.intelli_tollgate;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.FirebaseAuth;

public class forgetActivity extends AppCompatActivity
{
    EditText forgetEmail;
    Button sendForgetEmail;
    FirebaseAuth lauth;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_forget);

        lauth = FirebaseAuth.getInstance();

        forgetEmail = findViewById(R.id.email);

        sendForgetEmail = findViewById(R.id.sendEmail);

        sendForgetEmail.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                String forget = forgetEmail.getText().toString().trim();

                lauth.sendPasswordResetEmail(forget).addOnCompleteListener(new OnCompleteListener<Void>() {
                    @Override
                    public void onComplete(@NonNull Task<Void> task) {
                        if(task.isSuccessful())
                        {
                            Toast.makeText(forgetActivity.this, "We have sent you link to reset your password", Toast.LENGTH_SHORT).show();
                        }
                        else
                        {
                            Toast.makeText(forgetActivity.this, "Failed to send reset email", Toast.LENGTH_SHORT).show();
                        }
                    }
                });
            }
        });
    }
}
