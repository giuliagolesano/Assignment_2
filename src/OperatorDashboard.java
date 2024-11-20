import com.fazecast.jSerialComm.SerialPort;

import javax.swing.*;
import java.awt.*;
import java.io.PrintWriter;
import java.util.Scanner;

public class OperatorDashboard {

    private SerialPort serialPort;
    private PrintWriter output;
    private Scanner input;

    private JLabel tempValueLabel;
    private JProgressBar wasteLevelProgress;
    private JButton btnEmpty;
    private JButton btnRestore;

    public OperatorDashboard() {
        setupSerial();

        JFrame frame = new JFrame("Smart Waste Disposal System");
        frame.setLayout(new BorderLayout());
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500, 300);

        JPanel topPanel = new JPanel();
        btnEmpty = new JButton("Empty");
        btnRestore = new JButton("Restore");

        btnEmpty.addActionListener(e -> sendCommand("EMPTY"));
        btnRestore.addActionListener(e -> sendCommand("RESTORE"));

        topPanel.add(btnEmpty);
        topPanel.add(btnRestore);

        tempValueLabel = new JLabel("Temperature: 0.00 °C");
        wasteLevelProgress = new JProgressBar(0, 100);
        wasteLevelProgress.setValue(0);
        wasteLevelProgress.setStringPainted(true);

        frame.add(tempValueLabel, BorderLayout.WEST);
        frame.add(wasteLevelProgress, BorderLayout.CENTER);
        frame.add(topPanel, BorderLayout.SOUTH);

        frame.setVisible(true);

        new Thread(this::readSerial).start();
    }

    private void setupSerial() {
        serialPort = SerialPort.getCommPort("COM3"); 
        serialPort.setBaudRate(9600);

        if (serialPort.openPort()) {
            output = new PrintWriter(serialPort.getOutputStream(), true);
            input = new Scanner(serialPort.getInputStream());
        }
    }

    private void sendCommand(String command) {
        if (output != null) {
            output.println(command);
        }
    }

    private void readSerial() {
        while (input.hasNextLine()) {
            String line = input.nextLine();
            if (line.startsWith("TEMP:")) {
                String temp = line.split(":")[1].split(";")[0];
                SwingUtilities.invokeLater(() -> tempValueLabel.setText("Temperature: " + temp + " °C"));
            }
            if (line.contains("WASTE:")) {
                String waste = line.split(";")[1].split(":")[1];
                SwingUtilities.invokeLater(() -> wasteLevelProgress.setValue(Integer.parseInt(waste.trim())));
            }
        }
    }

    public static void main(String[] args) {
        new OperatorDashboard();
    }
}
