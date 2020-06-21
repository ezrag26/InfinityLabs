package il.co.ilrd.threadcountdictionarybyletters;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class DictionaryCountLetters {
	/**
	 * Uppercase characters are counted as lowercase.
	 * 27 letters = 26 letters in alphabet + 1 for characters not in alphabet.
	 */
	static final int LETTERS = 27;

	public static void main(String[] args) throws IOException, InterruptedException {
		long[] avgExecutionTimePerNumOfThreads = new long[101];
		final int LOADS = 300;
		final int THREADS = 20;
		final int TIMES_TO_RUN = 1000;
		final File dictionaryPath = new File("/usr/share/dict/words");

		for (int numOfDictionaryLoads = 1; numOfDictionaryLoads < LOADS; numOfDictionaryLoads += 50) {
			long totalExecution = 0;
			ArrayList<String> dictArray = new ArrayList<>();

			/* add all words in the dictionary for specified amount of times */
			for (int i = 0; i < numOfDictionaryLoads; ++i) {
				createDictionaryArray(dictionaryPath, dictArray);
			}
			Collections.shuffle(dictArray); /* shuffle words in the array */

			for (int numOfThreads = 1; numOfThreads < THREADS; ++numOfThreads) {

				long executionTimeForThreadAmount = 0;
				int chunkSize = calculateChunkSize(dictArray, numOfThreads);

				for (int z = 0; z < TIMES_TO_RUN; ++z) {

					ArrayList<int[]> retrievedThreadLUTs = new ArrayList<>();
					ArrayList<Thread> threads = new ArrayList<>();
					ArrayList<CountLettersRunnable> runnables = new ArrayList<>();

					/**
					 * create runnables to be sent to the threads, each with their proper
					 * ranges of words to work on
					 */
					for (int i = 0; i < numOfThreads - 1; ++i) {
						runnables.add(new CountLettersRunnable(dictArray, (i * chunkSize), (i * chunkSize) + chunkSize));
					}
					runnables.add(new CountLettersRunnable(dictArray, ((numOfThreads - 1) * chunkSize), dictArray.size()));

					for (int i = 0; i < numOfThreads; ++i) {
						threads.add(new Thread(runnables.get(i)));
					}

					long start = System.nanoTime();

					for (int i = 0; i < numOfThreads; ++i) {
						threads.get(i).start();
					}

					for (int i = 0; i < numOfThreads; ++i) {
						threads.get(i).join();
					}

					for (int i = 0; i < numOfThreads; ++i) {
						retrievedThreadLUTs.add(runnables.get(i).getThreadLUT());
					}

					int[] finalCountLUT = new int[LETTERS];
					for (int i = 0; i < numOfThreads; ++i) {
						for (int j = 0; j < LETTERS; ++j) {
							finalCountLUT[j] += retrievedThreadLUTs.get(i)[j];
						}
					}
					long end = System.nanoTime();
					totalExecution = end - start;
					executionTimeForThreadAmount += totalExecution;

//					int totalSum = 0;
//					for (int i = 0; i < LETTERS; ++i) {
//						//					System.out.println((char) (i + 'a') + ": " + finalCountLUT[i]);
//						totalSum += finalCountLUT[i];
//					}

					//				System.out.println("Total letters: " + totalSum);
					//				System.out.println("Milliseconds: " + totalExecution / 1_000_000);
					//		printDictionaryArray(dictArray);
				}
				avgExecutionTimePerNumOfThreads[numOfThreads] += ((executionTimeForThreadAmount / TIMES_TO_RUN) / 1_000_000);

				System.out.print("Dictionaries: " + numOfDictionaryLoads);
				System.out.print(" || Threads: " + numOfThreads);
				System.out.println(" || Avg execution time: " + avgExecutionTimePerNumOfThreads[numOfThreads] + "ms\n");
			}
		}

		for (int i = 1; i < THREADS; ++i) {
			System.out.println("Avg for " + i + " threads " + avgExecutionTimePerNumOfThreads[i]);
		}
	}

	static void createDictionaryArray(File dictionaryPath, List<String> dictArray) throws IOException {
		BufferedReader bufferedReader = new BufferedReader(new FileReader(dictionaryPath));
		String word;

		while ((word = bufferedReader.readLine()) != null) {
			dictArray.add(word.toLowerCase());
		}
		bufferedReader.close();
	}

	static int calculateChunkSize(List<String> dictArray, int numOfThreads) {
		return dictArray.size() / numOfThreads;
	}

	static void printDictionaryArray(List<String> dictArray) {
		for (String word : dictArray) {
			System.out.println(word);
		}
	}

	static class CountLettersRunnable implements Runnable {
		int startIndex;
		int endIndex;
		List<String> dictArray;

		public CountLettersRunnable(List<String> dictArray, int startIndex, int endIndex) {
			this.dictArray = dictArray;
			this.startIndex = startIndex;
			this.endIndex = endIndex;
		}

		private int[] threadLUT = new int[27];

		public int[] getThreadLUT() {
			return threadLUT;
		}

		@Override
		public void run() {
			for (int i = startIndex; i < endIndex; ++i) {
				for (int j = 0; j < dictArray.get(i).length(); ++j) {
					int ch = dictArray.get(i).charAt(j) - 'a';
					if (ch >= 0 && ch <= 25) {
						threadLUT[ch] += 1;
					} else {
						threadLUT[(LETTERS - 1)] += 1;
					}
				}
			}
		}
	}
}
