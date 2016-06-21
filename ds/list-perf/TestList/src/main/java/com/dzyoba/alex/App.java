package com.dzyoba.alex;

import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Arrays;
import java.util.Random;
import java.util.LinkedHashMap;
import java.util.Map;

public class App {
    public static void main(String[] args) {
        if (args.length != 3) {
            System.out.println("Usage: App <list size> <random ops> <test runs>");
            System.exit(1);
        }

        int listSize = Integer.parseInt(args[0]);
        int randomOps = Integer.parseInt(args[1]);
        int testRuns = Integer.parseInt(args[2]);

        System.out.println("Testing LinkedList");
        LinkedList<Integer> linkedList = new LinkedList<>();
        testList(linkedList, testRuns, listSize, randomOps);

        System.out.println("\n------------------\n");

        System.out.println("Testing ArrayList");
        ArrayList<Integer> arrayList = new ArrayList<>();
        testList(arrayList, testRuns, listSize, randomOps);
    }

    /**
     * Test particular list implementation
     */
    private static void testList(List<Integer> list, int testRuns, int listSize, int randomOps) {
        // LinkedHashMap stores *ordered* collection of tests to run in sequence
        // with arrays of running times for each test
        LinkedHashMap <Runnable, long[]> measureMap = new LinkedHashMap<>();
        measureMap.put(new TestAlloc(list, listSize), new long[testRuns]);
        measureMap.put(new TestInsert(list, randomOps), new long[testRuns]);
        measureMap.put(new TestInsertHead(list, randomOps), new long[testRuns]);
        measureMap.put(new TestInsertTail(list, randomOps), new long[testRuns]);
        measureMap.put(new TestSearch(list, randomOps), new long[testRuns]);
        measureMap.put(new TestDelete(list), new long[testRuns]);

        Measurer.measureTestMap(measureMap, testRuns);

        printStats(measureMap);
    }

    private static void printStats(LinkedHashMap<Runnable, long[]> testMap) {
        for (Map.Entry<Runnable, long[]> e : testMap.entrySet()) {
            Runnable test = e.getKey();
            long[] times = e.getValue();
            Arrays.sort(times);
            System.out.println(test.getClass().getName() + ": " + Arrays.toString(times));
        }
    }
}
