package il.co.ilrd.serverhttp;

import com.sun.net.httpserver.HttpExchange;
import com.sun.net.httpserver.HttpHandler;
import il.co.ilrd.command.Command;
import il.co.ilrd.factory.Factory;
import org.json.JSONObject;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.concurrent.Executors;
import java.util.concurrent.ThreadPoolExecutor;

class RequestHandler implements HttpHandler {
    private final Factory<String, Command, Object> factory;
    private final ThreadPoolExecutor executor = (ThreadPoolExecutor) Executors.newFixedThreadPool(2);

    public RequestHandler(Factory<String, Command, Object> factory) {
        this.factory = factory;
    }

    @Override
    public void handle(HttpExchange exchange) {
        executor.execute(() -> {
            try (InputStream requestBody = exchange.getRequestBody()) {
                /* create JSON object from request body */
                String body = new String(requestBody.readAllBytes());
                JSONObject json = new JSONObject(body);

                /* get type from request */
                String type = (String)json.remove("type");
                if (type == null) sendErrorResponse(exchange, "syntax");

                try {
                    /* create command */
//                        Command cmd = factory.create("command", type);
                    Command cmd = factory.create(type, null);

                    /* execute request */
                    boolean executedSuccessfully = cmd.execute(json);

                    sendResponse(exchange, executedSuccessfully);

                    /* log request */
                    factory.create("writelog", null).execute(type + " request handled.");
                } catch (IllegalArgumentException e) {
                    sendErrorResponse(exchange, "unknown type");
                }
            } catch (IOException e) {
                //TODO: what to do if exception is thrown
                e.printStackTrace();
            }
        });
    }

    private void sendResponse(HttpExchange exchange, boolean retVal) throws IOException {
        JSONObject responseBody = new JSONObject();

        /* add status field to response body */
        responseBody.put("status", retVal);

        int statusCode = retVal ? 201 : 400;

        sendResponse(exchange, statusCode, responseBody.toString());
    }

    private void sendErrorResponse(HttpExchange exchange, String error) throws IOException {
        JSONObject responseBody = new JSONObject();

        /* add status field to response body */
        responseBody.put("status", false);

        int statusCode;

        switch (error) {
            case "unknown type":
                responseBody.put("message", "Unknown \"type\"");
                statusCode = 422;
                break;
            case "syntax":
                responseBody.put("message", "Invalid syntax: missing \"type\"");
            default:
                statusCode = 400;
        }

        sendResponse(exchange, statusCode, responseBody.toString());
    }

    private void sendResponse(HttpExchange exchange, int statusCode, String response) throws IOException {
        exchange.getResponseHeaders().set("Content-Type", "application/json");
        exchange.sendResponseHeaders(statusCode, response.length());
        try (OutputStream outputStream = exchange.getResponseBody()) {
            outputStream.write(response.getBytes());
            outputStream.flush();
        }
    }
}