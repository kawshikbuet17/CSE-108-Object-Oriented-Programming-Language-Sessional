package sample;

import javafx.application.Application;
import javafx.application.Platform;

import java.io.*;
import java.net.Socket;
import java.util.StringTokenizer;

public class ReadThread extends Thread {

        private Socket connectionSocket;
        private BufferedReader inFromServer;
        private PrintWriter outToServer;
        public Controller pc;
        private String sentence;


        public ReadThread(Socket connectionSocket,Controller pc)
        {
            this.connectionSocket=connectionSocket;
            this.pc=pc;
            sentence=new String();
        }

        @Override
        public void run() {
            try{
                while (true)
                {
                    //System.out.println("in there");
                    BufferedReader inFromServer = new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
                    //PrintWriter outToServer = new PrintWriter(connectionSocket.getOutputStream());
                    sentence=inFromServer.readLine();
                    if(!sentence.equals("File"))
                        System.out.println(sentence);

                    if(!sentence.equals("File"))
                    {
                        Platform.runLater(new Runnable() {
                                                      @Override
                                                      public void run() {
                                                          if(!sentence.equals("File"))
                                                            pc.setLabel(sentence);
                                                      }
                                                  });
                    }
                    if(sentence.equals("Logged out")){
                        Thread.sleep(2000);
                        Platform.runLater(new Runnable() {
                                                      @Override
                                                      public void run() {
                                                          pc.closer();
                                                      }
                                                  });
                        return;
                    }

                    if(sentence.equals("File"))
                    {
                        byte[] byara=new byte[2004];
                        InputStream is=connectionSocket.getInputStream();
                        FileOutputStream os=new FileOutputStream("Client_received.txt");
                        is.read(byara,0, byara.length);
                        os.write(byara,0, byara.length);
                    }
                }
            }
            catch (Exception e)
            {
                e.printStackTrace();
            }
        }
    }
