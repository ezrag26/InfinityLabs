package il.co.ilrd.chatserver;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ClientProtocolV1 implements Protocol {
    private String STX = "\002", ETX = "\003", DC1 = "\021", US = "\037";
    private String version = "v1";
    private String userID;

    public static final String ANSI_RESET = "\u001B[0m";
    public static final String ANSI_BLACK = "\u001B[30m";
    public static final String ANSI_RED = "\u001B[31m";
    public static final String ANSI_GREEN = "\u001B[32m";
    public static final String ANSI_YELLOW = "\u001B[33m";
    public static final String ANSI_BLUE = "\u001B[34m";
    public static final String ANSI_PURPLE = "\u001B[35m";
    public static final String ANSI_CYAN = "\u001B[36m";
    public static final String ANSI_WHITE = "\u001B[37m";

    @Override
    public String encode(String action, String content) {
        /* FORMAT: action: content */
        Pattern pattern = Pattern.compile("([a-z])+(: )(.)+");
        Matcher matcher = pattern.matcher(content);
        if (!matcher.matches()) return null;

        String[] strings = content.split(": ");
        String userAction;

        switch (strings[0]) {
            case "create":
                userAction = "2";
                break;
            case "join":
                userAction = "3";
                break;
            case "username":
                userAction = "4";
                break;
            case "me":
                userAction = "5";
                break;
            case "leave":
                userAction = "7";
                break;
            default:
                return null;
        }

        String newContent = "";

        for (int i = 1; i < strings.length; ++i) {
            newContent = newContent.concat(strings[i]);
        }

        return STX + DC1 + version + DC1 + userAction + DC1 + newContent + DC1 + ETX;
    }

    @Override
    public String[] decode(String message) {
        String[] strings = message.split(DC1);
        String version = strings[0];
        String action = strings[1];
        String content = strings[2];
        String[] messageToUser = new String[1];

        switch (action) {
			case "1": // connect
                messageToUser[0] = decodeConnectMessage(content);
                break;
            case "2": // create
                messageToUser[0] = decodeCreateGroupMessage(content);
                break;
            case "3": // join
                messageToUser[0] = decodeJoinMessage(content);
                break;
            case "4": // setUserName
                messageToUser[0] = decodeSetUserNameMessage(content);
                break;
            case "5": // message
                messageToUser[0] = decodeGroupMessage(content);
                break;
            case "6": // error
                messageToUser[0] = decodeErrorMessage(content);
                break;
            case "7": // exit
                messageToUser[0] = decodeExitMessage(content);
                break;
            default:
                messageToUser[0] = "Unknown action " + action;
        }

		return messageToUser;
    }

    private String colorString(String color, String message) {
        return color + message + ANSI_RESET;
    }

    private String decodeConnectMessage(String content) {
        this.userID = content;
        return colorString(ANSI_GREEN, "Connected to server.");
    }

    private String decodeCreateGroupMessage(String content) {
        return colorString(ANSI_GREEN, "Group '" + content + "' created.");
    }

    private String decodeJoinMessage(String content) {
        String[] strings = content.split(US);
        String userID = strings[0];
        String userName = strings[1];
        String group = strings[2];

        if (userID.equals(this.userID)) {
            return colorString(ANSI_BLUE, "You have joined " + group);
        }

        return colorString(ANSI_BLUE, userName + " has joined " + group);
    }

    private String decodeSetUserNameMessage(String content) {
        return colorString(ANSI_BLUE, "user name set to: " + content);
    }

    private String decodeGroupMessage(String content) {
        String[] strings = content.split(US);
        String userID = strings[0];
        String userName = strings[1];
        String message = strings[2];

        if (userID.equals(this.userID)) { return null; }

        return userName + ": " + message;
    }

    private String decodeErrorMessage(String content) {
        String[] strings = content.split(US);
        String action = strings[0];
        String error = strings[1];

        return colorString(ANSI_RED, "Error: " + action + " " + error); //TODO not sure about this
    }

    private String decodeExitMessage(String content) {
        String[] strings = content.split(US);
        String userID = strings[0];
        String userName = strings[1];
        String exitMessage = strings[2];

        if (userID.equals(this.userID)) {
            return colorString(ANSI_YELLOW, "me: " + exitMessage) +
             "\n" + colorString(ANSI_BLUE, "You have exited the group");
        }

        return userName + ": " + exitMessage + "\n" + colorString(ANSI_BLUE, userName + " has left the group");
    }

}
