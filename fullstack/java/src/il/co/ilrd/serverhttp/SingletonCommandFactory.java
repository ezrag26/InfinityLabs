package il.co.ilrd.serverhttp;

import il.co.ilrd.command.Command;
import il.co.ilrd.factory.Factory;

public class SingletonCommandFactory {
    private static class SingletonHolder {
        private static final Factory<String, Command, Object> INSTANCE = new Factory<>();
    }

    private SingletonCommandFactory() {}

    public static Factory<String, Command, Object> getInstance() {
        return SingletonHolder.INSTANCE;
    }
}
