package com.ilong.jnidemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        //Test
        Student student = new Student();
        student.setName("ilong");
        Log.d(TAG, "name: "+student.getName());
        student.setGrade(101);
        Log.d(TAG, "grade: "+student.getGrade());
        student.asynGetName(new Student.Callback() {
            @Override
            public void onResponse(String resp) {
                Log.d(TAG, "asynGetName: "+resp);
            }
        });
        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(Student.printClassName()+" "+student.print());
    }
}
