package allin;

import java.io.*;
import java.net.Socket;

public class Cmessage {
    private String sender;
    private String receiver;
    private String[] ara;
    private Server server;
    private PrintWriter pw;
    private Socket connectionsocket;

    public Cmessage(String sender, String[] ara, Server server, PrintWriter pw, Socket connectionsocket)
    {
        this.sender=sender;
        this.ara=ara;
        this.server=server;
        this.pw=pw;
        this.connectionsocket=connectionsocket;
    }

    public void send()
    {
        server.sendTosomeClient(ara[1],sender,ara[2]);

        if(ara[3]!=null)
        {
            pw.println("Message and File Sending Successful");
            pw.flush();
            //System.out.println("File has to be sent");
            try {
                //FileInputStream is=new FileInputStream("C:\\Users\\User\\Desktop\\Offline of networking\\Files to be sent\\"+ara[3]);
                FileInputStream is=new FileInputStream("D:\\Files to be sent\\"+ara[3]);
                byte[] byara=new byte[2004];
                is.read(byara,0,byara.length);
                server.sendFile(ara[1],byara);
                //System.out.println("File sent successfully");
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        else {
            pw.println("Message Sending Successful");
            pw.flush();
        }
    }

}
