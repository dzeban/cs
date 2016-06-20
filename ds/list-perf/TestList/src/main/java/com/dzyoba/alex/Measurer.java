package com.dzyoba.alex;

public class Measurer {
    public static long measureRunsMillis(Runnable r) {
        long startTime = System.currentTimeMillis();
        r.run();
        long endTime = System.currentTimeMillis();
        return endTime - startTime;
    }
}
