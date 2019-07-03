package allin;

import java.io.File;
import java.util.Scanner;


public class readfromfile {
    private Scanner sc;
    private int i;
    private String file;
    private String []s;
    private int length;

    public String[] getS()
    {
        return s;
    }

    public readfromfile(String file2)
    {
        i=0;
        length=0;
        file=new String(file2);
        s=new String[1000];
    }

    public void openfile()
    {
        try {
            sc=new Scanner(new File(file));
        }
        catch (Exception e)
        {
            System.out.println("Invalid File");
        }
    }
    public void readfile()
    {
        while(sc.hasNext())
        {
            s[i]=sc.next();
            i++;
            s[i]=sc.next();
            i++;
            s[i]=sc.next();
            i++;
        }
        length=i;
    }

    public int getLength()
    {
        return length;
    }

    public void closefile()
        {
            sc.close();
        }

}

