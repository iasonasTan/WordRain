import javax.swing.*;
import java.io.*;

public class Main {
    public static void main (String[] args) {
        String msg = JOptionPane.showInputDialog(null, "Enter text to display...");
        if(msg != null) {
            FileHandler.write(msg);
            WordRain wr = new WordRain();
            wr.rainWord();
        }
    }

    static class FileHandler {
        static void write (String msg) {
            File f = new File("message.txt");
            try (FileOutputStream fos=new FileOutputStream(f)) {
                byte[] msgBt = msg.getBytes();
                fos.write(msgBt);
            } catch (IOException e) {
                JOptionPane.showMessageDialog(null, "Cannot write to or create file message.txt. "+e);
                throw new RuntimeException(e);
            }

        }
    }

    static class WordRain {
        static {
            System.loadLibrary("NativeLib");
        }

        native void rainWord();
    }
}