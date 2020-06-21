package il.co.ilrd.command;

import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.json.JSONObject;

import java.io.IOException;
import java.io.UnsupportedEncodingException;

public class EndUserRegistration implements Command {

    public EndUserRegistration(Object o) {}

    @Override
    public boolean execute(Object o) {
        JSONObject json = (JSONObject)o;

        HttpPost post = new HttpPost("http://localhost:8082/GenericIOTCompanyDatabases/end_users");
        try {
            post.setEntity(new StringEntity(json.toString()));

            try (CloseableHttpClient client = HttpClients.createDefault();
                 CloseableHttpResponse response = client.execute(post)) {
                return response.getStatusLine().getStatusCode() == 201;
            } catch (IOException e) {
                return false;
            }
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace(); //TODO: some more relevant return value or exception
            return false;
        }
//        if (users.contains(user)) return false; //TODO: some more relevant return value or exception

//        users.add(user);

//        return true;
    }
}
