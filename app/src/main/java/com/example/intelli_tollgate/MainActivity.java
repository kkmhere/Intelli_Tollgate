package com.example.intelli_tollgate;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.provider.ContactsContract;
import android.view.View;
import android.widget.ImageView;

public class MainActivity extends AppCompatActivity {

    public void adminLogin(View view)
    {
        Intent intent=new Intent(MainActivity.this,check.class);
        startActivity(intent);
    }

    public void userLogin(View view)
    {
        Intent intent=new Intent(MainActivity.this,user_login.class);
        startActivity(intent);
    }


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ImageView userImage=(ImageView)findViewById(R.id.user_acces);
        ImageView adminImage=(ImageView)findViewById(R.id.admin_access);
    }
}
