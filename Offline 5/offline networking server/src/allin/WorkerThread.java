package allin;


import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.StringTokenizer;

public class WorkerThread implements Runnable
{
    private Socket connectionSocket;
    private int id;
    private BufferedReader inFromClient;
    private PrintWriter outToClient2;
    //different modes
    private int mode;
    public Server server;

    public String getUsername() {
        return username;
    }

    public String getType() {
        return type;
    }

    //logged in state
    private boolean logged_in;
    //Client Information
    private String username;
    private String password;
    private String type;
    //logged in members
    //public  String loggedinmembers;

        /*static {
            loggedinmembers=new String();
        }*/

    public WorkerThread(Socket s, int id,Server server)throws Exception
    {
        this.connectionSocket = s;
        this.id = id;
        mode=0;
        logged_in=false;
        this.server=server;
    }

    public void sendMessage(String username,String Message)
    {
        outToClient2.println(username+" says "+Message);
        outToClient2.flush();
    }

    public void sendFiletoClient(byte[] b)
    {
        try
        {
            outToClient2.println("File");
            outToClient2.flush();
            OutputStream outputStream = connectionSocket.getOutputStream();
            outputStream.write(b,0,b.length);
            //outputStream.flush();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    public void run()
    {
        String clientCommand;
        //String capitalizedSentence;
        while(true) {
            try {
                //System.out.println(logged_in);
                inFromClient = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
                outToClient2 = new PrintWriter(connectionSocket.getOutputStream());
                clientCommand = inFromClient.readLine();
                //System.out.println(clientCommand);
                StringTokenizer st = new StringTokenizer(clientCommand, "#");
                String[] ara = new String[100];
                int length = 0;
                while (st.hasMoreTokens()) {
                    ara[length] = st.nextToken();
                    length++;
                }

                if (ara[0].equals("L")) {
                    Lmessage lm=new Lmessage(ara,logged_in,connectionSocket);
                    if (lm.login()) {
                        outToClient2.println("login successful");
                        username=lm.getUsername();
                        type=lm.getType();
                        outToClient2.flush();
                        logged_in = lm.isLogged_in();
                    }

                    else {
                        if(logged_in)
                        {
                            outToClient2.println("already logged in");
                            outToClient2.flush();
                        }
                        else {
                            outToClient2.println("login failed");
                            outToClient2.flush();
                        }
                    }
                }
                else if(ara[0].equals("S"))
                {
                    Smessage sm=new Smessage(ara,username,logged_in);
                    int l=sm.soptions();
                    //System.out.println(l);

                    if(l==1)
                    {
                        outToClient2.println(Server.loggedinmembers);
                        outToClient2.flush();
                    }
                    else if(l==2)
                    {

                        logged_in=sm.isLoggedin();
                        outToClient2.println("Logged out");
                        outToClient2.flush();
                        connectionSocket.close();
                        return;
                    }
                    else
                    {
                        outToClient2.println("Invalid Command");
                        outToClient2.flush();
                    }
                }
                else if(ara[0].equals("B"))
                {
                    if(logged_in) {
                        Bmessage bm = new Bmessage(username, server, type, ara, outToClient2);
                        bm.send();
                    }

                    else {
                        outToClient2.println("Invalid Command");
                        outToClient2.flush();
                    }
                }

                else if(ara[0].equals("C"))
                {
                    if(logged_in)
                    {
                        Cmessage cm=new Cmessage(username,ara,server,outToClient2,connectionSocket);
                        cm.send();
                    }
                    else {
                        outToClient2.println("Invalid Command");
                        outToClient2.flush();
                    }
                }

                else
                {
                    if(logged_in)
                    {
                        outToClient2.println("Invalid Command");
                        outToClient2.flush();
                    }
                    else
                    {
                        outToClient2.println("login failed");
                        outToClient2.flush();
                    }
                }

            }
            catch (Exception e) {
                System.out.println("Caught Exception in run of Server");
            }
        }
    }

    /*
    public boolean login(String[] ara)
    {
        readfromfile r=new readfromfile("D:\\offline networking server\\src\\expi.txt");
        System.out.println("constructor");
        r.openfile();
        System.out.println("opened");
        r.readfile();
        System.out.println("read");
        String []s=r.getS();
        r.closefile();
        System.out.println("closed");
        for(int i=0;i<r.getLength();i++)
        {
            System.out.println(s[i]);
        }

        if(ara[0].equals("L")) {
            for (int i = 0; i < r.getLength(); i += 3) {
                if (ara[1].equals(s[i])) {
                    if (ara[2].equals(s[i + 1])) {
                        if (ara[3].equals(s[i + 2])) {
                            username=ara[1];
                            password=ara[2];
                            type=ara[3];
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }
    */
}
