package il.co.ilrd.reviews.alexobserver;

import org.junit.jupiter.api.Test;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

import static org.junit.jupiter.api.Assertions.*;

class ObserverDesignPatternTest {

	Consumer<String> eventHandler = new Consumer<String>() {
		@Override
		public void accept(String s) {
			switch (s) {
				case "Earthquake":
					System.out.println("An Earthquake has occurred");
					break;
				case "Tsunami":
					System.out.println("A Tsunami has occurred");
					break;
				case "Hurricane":
					System.out.println("A Hurricane has occurred");
					break;
				default:
					System.out.println("Crisis: Unknown disaster!");
			}
		}
	};

	Consumer<Void> deathHandler = new Consumer<Void>() {
		@Override
		public void accept(Void aVoid) {
			System.out.println("Dispatcher is no longer signaling...");
		}
	};

	@Test
	public void testObserverOnEvent() {

		Observer<String> police = new Observer<>(eventHandler, deathHandler);
		police.onEvent("Earthquake");
		police.onEvent("Tsunami");
		police.onEvent("Hurricane");
		police.onEvent("Unknown disaster");
	}

	@Test
	public void testObserverSubscribe() {
		Observer<String> police = new Observer<>(eventHandler, deathHandler);
		Observer<String> hospital = new Observer<>(eventHandler, deathHandler);
		DispatcherFix<String> crisis = new DispatcherFix<>();

		crisis.subscribe(police);
		assertNotNull(police.getDispatcher());
		crisis.subscribe(hospital);
		assertNotNull(hospital.getDispatcher());


		crisis.notifyAll("Earthquake");
		crisis.notifyAll("Tsunami");
		crisis.notifyAll("Hurricane");
		crisis.notifyAll("Unknown disaster");
	}

	@Test
	public void testObserverUnsubscribe() {
		Observer<String> police = new Observer<>(eventHandler, deathHandler);
		Observer<String> hospital = new Observer<>(eventHandler, deathHandler);
		DispatcherFix<String> crisis = new DispatcherFix<>();

		crisis.subscribe(hospital);
		crisis.subscribe(police);

		crisis.unSubscribe(hospital);
		assertNull(hospital.getDispatcher());

		crisis.notifyAll("Earthquake");
		crisis.notifyAll("Tsunami");
		crisis.notifyAll("Hurricane");
		crisis.notifyAll("Unknown disaster");

		crisis.unSubscribe(police);
		assertNull(police.getDispatcher());

	}

	@Test
	public void testObserverClose() throws Exception {
		Observer<String> police = new Observer<>(eventHandler, deathHandler);
		Observer<String> hospital = new Observer<>(eventHandler, deathHandler);
		DispatcherFix<String> crisis = new DispatcherFix<>();

		crisis.subscribe(hospital);
		crisis.subscribe(police);

		crisis.notifyAll("Earthquake");
		crisis.notifyAll("Tsunami");
		crisis.notifyAll("Hurricane");
		crisis.notifyAll("Unknown disaster");

		crisis.close();
	}

	@Test
	public void testSubscribeBeforeUnsubscribe() throws Exception {
		Observer<String> police = new Observer<>(eventHandler, deathHandler);
		Observer<String> hospital = new Observer<>(eventHandler, deathHandler);
		DispatcherFix<String> crisis = new DispatcherFix<>();
		DispatcherFix<String> crisis1 = new DispatcherFix<>();

		crisis.subscribe(hospital);
		crisis.subscribe(police);
		assertThrows(IllegalStateException.class, () -> crisis.subscribe(police));
		assertThrows(IllegalStateException.class, () -> crisis1.subscribe(police));

		crisis.notifyAll("Earthquake");
		crisis.notifyAll("Tsunami");
		crisis.notifyAll("Hurricane");
		crisis.notifyAll("Unknown disaster");

		crisis.close();
	}

	@Test
	public void testRescueTeam() throws Exception {
		Crisis<String> earthquake = new Crisis<>();
		Crisis<String> hurricane = new Crisis<>();
		Crisis<String> tsunami = new Crisis<>();
		RescueTeam<String> police = new RescueTeam<>();
		RescueTeam<String> hospital = new RescueTeam<>();
		Consumer<String> eventHandler = new Consumer<String>() {
			@Override
			public void accept(String s) {
				police.doThis(s);
			}
		};

		Consumer<Void> deathHandler = new Consumer<>() {
			@Override
			public void accept(Void aVoid) {
				police.deathMethod();
			}
		};

		police.addObserver(earthquake, eventHandler, deathHandler);
		police.addObserver(hurricane, eventHandler, deathHandler);
		police.addObserver(tsunami, eventHandler, deathHandler);
		hospital.addObserver(earthquake, eventHandler, deathHandler);
		hospital.addObserver(hurricane, eventHandler, deathHandler);
		hospital.addObserver(tsunami, eventHandler, deathHandler);


		earthquake.sendMessage("Earthquake of 7.7");
		tsunami.sendMessage("Tsunami coming in on west coast");
		hurricane.sendMessage("Level 3 hurricane on its way");
		earthquake.sendMessage("Minor earthquake of 1.4 felt");
		tsunami.sendMessage("WARNING! Tsunami about to hit");
		hurricane.sendMessage("Hurricane is gradually getting smaller");

		earthquake.close();
		tsunami.close();
		hurricane.close();
	}

	class RescueTeam<T> {
		List<Observer<T>> observers = new ArrayList<>();

		public RescueTeam() {}

		public void addObserver(Crisis<T> crisis, Consumer<T> eventHandler, Consumer<Void> deathHandler) {
			Observer<T> observer = new Observer<>(eventHandler, deathHandler);
			crisis.getDispatcher().subscribe(observer);
			observers.add(observer);
		}

		public boolean removeObserver(Crisis<T> crisis, Observer<T> observer) {
			if (crisis.getDispatcher().unSubscribe(observer)) {
				return observers.remove(observer);
			}
			return false;
		}

		public void doThis(String s) {
			System.out.println("Received update of " + s);
		}

		public void deathMethod() {
			System.out.println("Dispatcher no longer signaling...");
		}
	}

	class Crisis<T> {
		DispatcherFix<T> dispatcher = new DispatcherFix<>();

		public Crisis() {

		}

		public void sendMessage(T event) {
			dispatcher.notifyAll(event);
		}

		public void close() throws Exception {
			dispatcher.close();
		}

		public DispatcherFix<T> getDispatcher() {
			return this.dispatcher;
		}
	}
}