package il.co.ilrd.crud.filecrud;

import il.co.ilrd.crud.Crud;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class FileCrud implements Crud<Integer, String> {
	private BufferedWriter outputStream;
	private Integer key = 0;
	private final Map<Integer, String> rows = new HashMap<>();

	/**
	 * Creates a new FileCrud object.
	 *
	 * @param outFilePath the path to the file of which to work on
	 * @throws IOException  if the named file exists but is a directory rather
	 *                      than a regular file, does not exist but cannot be
	 *                      created, or cannot be opened for any other reason
	 */
	public FileCrud(String outFilePath) throws IOException {
		outputStream = new BufferedWriter(new FileWriter(outFilePath, true));
	}

	/**
	 * Appends the given data to this FileCrud.
	 *
	 * @param data the data to be appended
	 * @return the key to which the data is associated with
	 */
	@Override
	public Integer create(String data) {
		try {
			/* write the new data and flush stream to make sure everything is written */
			outputStream.write(data + System.lineSeparator());
			outputStream.flush();

			rows.put(++key, data);

			return key;
		} catch (IOException ignored) {}

		return null;
	}

	/**
	 * Gets the value associated with the given key.
	 *
	 * @param key the key of the value to be read
	 * @return the value associated with the given key
	 *
	 * @throws UnsupportedOperationException
	 */
	@Override
	public String read(Integer key) { throw new UnsupportedOperationException(); }

	/**
	 * Updates the value of the given key.
	 *
	 * @param key the key of the value to update
	 * @param data the new value to be associated with the given key
	 * @return the value associated with this key before updating to new value
	 *
	 * @throws UnsupportedOperationException
	 */
	@Override
	public String update(Integer key, String data) { throw new UnsupportedOperationException(); }

	/**
	 * Deletes the key and value associated with the given key.
	 *
	 * @param key the key to delete
	 * @return the value associated with the given key
	 *
	 * @throws UnsupportedOperationException
	 */
	@Override
	public String delete(Integer key) { throw new UnsupportedOperationException(); }

	/**
	 * Closes the opened files.
	 *
	 * @throws Exception
	 */
	@Override
	public void close() throws Exception { outputStream.close(); }
}
