package com.dzyoba.alex;

import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Arrays;
import java.util.Random;

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
        linkedList.clear();
        System.out.println("\n------------------\n");

        System.out.println("Testing ArrayList");
        ArrayList<Integer> arrayList = new ArrayList<>();
        testList(arrayList, testRuns, listSize, randomOps);
    }

    private static void testList(List<Integer> list, int testRuns, int listSize, int randomOps) {
        long[] allocTimes, insertTimes, insertHeadTimes, insertTailTimes, searchTimes, deleteTimes;
        allocTimes = new long[testRuns];
        insertTimes = new long[testRuns];
        insertHeadTimes = new long[testRuns];
        insertTailTimes = new long[testRuns];
        searchTimes = new long[testRuns];
        deleteTimes = new long[testRuns];

        TestAlloc testAlloc = new TestAlloc(list, listSize);
        TestInsert testInsert = new TestInsert(list, randomOps);
        TestInsertHead testInsertHead = new TestInsertHead(list, randomOps);
        TestInsertTail testInsertTail = new TestInsertTail(list, randomOps);
        TestSearch testSearch = new TestSearch(list, randomOps);
        TestDelete testDelete = new TestDelete(list);

        for (int i = 0; i < testRuns; i++) {
            try {
                allocTimes[i] = Measurer.measureRunsMillis(testAlloc);
                insertTimes[i] = Measurer.measureRunsMillis(testInsert);
                insertHeadTimes[i] = Measurer.measureRunsMillis(testInsertHead);
                insertTailTimes[i] = Measurer.measureRunsMillis(testInsertTail);
                searchTimes[i] = Measurer.measureRunsMillis(testSearch);
                deleteTimes[i] = Measurer.measureRunsMillis(testDelete);
            } catch (Exception E) {
            }
        }
        printStats("Allocation", allocTimes);
        printStats("Insert", insertTimes);
        printStats("InsertHead", insertHeadTimes);
        printStats("InsertTail", insertTailTimes);
        printStats("Search", searchTimes);
        printStats("Delete", deleteTimes);
    }

    private static void printStats(String intro, long[] times) {
        Arrays.sort(times);
        System.out.println(intro + ": " + Arrays.toString(times));
    }
}
