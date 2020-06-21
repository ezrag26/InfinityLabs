package il.co.ilrd.reviews.alexobserver;

import java.util.LinkedList;
import java.util.List;
import java.util.Objects;

public class DispatcherFix<T> implements AutoCloseable {
    private List<Observer<T>> observers = new LinkedList<>();
    private boolean isClosed = false;

    /****
     * FIXME Subscribe should first check if the current observer is already subscribed to a Dispatcher, and if it is, should throw something like an IllegalStateException
     * FIXME Also, you should update the observers Dispatcher when it successfully subscribes to the Dispatcher
     ****/
    public void subscribe(Observer<T> observer) {
    	requireNotClosed();
    	Objects.requireNonNull(observer);
    	observers.add(observer);
    }

    /****
     * FIXME Should return boolean checking if it was successfully removed or not - also, if it does remove it, you should set the observer's Dispatcher to null
     * FIXME I think this should also require observer to not be null and check if isClosed is true or not
     ****/
    public boolean unSubscribe(Observer<T> observer) {
    	observer.onDispatcherDeath();
    	return observers.remove(observer);
    }

    public void notifyAll(T event) {
    	requireNotClosed();
    	
    	for (Observer<T> ob: observers) {
    		ob.onEvent(event);
    	}
    }

    @Override
    public void close() throws Exception {
    	isClosed = true;
    	    	
    	for (Observer<T> ob: observers) {
    		ob.onDispatcherDeath();
    	}
    	
    	observers.clear();
    }
    
    private void requireNotClosed() {
    	if (isClosed) {
    		throw new IllegalStateException();
    	}
    }
}
