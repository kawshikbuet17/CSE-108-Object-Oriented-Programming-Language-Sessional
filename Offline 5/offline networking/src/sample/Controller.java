package sample;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.net.URL;
import java.util.ResourceBundle;
import java.util.StringTokenizer;

public class Controller implements Initializable {

    ReadThread r;

    @FXML
    private AnchorPane rootpane;
    @FXML
    private TextField textField;
    @FXML
    public Label label;


    //Socket to connect to server
    private Socket clientSocket;
    //read from the server
    private BufferedReader inFromServer;
    //send to the server
    private PrintWriter outToServer;


    @Override
    public void initialize(URL location, ResourceBundle resources) {
        try {
            clientSocket = new Socket("localhost", 4444);
            r=new ReadThread(clientSocket,this);
            //yourValue=null;
            Thread t=new Thread(r);
            t.start();
        }
        catch (Exception e)
        {
            System.out.println("Exception caught in client Initialize method");
        }
    }

    public void closer()
    {
        Stage stage=(Stage)rootpane.getScene().getWindow();
        stage.close();
    }

    public void clicksendbutton()throws Exception
    {
        String sentence;
        outToServer = new PrintWriter(clientSocket.getOutputStream());
        sentence = textField.getText();
        outToServer.println(sentence);
        outToServer.flush();
    }

    public void setLabel(String s)
    {
        label.setText(s);
    }

}
