import com.fazecast.jSerialComm.SerialPort;

import javax.swing.*;
import java.awt.*;
import java.io.PrintWriter;
import java.util.Scanner;

public class OperatorDashboard {

    private SerialPort serialPort;
    private PrintWriter output;
    private Scanner input;

    private JFrame frame;
    private JLabel tempLabel;
    private JLabel wasteLevelLabel;
    private JLabel tempValueLabel;
    private JLabel wasteImageLabel;
    private JLabel gifLabel;
    private JProgressBar wasteLevelProgress;
    private JButton btnEmpty;
    private JButton btnRestore;

    public OperatorDashboard() {
        setupSerial();

        frame = new JFrame("Smart Waste Disposal System");
        frame.setLayout(new BorderLayout());
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(500, 300);
        frame.setResizable(false);
        frame.getContentPane().setBackground(new Color(255, 248, 198));

        JPanel topPanel = new JPanel();
        topPanel.setLayout(new FlowLayout());
        topPanel.setBackground(new Color(204, 255, 204));
        btnEmpty = new JButton("Empty");
        btnRestore = new JButton("Restore");
        btnEmpty.setBackground(new Color(255, 204, 204));
        btnRestore.setBackground(new Color(255, 204, 204));
        btnEmpty.addActionListener(e -> sendCommand("EMPTY"));
        btnRestore.addActionListener(e -> sendCommand("RESTORE"));
        topPanel.add(btnEmpty);
        topPanel.add(btnRestore);

        frame.add(topPanel, BorderLayout.NORTH);

        JPanel mainPanel = new JPanel();
        mainPanel.setLayout(new GridLayout(1, 2));

        JPanel leftPanel = new JPanel();
        leftPanel.setLayout(new BorderLayout());
        leftPanel.setBackground(new Color(255, 248, 198));
        tempLabel = new JLabel("Temperature reached:");
        tempValueLabel = new JLabel("0.00 °C");

        gifLabel = new JLabel(new ImageIcon("temp.png"));
        gifLabel.setOpaque(true);
        gifLabel.setBackground(new Color(255, 248, 198)); 

        leftPanel.add(tempLabel, BorderLayout.NORTH);
        leftPanel.add(tempValueLabel, BorderLayout.CENTER);
        leftPanel.add(gifLabel, BorderLayout.SOUTH);

        JPanel rightPanel = new JPanel();
        rightPanel.setLayout(new BorderLayout());
        rightPanel.setBackground(new Color(255, 248, 198));
        wasteLevelLabel = new JLabel("Waste Level: ");
        wasteLevelProgress = new JProgressBar(0, 100);
        wasteLevelProgress.setValue(0);
        wasteLevelProgress.setStringPainted(true);

        wasteImageLabel = new JLabel(new ImageIcon("liquid.png"));
        wasteImageLabel.setOpaque(true);
        wasteImageLabel.setBackground(new Color(255, 248, 198)); 

        rightPanel.add(wasteLevelLabel, BorderLayout.NORTH);
        rightPanel.add(wasteLevelProgress, BorderLayout.CENTER);
        rightPanel.add(wasteImageLabel, BorderLayout.SOUTH);

        mainPanel.add(leftPanel);
        mainPanel.add(rightPanel);
 
        frame.add(mainPanel, BorderLayout.CENTER);

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
