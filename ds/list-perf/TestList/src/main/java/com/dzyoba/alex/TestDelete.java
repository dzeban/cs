package com.dzyoba.alex;

import java.util.List;

public class TestDelete implements Runnable {
    private List<Integer> list;

    public TestDelete(List<Integer> list) {
        this.list = list;
    }

    public void run() {
        list.clear();
    }
}
