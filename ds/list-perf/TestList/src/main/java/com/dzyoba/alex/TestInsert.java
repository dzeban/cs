package com.dzyoba.alex;

import java.util.List;
import java.util.Random;

public class TestInsert implements Runnable {
    private List<Integer> list;
    private int listSize;
    private int randomOps;

    public TestInsert(List<Integer> list, int randomOps) {
        this.list = list;
        this.randomOps = randomOps;
    }

    public void run() {
        int index, element;
        int listSize = list.size();
        Random randGen = new Random();
        for (int i = 0; i < randomOps; i++) {
            index = randGen.nextInt((int)listSize);
            element = randGen.nextInt((int)listSize);
            list.add(index, element);
        }
    }
}
