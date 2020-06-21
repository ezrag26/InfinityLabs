package il.co.ilrd.observerdesignpattern;

import java.util.Objects;
import java.util.function.Consumer;

public class Observer<T> {
	private Dispatcher<T> dispatcher;
	private Consumer<T> eventHandler;
	private Consumer<Void> deathHandler;

	public Observer(Consumer<T> eventHandler, Consumer<Void> deathHandler) {
		this.eventHandler = Objects.requireNonNull(eventHandler);
		this.deathHandler = Objects.requireNonNull(deathHandler);
	}

	void onEvent(T event) { eventHandler.accept(event); }

	void setDispatcher(Dispatcher<T> dispatcher) {
		this.dispatcher = dispatcher;
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

	public Dispatcher<T> getDispatcher() { return dispatcher; }

}
