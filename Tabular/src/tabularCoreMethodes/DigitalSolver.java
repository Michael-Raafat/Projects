package tabularCoreMethodes;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import javax.swing.JButton;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Collections;
import java.awt.event.ActionEvent;
import javax.swing.SwingConstants;

public class DigitalSolver {

	private JFrame frame;
	private JLabel label;
	private OuterShell shell = new OuterShell();
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					DigitalSolver window = new DigitalSolver();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public DigitalSolver() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.getContentPane().setBackground(Color.BLACK);
		frame.setResizable(false);
		frame.setBounds(100, 100, 600, 400);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);
		
		label = new JLabel("");
		label.setHorizontalAlignment(SwingConstants.CENTER);
		label.setForeground(Color.GREEN);
		label.setFont(new Font("Agency FB", Font.BOLD, 18));
		label.setOpaque(true);
		label.setBackground(Color.GRAY);
		label.setBounds(0, 0, 594, 111);
		frame.getContentPane().add(label);
		
		JButton btnNewButton = new JButton("<html>Read from File</html>");
		btnNewButton.setBackground(Color.LIGHT_GRAY);
		btnNewButton.setForeground(Color.GREEN);
		btnNewButton.setFont(new Font("Times New Roman", Font.BOLD, 19));
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					JTextField field;
					field = new JTextField();
					JOptionPane.showMessageDialog(null, field, "Enter your Filename without extension", 1);
					String name = field.getText();
					shell.readFile(name);
					label.setText("<html>"+"First minimal Solution is "+shell.getFirstAnswer()+"<br>"
							+"You can find the complete answer in the text file "+ shell.getWriteName()+"</html>");
				} catch (StackOverflowError sd) {
					label.setText("<html>Couldn't find the file named like this. Please put in the same destination as the program.</html>");
				} catch (Exception eds) {
					label.setText("<html>An Error has happenend! please read the help instructions first.</html>");
				}
			}});
		btnNewButton.setBounds(427, 124, 155, 91);
		frame.getContentPane().add(btnNewButton);
		
		JButton btnenterInputs = new JButton("<html>Enter Inputs</html>");
		btnenterInputs.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				try {
					JTextField field;
					int num;
					ArrayList<Integer> m = new ArrayList<Integer>();
					ArrayList<Integer> d = new ArrayList<Integer>();
					do {
						field = new JTextField();
						JOptionPane.showMessageDialog(null, field, "Enter your minterms", 1);
						num = Integer.parseInt(field.getText());
						if (num != -1) {
							m.add(num);
						}
					} while (num != -1);
					do {
						field = new JTextField();
						JOptionPane.showMessageDialog(null, field, "Enter your don't care terms", 1);
						num = Integer.parseInt(field.getText());
						if (num != -1) {
							d.add(num);
						}
					} while (num != -1);
					Collections.sort(m);
					Collections.sort(d);
					shell.solTwoList(m, d);
					label.setText("<html>"+"First minimal Solution is "+shell.getFirstAnswer()+"<br>"
							+"You can find the complete answer in the text file "+ shell.getWriteName()+"</html>");
				} catch (Exception eds) {
					label.setText("<html>An Error has happenend! please read the help instructions first.</html>");
				}
			}
		});
		btnenterInputs.setForeground(Color.GREEN);
		btnenterInputs.setFont(new Font("Times New Roman", Font.BOLD, 19));
		btnenterInputs.setBackground(Color.LIGHT_GRAY);
		btnenterInputs.setBounds(10, 124, 155, 91);
		frame.getContentPane().add(btnenterInputs);
		
		JButton btnhelp = new JButton("<html>Help</html>");
		btnhelp.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				JOptionPane.showMessageDialog(null, "<html>This is a program that solves digital problems by using"
						+ " tabular method.<br> You can Enter the terms manually and end the insertion of a certain type by inputing -1"
						+ ".<br> If you choose a file , then you must have m before the minterms and d before the dont'care terms.<br> And between each number a comma.<br>"
						+ "And you input the textfile name without extension<br>"
						+ "have fun :D");
			}
		});
		btnhelp.setForeground(Color.GREEN);
		btnhelp.setFont(new Font("Times New Roman", Font.BOLD, 19));
		btnhelp.setBackground(Color.LIGHT_GRAY);
		btnhelp.setBounds(221, 124, 155, 91);
		frame.getContentPane().add(btnhelp);
		
		JLabel lblMadeByAmr = new JLabel("Made by Amr Nasr & Michael Raafat");
		lblMadeByAmr.setForeground(Color.YELLOW);
		lblMadeByAmr.setFont(new Font("Algerian", Font.BOLD, 21));
		lblMadeByAmr.setHorizontalAlignment(SwingConstants.CENTER);
		lblMadeByAmr.setOpaque(true);
		lblMadeByAmr.setBackground(Color.LIGHT_GRAY);
		lblMadeByAmr.setBounds(0, 274, 594, 91);
		frame.getContentPane().add(lblMadeByAmr);
	}
}
