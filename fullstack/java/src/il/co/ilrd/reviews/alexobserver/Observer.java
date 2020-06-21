package il.co.ilrd.reviews.alexobserver;

import java.util.Objects;
import java.util.function.Consumer;

public class Observer<T> {
    private DispatcherFix<T> dispatcher;
    private Consumer<T> eventHandler;
    private Consumer<Void> deathHandler;

    public Observer() {
    }
    
    public Observer(Consumer<T> eventHandler, Consumer<Void> deathHandler) {
    	this.eventHandler = Objects.requireNonNull(eventHandler); 
    	this.deathHandler = Objects.requireNonNull(deathHandler); 
    }
    
    public Observer(Consumer<T> eventHandler) {
    	this(eventHandler, (s)->{});
    }

    void setDispatcher(DispatcherFix<T> dispatcher) {
    	this.dispatcher = dispatcher; 
    }

    void onEvent(T event) {
    	eventHandler.accept(event);
    }

    void onDispatcherDeath() {
    	deathHandler.accept(null);
    	dispatcher = null;
    }

    public void setEventHandler(Consumer<T> eventHandler) {
    	this.eventHandler = Objects.requireNonNull(eventHandler); 
    }

    public void setDeathHandler(Consumer<Void> deathHandler) {
    	this.deathHandler = Objects.requireNonNull(deathHandler); 
    }

    public DispatcherFix<T> getDispatcher() {
    	return dispatcher;
    }
}
