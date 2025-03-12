package com.wanwire.libxraygo;

public class XrayGo {
    static {
        try {
            System.loadLibrary("xray-go-android");
            System.loadLibrary("xray-jni");
        } catch(Exception exception) {
            System.out.println(exception.getMessage());
	    throw exception;
        }
    }
    public native long libxrayMain(int argc, String[] argv, int envc, String[] envv);
}
