package il.co.ilrd.worksheets.ws1.ex5;

public class RecursiveFrameMain {
	public static void main(String[] args) {

		int counter_not_static = 0;
		int counter_static = 0;

		RecursiveFrameMain not_static_instance = new RecursiveFrameMain();

		System.out.println("notStaticCountFrame");
		counter_not_static = not_static_instance.notStaticCountFrame(counter_not_static);
		System.out.println(counter_not_static);

		System.out.println("-------------------------------");

		System.out.println("staticCountFrame");
		counter_static = RecursiveFrameMain.staticCountFrame(counter_static);
		System.out.println(counter_static);
	}

	int notStaticCountFrame(int counter_not_static) {

		if (counter_not_static == 10)
		{
			return (counter_not_static);
		}

		System.out.println(counter_not_static);

		return (notStaticCountFrame(counter_not_static + 1));
	}

	static int staticCountFrame(int counter_static) {

		if (counter_static == 10)
		{
			return (counter_static);
		}

		System.out.println(counter_static);

		return (staticCountFrame(counter_static + 1));
	}
}
