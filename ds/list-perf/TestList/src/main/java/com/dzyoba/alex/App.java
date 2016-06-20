package com.dzyoba.alex;

import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Arrays;
import java.util.Random;

public class App {
    private static final int LIST_ELEMENTS = 10_000;
    private static final int RANDOM_OPS = 100;

    public static void main(String[] args) {
        System.out.printf("Testing with %d elements, %d random ops\n", LIST_ELEMENTS, RANDOM_OPS);
        System.out.println("Testing LinkedList");
        LinkedList<Integer> linkedList = new LinkedList<>();
        testList(linkedList, 10);
        linkedList.clear();
        System.out.println("------------------\n");

        System.out.println("Testing ArrayList");
        ArrayList<Integer> arrayList = new ArrayList<>();
        testList(arrayList, 10);
    }

    private static void testList(List<Integer> list, int testRuns) {
        long[] allocTimes, insertTimes, insertHeadTimes, insertTailTimes, searchTimes, deleteTimes;
        allocTimes = new long[testRuns];
        insertTimes = new long[testRuns];
        insertHeadTimes = new long[testRuns];
        insertTailTimes = new long[testRuns];
        searchTimes = new long[testRuns];
        deleteTimes = new long[testRuns];

        TestAlloc testAlloc = new TestAlloc(list, LIST_ELEMENTS);
        TestInsert testInsert = new TestInsert(list, RANDOM_OPS);
        TestInsertHead testInsertHead = new TestInsertHead(list, RANDOM_OPS);
        TestInsertTail testInsertTail = new TestInsertTail(list, RANDOM_OPS);
        TestSearch testSearch = new TestSearch(list, RANDOM_OPS);
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
