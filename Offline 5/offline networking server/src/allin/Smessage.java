package allin;

public class Smessage {
    private String[] ara;
    private String username;
    private boolean loggedin;


    public Smessage(String[] ara,String username,boolean loggedin) {
        this.ara = ara;
        this.username=username;
        this.loggedin=loggedin;
    }

    public boolean isLoggedin() {
        return loggedin;
    }

    public int soptions()
    {
        if(loggedin) {
            if (ara[1].equals("show")) {
                System.out.println(ara[2]);
                return 1;
            } else if (ara[1].equals("logout")) {
                System.out.println(ara[2]);
                System.out.println(username+" logged out successfully");
                loggedin = false;
                Server.loggedinmembers=Server.loggedinmembers.replaceAll(username,"");
                return 2;
            }
        }
        else {
            return 0;
        }
        return 0;
    }
}

