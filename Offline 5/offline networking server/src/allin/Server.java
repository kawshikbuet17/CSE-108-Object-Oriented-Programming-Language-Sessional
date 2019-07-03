package allin;


import java.net.*;
import java.util.Vector;


public class Server {
    Vector<WorkerThread> clients = new Vector<WorkerThread>();
    public static String loggedinmembers;

    static{
        loggedinmembers=new String();
    }


    public static void main(String[] args) throws Exception {
        new Server().connection();

    }

    public void connection()throws Exception
    {
        System.out.println("Server is up and running...");
        int workerThreadCount = 0;
        String clientSentence;
        String capitalizedSentence;
        ServerSocket welcomeSocket = new ServerSocket(4444);
        int id = 1;
        while (true) {
            Socket connectionSocket = welcomeSocket.accept();
            WorkerThread wt = new WorkerThread(connectionSocket, id,this);
            clients.add(wt);
            Thread t = new Thread(wt);
            t.start();
            workerThreadCount++;
            System.out.println("Client [" + id + "] is now connected. No. of worker threads = " + workerThreadCount);
            id++;
        }
    }

    public void sendTOallClients(String username,String msg)
    {
        //System.out.println("Got there");
        for(WorkerThread wt:clients)
        {
            //System.out.println("Got in the loop");
            //wt.sendMessage(username,msg);
           if(!wt.getUsername().equals(username))
            {
                wt.sendMessage(username,msg);
            }
        }
    }

    public void sendTosomeClient(String receiver,String sender,String msg)
    {
        for(WorkerThread wt:clients)
        {
            if(wt.getUsername().equals(receiver))
            {
                wt.sendMessage(sender,msg);
            }
        }
    }

    public void sendFile(String receiver,byte[] b)
    {
        for(WorkerThread wt:clients)
        {
            if(wt.getUsername().equals(receiver))
            {
                wt.sendFiletoClient(b);
            }
        }
    }

}


