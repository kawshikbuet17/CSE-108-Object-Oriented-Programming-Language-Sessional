package allin;

import java.io.PrintWriter;

public class Bmessage {
    private String type;
    private Server server;
    private String username;
    private String[] ara;
    private PrintWriter pw;
    //private WorkerThread wt;

    public Bmessage(String username, Server server, String type, String[] ara,PrintWriter pw) {
        this.type = type;
        this.server = server;
        this.username = username;
        this.ara = ara;
        this.pw=pw;
    }

    public void send()
    {
        //System.out.println("Type="+type);
        if(type.equals("admin"))
        {
            server.sendTOallClients(username,ara[1]);
            pw.println("Message Sending Successful");
            pw.flush();
        }
        else {
            pw.println("Message Sending Unsuccessful");
            pw.flush();
        }
    }

}
