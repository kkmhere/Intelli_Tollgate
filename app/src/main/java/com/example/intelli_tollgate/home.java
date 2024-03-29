package com.example.intelli_tollgate;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;
import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

public class home extends AppCompatActivity {
    Button pay1,pay2,pay3,pay4,pay5;
    int walletBalance,niceAmountInt,payStatus=0,nelaAmountInt;
    int tollNo;
    int currentBalance;
    private FirebaseAuth mAuth;
    FirebaseUser user;
    DatabaseReference myRef;
    DatabaseReference myref1;
    DatabaseReference payRef,tollRef;
    String niceAmount,nelaAmount;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home);
        mAuth = FirebaseAuth.getInstance();
        FirebaseDatabase database = FirebaseDatabase.getInstance();
         user= mAuth.getCurrentUser();
        myRef = database.getReference("WALLET")
                .child(user.getUid());

        payRef=database.getReference("PAY_STATUS")
                .child(user.getUid());
        payRef.setValue(payStatus);
        myref1=database.getReference("WALLET");
    //    myRef.setValue(walletBalance);
        tollRef=database.getReference("TOLL_NO")
                .child(user.getUid());

        pay1 = findViewById(R.id.pay1);
        pay2 = findViewById(R.id.pay2);

        TextView nice=(TextView)findViewById(R.id.nice_amount);
        niceAmount=nice.getText().toString();
        niceAmountInt= Integer.parseInt(niceAmount);

        TextView nela=(TextView)findViewById(R.id.nela_Amount);
        nelaAmount=nela.getText().toString();
        nelaAmountInt= Integer.parseInt(nelaAmount);

        pay1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                //Toast.makeText(home.this, String.valueOf(niceAmountInt),Toast.LENGTH_SHORT).show();

                myref1.child(user.getUid()).addListenerForSingleValueEvent(new ValueEventListener() {
                    @Override
                    public void onDataChange(DataSnapshot dataSnapshot) {
                        currentBalance = dataSnapshot.getValue(Integer.class);

                    }

                    @Override
                    public void onCancelled(DatabaseError databaseError) {
                    }
                });

                //Toast.makeText(home.this,String.valueOf(currentBalance),Toast.LENGTH_SHORT).show();
                if(currentBalance>=niceAmountInt)
                {
                    currentBalance=currentBalance-niceAmountInt;
                    payStatus=1;
                    tollNo=1;
                    payRef.setValue(payStatus);
                    myRef.setValue(currentBalance);
                    tollRef.setValue(tollNo);
                    Toast.makeText(home.this,"Toll PAID.. \nNew BALANCE ->"+String.valueOf(currentBalance),Toast.LENGTH_LONG).show();
                }
                else
                {
                    Toast.makeText(home.this,"MADARCHOD PAISE NHI HAI TUMHARE PASS",Toast.LENGTH_LONG).show();
                }
            }
        });

        pay2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                myref1.child(user.getUid()).addListenerForSingleValueEvent(new ValueEventListener() {
                    @Override
                    public void onDataChange(DataSnapshot dataSnapshot) {
                        currentBalance = dataSnapshot.getValue(Integer.class);

                    }

                    @Override
                    public void onCancelled(DatabaseError databaseError) {
                    }
                });

                //Toast.makeText(home.this,String.valueOf(currentBalance),Toast.LENGTH_SHORT).show();
                if(currentBalance>=nelaAmountInt)
                {
                    currentBalance=currentBalance-nelaAmountInt;
                    payStatus=1;
                    tollNo=2;
                    payRef.setValue(payStatus);
                    myRef.setValue(currentBalance);
                    tollRef.setValue(tollNo);
                    Toast.makeText(home.this,"Toll PAID.. \nNew BALANCE ->"+String.valueOf(currentBalance),Toast.LENGTH_LONG).show();
                }
                else
                {

                    Toast.makeText(home.this,"Balance Hana Illa",Toast.LENGTH_LONG).show();
                }
            }
        });



        Toolbar toolbar=(Toolbar)findViewById(R.id.mytoolbar);
        if(toolbar!=null)
        {
            setSupportActionBar(toolbar);
        }

    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        getMenuInflater().inflate(R.menu.mymenu,menu);
        return super.onCreateOptionsMenu(menu);
    }

    @Override
    public boolean onOptionsItemSelected(@NonNull MenuItem item) {

        switch(item.getItemId())
        {
            case R.id.wallet:
                myref1.child(user.getUid()).addListenerForSingleValueEvent(new ValueEventListener() {
                    @Override
                    public void onDataChange(DataSnapshot dataSnapshot) {
                        currentBalance = dataSnapshot.getValue(Integer.class);

                    }

                    @Override
                    public void onCancelled(DatabaseError databaseError) {
                    }
                });
                Toast.makeText(home.this,"WALLET SELECTED",Toast.LENGTH_SHORT).show();
                AlertDialog.Builder builder = new AlertDialog.Builder(home.this);
                builder.setMessage("WALLET BALANCE ->"+currentBalance)
                        .setPositiveButton("OK", new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {
                                // FIRE ZE MISSILES!
                            }
                        });
                AlertDialog dialog = builder.create();
                dialog.show();

                break;
            case R.id.addMoney:
                Toast.makeText(home.this,"ADD MONEY",Toast.LENGTH_SHORT).show();
                AlertDialog.Builder builder1 = new AlertDialog.Builder(home.this);
                LayoutInflater inflater = home.this.getLayoutInflater();

                builder1.setView(inflater.inflate(R.layout.mydialog, null))
                        .setPositiveButton("Add", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialog, int id) {

                                walletBalance=currentBalance+100;
                                Toast.makeText(home.this,"New Balance="+walletBalance,Toast.LENGTH_LONG).show();
                                myRef.setValue(walletBalance);
                            }
                        })
                        .setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                            public void onClick(DialogInterface dialog, int id) {

                            }
                        });
                final AlertDialog dialog1 = builder1.create();
                dialog1.show();
                break;
            case R.id.logout:
                //Toast.makeText(home.this,"LOGOUT",Toast.LENGTH_SHORT).show();
                mAuth.signOut();
                Intent intent=new Intent(home.this,user_login.class);
                startActivity(intent);
                break;
        }
        return super.onOptionsItemSelected(item);
    }
}
