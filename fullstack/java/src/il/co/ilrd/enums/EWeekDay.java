package il.co.ilrd.enums;

public enum EWeekDay {
	SUNDAY /*(1)*/,
	MONDAY /*(2)*/,
	TUESDAY /*(3)*/,
	WEDNESDAY /*(4)*/,
	THURSDAY /*(5)*/,
	FRIDAY /*(6)*/,
	SATURDAY /*(7)*/;

	private static EWeekDay[] weekDays = EWeekDay.values();
//	final int value;

//	EWeekDay(int value) {
//		this.value = value;
//	}

	public int getValue() {
		return this.ordinal();
	}

	public static EWeekDay fromValue(int value) {
		return weekDays[value];
	}

	public static void printValues() {
		for (EWeekDay day: weekDays) {
			System.out.println(day);
		}
	}
}