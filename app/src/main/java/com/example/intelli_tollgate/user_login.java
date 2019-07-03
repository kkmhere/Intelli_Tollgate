package com.example.intelli_tollgate;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageView;
import android.widget.Toast;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.auth.AuthResult;
import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;

public class user_login extends AppCompatActivity {
    private FirebaseAuth mAuth;
    String uname;
    String pass;
    EditText carnum,passs;
    Button loginButton,registerButton;

    public void goToRegister(View view)
    {
        Intent intent=new Intent(user_login.this,register.class);
        startActivity(intent);
    }

    @Override
    public void onStart() {
        super.onStart();
        // Check if user is signed in (non-null) and update UI accordingly.
        FirebaseUser currentUser = mAuth.getCurrentUser();

    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_user_login);
        carnum=(EditText)findViewById(R.id.card_number);
        passs=(EditText)findViewById(R.id.userpassword);
        pass=passs.getText().toString();
        loginButton=(Button)findViewById(R.id.loginButton);
        registerButton=(Button)findViewById(R.id.registerButton);
        mAuth = FirebaseAuth.getInstance();

        loginButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                uname= carnum.getText().toString();
                pass=passs.getText().toString();
                mAuth.signInWithEmailAndPassword(uname, pass).addOnCompleteListener(user_login.this, new OnCompleteListener<AuthResult>() {
                    @Override
                    public void onComplete(@NonNull Task<AuthResult> task) {
                        if(task.isSuccessful())
                        {
                            FirebaseUser user=mAuth.getCurrentUser();

                            Intent intent = new Intent(user_login.this, home.class);
                            startActivity(intent);
                            finish();
                        }
                        else
                        {
                            Toast.makeText(user_login.this, "Authentication failed.",
                                    Toast.LENGTH_SHORT).show();
                        }

                    }
                });

            }
        });

    }
}
