package il.co.ilrd.quizzes.aftermediakindinterviewquiz;

import org.junit.jupiter.api.Test;

import java.util.Arrays;

import static org.junit.jupiter.api.Assertions.*;

class MediaKindInterviewQuestionsTest {
	@Test
	public void test() {
		System.out.println(MediaKindInterviewQuestions.reverseString("Hello    nice day"));

		int[] nums = {1, 0, 1, 1, 0, 0, 0, 1};
		System.out.println(Arrays.toString(MediaKindInterviewQuestions.sortZeroOne(nums)));

		int[] numArray = {5, 1, 8, 3, 8, 9, 2, 10, 15};
		System.out.println(Arrays.toString(MediaKindInterviewQuestions.findTripletSum(14, numArray)));
		System.out.println(Arrays.toString(MediaKindInterviewQuestions.findTripletSum(100, numArray)));
	}
}