import javax.swing.*;
import java.io.*;

public class Main {
    public static void main (String[] args) {

        GuiInputService gis = new GuiInputService();
        String msg = gis.getInput();
        FileHandler.write(msg);

        WordRain wr = new WordRain();
        wr.rainWord();
    }

    static class FileHandler {
        public static void write (String msg) {
            try {
                File f = new File("message.txt");
                f.createNewFile();

                FileOutputStream fos = new FileOutputStream(f);
                final byte[] msgBt = msg.getBytes();
                fos.write(msgBt);
                fos.close();

            } catch (IOException e) {
                System.out.println(e);

            }

        }
    }

    static class GuiInputService {
        public GuiInputService () {

        }

        public String getInput () {
            return JOptionPane.showInputDialog(null, "Enter text to display...");
        }
    }

    public static class WordRain {
        static {
            System.loadLibrary("NativeLib");
        }

        public native void rainWord();
    }
}