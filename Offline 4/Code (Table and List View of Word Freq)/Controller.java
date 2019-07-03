package sample;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.Button;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.stage.FileChooser;

import java.awt.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Collection;
import java.util.Scanner;

public class Controller {
    @FXML
    private Button addFileButton;

    @FXML
    private ListView listView;
    @FXML
    private ListView listzzz;
    @FXML
    private ListView listzzz2;

    @FXML private Button b1;
    @FXML private Button b2;

    @FXML
    public static ObservableList<wordClass> list = FXCollections.observableArrayList();
    @FXML
    public static ObservableList<String> list2 = FXCollections.observableArrayList();
    public wordClass []w = new wordClass[1000];
    @FXML private TableView<wordClass> table;
    @FXML private TableColumn<wordClass, String> word;
    @FXML private TableColumn<wordClass, Integer>freq;
    @FXML
    private File selectedFile;

    @FXML
    public void ButtonAction() throws FileNotFoundException {
        list.clear();
        list2.clear();
        System.out.println("Kawshik Kumar Paul");
        FileChooser fc = new FileChooser();
        fc.getExtensionFilters().add(new FileChooser.ExtensionFilter("txt files", "*.txt"));
        selectedFile = fc.showOpenDialog(null);

        if (selectedFile != null) {
            listView.getItems().add(selectedFile.getName());
        } else {
            System.out.println("File not found");
        }
    }
    @FXML
    public void Button2Action() throws FileNotFoundException {

        if ((selectedFile != null)) {
            File fff = new File(selectedFile.getAbsolutePath());
            int cnt, i = 0, j, k;
            String[] str = new String[1000];
            Scanner sc = new Scanner(fff);
            sc.useDelimiter("[^A-Za-z0-9]+");
            while (sc.hasNext()) {
                str[i] = sc.next();
                System.out.println(str[i]);
                i++;
            }
            for (j = 0; str[j] != null; j++) {
                cnt = 1;
                if (!"~".equals(str[j])) {
                    for (k = j + 1; str[k] != null; k++) {
                        if (str[j].equalsIgnoreCase(str[k]) == true) {
                            str[k] = "~";
                            cnt++;
                        }
                    }

                    String temp = new String("");
                    temp += str[j] + "      " + String.valueOf(cnt);
                    list2.addAll(temp);
                    listzzz.setItems(list2);
                    //listzzz.getItems().addAll(str[j]);
                    //listzzz.getItems().addAll(String.valueOf(cnt));

                }
            }
        }
    }
    @FXML
    public void Button3Action() throws FileNotFoundException{

        if ((selectedFile != null)){
            File fff = new File(selectedFile.getAbsolutePath());
            int cnt, i = 0, j, k;
            String[] str = new String[1000];
            Scanner sc = new Scanner(fff);
            sc.useDelimiter("[^A-Za-z0-9]+");
            while (sc.hasNext()) {
                str[i] = sc.next();
                System.out.println(str[i]);
                i++;
            }
            for (j = 0; str[j] != null; j++) {
                cnt = 1;
                if (!"~".equals(str[j])) {
                    for (k = j + 1; str[k] != null; k++) {
                        if (str[j].equalsIgnoreCase(str[k]) == true) {
                            str[k] = "~";
                            cnt++;
                        }
                    }
                    w[j] = new wordClass(str[j], cnt);
                    list.addAll(new wordClass(str[j], cnt));

                }
            }
            table.setItems(list);
            word.setCellValueFactory(new PropertyValueFactory<wordClass, String>("word"));
            freq.setCellValueFactory(new PropertyValueFactory<wordClass, Integer>("freq"));
        }
    }
}
