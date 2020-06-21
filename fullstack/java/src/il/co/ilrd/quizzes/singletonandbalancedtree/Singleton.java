package il.co.ilrd.quizzes.singletonandbalancedtree;

// A design pattern that limits a class to be instantiated no more than once.
// All references point to the same instance, so changing its state will change
// all reference to the instance

// Creates instance on first call to getInstance as it loads the static class
class OnDemandSingleton {
    private static class OnDemandSingletonHolder {
        private static final OnDemandSingleton INSTANCE = new OnDemandSingleton();
    }

    private OnDemandSingleton() {}

    public OnDemandSingleton getInstance() {
        return OnDemandSingletonHolder.INSTANCE;
    }
}

// Creates instance at class loading
class EagerSingleton {
    private static final EagerSingleton INSTANCE = new EagerSingleton();

    private EagerSingleton() {}

    public EagerSingleton getInstance() {
        return INSTANCE;
    }

}

// create instance if not already created, otherwise return instance.
// Not thread safe
class LazyInitializationSingleton {
    private LazyInitializationSingleton instance;

    private LazyInitializationSingleton() {}

    public LazyInitializationSingleton getInstance() {
        if (instance == null) {
            instance = new LazyInitializationSingleton();
        }
        return instance;
    }
}

// Checks if the instance is null, synchronizes on the class object, checks again
// if the instance is still not created, then creates it.
// If at any point instance is not null, it has already been created, so return
// the instance. This allows for thread safe singleton creation
class DoubleCheckSingleton {

    private DoubleCheckSingleton instance;

    private DoubleCheckSingleton() {}
    public DoubleCheckSingleton getInstance() {
        if (instance == null) {
            synchronized (DoubleCheckSingleton.class) {
                if (instance == null) {
                    instance = new DoubleCheckSingleton();
                }
            }
        }
        return instance;
    }

}

// enums already have just one place in memory, so by default are singleton-y
enum SingletonEnum {
    INSTANCE
}

/* ************************************************************************** */
class BalancedTree {
    private boolean isBalanced(Node root) {
        if (root == null) return true;

        int leftHeight = getHeight(root.getLeft());
        int rightHeight = getHeight(root.getRight());
        int height = leftHeight - rightHeight;

        return height > -2 && height < 2 &&
                isBalanced(root.getLeft()) &&
                isBalanced(root.getRight());
    }

    private int getHeight(Node node) {
        if (node == null) return 0;

        return 1 + Integer.max(getHeight(node.getLeft()), getHeight(node.getRight()));
    }
}

class Node {
    private int data;
    private Node left;
    private Node right;

    public Node(int data) {
        this.data = data;
    }

    public Node getLeft() {
        return left;
    }

    public Node getRight() {
        return right;
    }
}