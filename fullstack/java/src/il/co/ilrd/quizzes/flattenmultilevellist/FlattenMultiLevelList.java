package il.co.ilrd.quizzes.flattenmultilevellist;

import java.util.ArrayList;
import java.util.List;

//Second : Flatten a multilevel linked list
//        flattening of a multi-level linked list where nodes have two pointers down and next.
// Input:
//    1 - 2 - 3 - 4
//        |
//        7 - 8 - 10 - 12
//        |   |    |
//        9  16    11
//        |   |
//        14 17 - 18 - 19 - 20
//        |                 |
//        15 - 23           21
//             |
//             24
// Output:
// Linked List to be flattened to:
//        1 - 2 - 7 - 9 - 14 - 15 - 23 - 24 - 8
//        - 16 - 17 - 18 - 19 - 20 - 21 - 10 -
//        11 - 12 - 3 - 4

public class FlattenMultiLevelList {

    public static List<Integer> flattenMultiLevelList(Node root) {
        List<Integer> newList = new ArrayList<>();
        flattenMultiLevelList(root, newList);
        return newList;
    }

    public static void flattenMultiLevelList(Node node, List<Integer> list) {
        if (node == null) return;

        list.add(node.getData());

        flattenMultiLevelList(node.getDown(), list);
        flattenMultiLevelList(node.getNext(), list);
    }
}

class Node {
    private int data;
    private Node down;
    private Node next;

    public Node(int data) {
        this.data = data;
    }

    public int getData() {
        return data;
    }

    public Node getDown() {
        return down;
    }

    public Node getNext() {
        return next;
    }

    public void setDown(Node node) {
        down = node;
    }

    public void setNext(Node node) {
        next = node;
    }
}