package il.co.ilrd.enums;

import org.junit.jupiter.api.Test;

public class EWeekDayTest {

	@Test
	public void enums() {
		EWeekDay sunday = EWeekDay.valueOf("SUNDAY");
		System.out.println(sunday);

		String sundayString = sunday.name();
		System.out.println(sundayString);

		int sundayOrdinal = sunday.ordinal();
		System.out.println(sundayOrdinal);

		EWeekDay[] daysOfWeek = EWeekDay.values();
		for (int i = 1; i < daysOfWeek.length; ++i) {
			System.out.println(daysOfWeek[i - 1].compareTo(daysOfWeek[i]));
		}

		for (int i = 0; i < daysOfWeek.length; ++i) {
			System.out.print("getDeclaringClass: " + daysOfWeek[i].getDeclaringClass() + " : ");
			System.out.print("name: " + daysOfWeek[i].name() + " : ");
			System.out.print("ordinal: " + daysOfWeek[i].ordinal() + " : ");
			System.out.print("getValueOfDay: " + daysOfWeek[i].getValue() + " : ");
			System.out.print("toString: " + daysOfWeek[i].toString() + " : ");
			System.out.println("valueOf: " + EWeekDay.valueOf(daysOfWeek[i].toString()));
			System.out.println(EWeekDay.fromValue(i));
		}

		for (EWeekDay day: EWeekDay.values()) {
			System.out.println(day);
		}



	}

}