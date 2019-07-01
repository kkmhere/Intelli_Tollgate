package com.example.intelli_tollgate;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

public class check extends AppCompatActivity {
    EditText checkText;
    String pin="shagunkatoch",checkText1;
    Button checkButton;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_check);
        checkText=(EditText)findViewById(R.id.passCheck);
        checkButton=(Button)findViewById(R.id.verifyButton);

        checkButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                checkText1=checkText.getText().toString();
                if(checkText1.equals(pin))
                {
                    Intent intent=new Intent(check.this,admin_login.class);
                    startActivity(intent);
                }
                else
                {
                    Toast.makeText(check.this,"NOT CORRECT,FUCK OFF",Toast.LENGTH_SHORT).show();
                }
            }
        });
    }
}
