package com.dzyoba.alex;

import java.util.LinkedHashMap;
import java.util.Map;

/**
 * Measure test run
 */
public class Measurer {
    /**
     * Take runnable and wrap it with counters to measure running time
     */
    public static long measureRunsMillis(Runnable r) {
        long startTime = System.currentTimeMillis();
        r.run();
        long endTime = System.currentTimeMillis();
        return endTime - startTime;
    }

    /**
     * Measure sequence of tests from *ordered* map (LinkedHashMap)
     */
    public static void measureTestMap(LinkedHashMap<Runnable, long[]> testMap, int runs) {
        for (int i = 0; i < runs; i++) {
            for (Map.Entry<Runnable, long[]> e : testMap.entrySet()) {
                Runnable test = e.getKey();
                long[] times = e.getValue();
                times[i] = measureRunsMillis(test);
            }
        }
    }
}
