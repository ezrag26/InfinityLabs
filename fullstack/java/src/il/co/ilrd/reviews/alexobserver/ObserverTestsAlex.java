//package il.co.ilrd.reviews.alexobserver;
//
//import java.util.ArrayList;
//import java.util.List;
//
//public class ObserverTestsAlex {
//
//	static class ObserverImp{
//		Observer<Integer> obs = new Observer<>();
//		List<Integer> list = new ArrayList<>();
//
//		public ObserverImp() {
//			obs.setEventHandler(this::addAndPrintEmAll);
//			obs.setDeathHandler(this::tellMeDispacherDied);
//		}
//
//		private void addAndPrintEmAll(Integer s) {
//			list.add(s);
//			System.out.println("this is " + this.toString());
//			list.forEach(System.out::println);
//			System.out.println("**********************************************");
//		}
//
//		private void tellMeDispacherDied(Void v) {
//			System.out.println("this is " + this.toString() + " The dispacher just died");
//		}
//
//		public Observer<Integer> getObserver(){
//			return obs;
//		}
//	}
//
//	static class DispatcherImp{
//		private Integer cnt = 0;
//		private Dispatcher<Integer> disp = new Dispatcher<>();
//
//		public void subscribe(Observer<Integer> ob) {
//			disp.subscribe(ob);
//		}
//
//		public void unsubscribe(Observer<Integer> ob) {
//			disp.unSubscribe(ob);
//		}
//
//		 void notifyThemAll() {
//			disp.notifyAll(cnt);
//		}
//
//		public void incrCnt() {
//			++cnt;
//			notifyThemAll();
//		}
//	}
//
//
//	public static void main(String[] args) {
//		ObserverImp police = new ObserverImp();
//		ObserverImp fileFighters = new ObserverImp();
//
//		DispatcherImp EQMonitor = new DispatcherImp();
//
//		EQMonitor.subscribe(police.getObserver());
//		EQMonitor.subscribe(fileFighters.getObserver());
//
//		EQMonitor.incrCnt();
//		EQMonitor.incrCnt();
//		EQMonitor.incrCnt();
//		EQMonitor.incrCnt();
//		EQMonitor.incrCnt();
//		EQMonitor.incrCnt();
//		EQMonitor.incrCnt();
//
//		EQMonitor.unsubscribe(police.getObserver());
//
//		EQMonitor.incrCnt();
//		EQMonitor.incrCnt();
//		EQMonitor.incrCnt();
//
//		EQMonitor.unsubscribe(fileFighters.getObserver());
//
//		EQMonitor.incrCnt();
//		EQMonitor.incrCnt();
//		EQMonitor.incrCnt();
//
//	}
//
//}
