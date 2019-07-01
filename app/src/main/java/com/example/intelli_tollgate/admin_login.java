package com.example.intelli_tollgate;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;

public class admin_login extends AppCompatActivity
{
    EditText email,password;
    Button login;
    FirebaseAuth auth;

    public void forget(View view)
    {
        startActivity(new Intent(admin_login.this,forgetActivity.class));
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_admin_login);

        auth = FirebaseAuth.getInstance();

        email = findViewById(R.id.Email_ID);
        password = findViewById(R.id.password);

        login = findViewById(R.id.login_button);

        login.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                String emailID = email.getText().toString().trim();
                final String pwd = password.getText().toString().trim();

                auth.signInWithEmailAndPassword(emailID,pwd).addOnCompleteListener(admin_login.this, new OnCompleteListener<AuthResult>() {
                    @Override
                    public void onComplete(@NonNull Task<AuthResult> task) {
                        if(!task.isSuccessful())
                        {
                            if(pwd.length() < 6)
                            {
                                password.setError("Minimum [password length is 6!!");
                            }
                            else
                            {
                                Toast.makeText(admin_login.this, "Authentication failed", Toast.LENGTH_SHORT).show();
                            }
                        }
                        else
                        {
                            Intent intent= new Intent(admin_login.this,AdminActivity.class);
                            startActivity(intent);
                            finish();
                        }
                    }
                });
            }
        });
    }
}
