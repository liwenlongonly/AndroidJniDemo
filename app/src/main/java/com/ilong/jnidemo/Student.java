package com.ilong.jnidemo;

/**
 * Created by ilong on 2018/3/17.
 */

public class Student {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    public interface Callback{
        public void onResponse(String resp);
    }

    private long mNativeStudent = -1;

    private final String TAG = "Student";

    public Student() {
        mNativeStudent = CreateStudent();
    }

    public void setName(String name) {
        SetName(name);
    }

    public String getName() {
        return GetName();
    }

    public void asynGetName(Callback callback){
        AsynGetName(callback);
    }

    public void setGrade(int grade) {
        SetGrade(grade);
    }

    public int getGrade() {
        return GetGrade();
    }

    public String print() {
        return Print();
    }

    public static String printClassName() {
        return PrintClassName();
    }

    @Override
    protected void finalize() throws Throwable {
        DestoryStudent(mNativeStudent);
        super.finalize();
    }

    private native long CreateStudent();

    private native void DestoryStudent(long nativeStuent);

    private native void SetName(String name);

    private native String GetName();

    private native void AsynGetName(Object callback);

    private native void SetGrade(int grade);

    private native int GetGrade();

    private native String Print();

    private static native String PrintClassName();
}
