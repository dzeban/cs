package com.dzyoba.alex;

import java.util.List;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Arrays;
import java.util.Random;


/**
 * Hello world!
 *
 */
public class App {
    private static final long LIST_ELEMENTS = 1_000_000;
    private static final long RANDOM_OPS = 10_000;

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

        for (int i = 0; i < testRuns; i++) {
            try {
                allocTimes[i] = testAllocation(list);
                insertTimes[i] = testInsertion(list);
                insertHeadTimes[i] = testInsertionHead(list);
                insertTailTimes[i] = testInsertionTail(list);
                searchTimes[i] = testSearching(list);
                deleteTimes[i] = testDeletion(list);
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

    private static long testAllocation(List<Integer> list) {
        long startTime = System.currentTimeMillis();
        for (int i = 0; i < LIST_ELEMENTS; i++) {
            list.add(i);
        }
        long endTime = System.currentTimeMillis();
        return endTime - startTime;
    }

    private static long testInsertion(List<Integer> list) {
        long startTime = System.currentTimeMillis();
        int index, element;
        Random randGen = new Random();
        for (int i = 0; i < RANDOM_OPS; i++) {
            index = randGen.nextInt((int)LIST_ELEMENTS);
            element = randGen.nextInt((int)LIST_ELEMENTS);
            list.add(index, element);
        }
        long endTime = System.currentTimeMillis();
        return endTime - startTime;
    }

    private static long testInsertionHead(List<Integer> list) {
        long startTime = System.currentTimeMillis();
        int element;
        Random randGen = new Random();
        for (int i = 0; i < RANDOM_OPS; i++) {
            element = randGen.nextInt((int)LIST_ELEMENTS);
            list.add(0, element);
        }
        long endTime = System.currentTimeMillis();
        return endTime - startTime;
    }

    private static long testInsertionTail(List<Integer> list) {
        long startTime = System.currentTimeMillis();
        int element;
        Random randGen = new Random();
        for (int i = 0; i < RANDOM_OPS; i++) {
            element = randGen.nextInt((int)LIST_ELEMENTS);
            list.add(element);
        }
        long endTime = System.currentTimeMillis();
        return endTime - startTime;
    }

    private static long testSearching(List<Integer> list) {
        long startTime = System.currentTimeMillis();
        int element;
        Random randGen = new Random();
        for (int i = 0; i < RANDOM_OPS; i++) {
            element = randGen.nextInt((int)LIST_ELEMENTS);
            list.indexOf(element);
        }
        long endTime = System.currentTimeMillis();
        return endTime - startTime;
    }


    private static long testDeletion(List<Integer> list) {
        long startTime = System.currentTimeMillis();
        list.clear();
        long endTime = System.currentTimeMillis();
        return endTime - startTime;
    }

    private static void printStats(String intro, long[] times) {
        Arrays.sort(times);
        int n = times.length;
        System.out.printf("%s: ", intro);
        System.out.println(Arrays.toString(times));
        //System.out.printf("%s: %d/%d/%d ms\n", intro, times[0], median(times), times[n-1]);
    }

    private static long median(long[] times) {
        int n = times.length;
        if (n % 2 == 0) {
            return (times[n/2] + times[n/2-1])/2;
        } else {
            return times[n/2];
        }
    }
}
