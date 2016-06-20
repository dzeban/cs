package com.dzyoba.alex;

import java.util.List;

public class TestAlloc implements Runnable {
    private List<Integer> list;
    private int listSize;

    public TestAlloc(List<Integer> list, int listSize) {
        this.list = list;
        this.listSize = listSize;
    }

    public void run() {
        for (int i = 0; i < listSize; i++) {
            list.add(i);
        }
    }
}
