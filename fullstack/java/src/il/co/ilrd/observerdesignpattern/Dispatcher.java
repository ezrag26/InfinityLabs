package il.co.ilrd.observerdesignpattern;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Dispatcher<T> implements AutoCloseable {
	private List<Observer<T>> observers = new ArrayList<>();
	private boolean isClosed = false;

	@Override
	public void close() throws Exception {
		isClosed = true;
		for (Observer<T> observer : observers) {
			observer.onDispatcherDeath();
		}
	}

	public Dispatcher() {}

	public void notifyAll(T event) {
		if (isClosed) throw new IllegalStateException();
		for (Observer<T> observer : observers) {
			observer.onEvent(event);
		}
	}

	public void subscribe(Observer<T> observer) {
		Objects.requireNonNull(observer);
		if (isClosed) throw new IllegalStateException();

		if (observer.getDispatcher() != null) {
			throw new IllegalStateException("Already subscribed to a Dispatcher. Unsubscribe from this Dispatcher before subscribing to a new one");
		}

		observers.add(observer);
		observer.setDispatcher(this);

	}

	public boolean unsubscribe(Observer<T> observer) {
		Objects.requireNonNull(observer);
		if (isClosed) throw new IllegalStateException();

		if (!(observers.remove(observer))) return false;
		observer.onDispatcherDeath();

		return true;
	}
}
