Compare performance of List implementation with arrays and linked lists using
Java ArrayList and LinkedList data structures.

Tests:

1. Allocation by inserting 1 million random elements.
2. Inserting 10 000 elements in random places.
3. Searching for a 10 000 random elements.
4. Deleting 10 000 random elememnts.

```
    $ time java -cp target/TestList-1.0-SNAPSHOT.jar com.dzyoba.alex.TestList
    Testing LinkedList
    Allocation: 7/22/442 ms
    Insert: 9428/11125/23574 ms
    InsertHead: 0/1/3 ms
    InsertTail: 0/1/2 ms
    Search: 25069/27087/50759 ms
    Delete: 6/7/13 ms
    ------------------

    Testing ArrayList
    Allocation: 6/8/29 ms
    Insert: 1676/1761/2254 ms
    InsertHead: 4333/4615/5855 ms
    InsertTail: 0/0/2 ms
    Search: 9321/9579/11140 ms
    Delete: 0/1/5 ms

    real	10m31.750s
    user	10m36.737s
    sys	0m1.011s
```
