package allin;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;

public class Lmessage {

    private String username,password,type;
    private boolean logged_in;
    private String[] ara;
    private Socket connectionSocket;
    private PrintWriter outToclient;

    public boolean isLogged_in() {
        return logged_in;
    }

    public String getUsername() {
        return username;
    }

    public String getPassword() {
        return password;
    }

    public String getType() {
        return type;
    }

    public Lmessage(String[] ara,boolean logged_in,Socket connectionSocket)
    {
        this.ara=ara;
        this.logged_in=logged_in;
        this.connectionSocket=connectionSocket;
        try {
            outToclient=new PrintWriter(connectionSocket.getOutputStream());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public boolean login()
    {
        if(!logged_in) {
            readfromfile r = new readfromfile("F:\\Offline of networking(Swapnil)\\offline networking server\\src\\expi.txt");
            //System.out.println("constructor");
            r.openfile();
            //System.out.println("opened");
            r.readfile();
            //System.out.println("read");
            String[] s = r.getS();
            int length = r.getLength();
            r.closefile();
            //System.out.println("closed");
        /*for(int i=0;i<r.getLength();i++)
        {
            System.out.println(s[i]);
        }*/

            for (int i = 0; i < length; i += 3) {
                if (ara[1].equals(s[i])) {
                    if (ara[2].equals(s[i + 1])) {
                        if (ara[3].equals(s[i + 2])) {
                            username = ara[1];
                            password = ara[2];
                            type = ara[3];
                            logged_in = true;
                            Server.loggedinmembers += ara[1] + " ";
                            //System.out.println("Success");
                            return true;
                        }
                    }
                }
            }
            return false;
        }
        else
            return false;
    }
}
