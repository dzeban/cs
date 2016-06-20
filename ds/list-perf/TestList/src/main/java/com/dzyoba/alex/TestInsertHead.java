package com.dzyoba.alex;

import java.util.List;
import java.util.Random;

public class TestInsertHead implements Runnable {
    private List<Integer> list;
    private int randomOps;

    public TestInsertHead(List<Integer> list, int randomOps) {
        this.list = list;
        this.randomOps = randomOps;
    }

    public void run() {
        int element;
        int listSize = list.size();
        Random randGen = new Random();
        for (int i = 0; i < randomOps; i++) {
            element = randGen.nextInt(listSize);
            list.add(0, element);
        }
    }
}
