package tabularCoreMethodes;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class OuterShell {
	QuineMcCluskeyApplication qm;
	PetricksEngine pe;
	ArrayList<String> answers;
	ArrayList<Integer> dontcars;
	ArrayList<Integer> mincars;
	String firstAnswer;
	String tempreadname;
	String tempwritename;
	boolean rf = false;
	int prosolv = 0;
	public void solTwoList(ArrayList<Integer> m ,ArrayList<Integer> d) {
		if(m == null || (!(d==null) && !valid(m,d))) {
			throw new RuntimeException();
		}
		qm = new QuineMcCluskeyApplication();
		mincars = new ArrayList<Integer>();
		for (int j=0; j <m.size(); j++) {
			mincars.add(m.get(j));
		}
		if (d == null) {
			qm.setLists(m, null);
			dontcars = new ArrayList<Integer>();
		} else {
			dontcars = d;
			qm.setLists(m, dontcars);
		}
		qm.settingTable();
		qm.gettingTables();
		qm.gettingPrimes();
		pe = new PetricksEngine(qm);
		answers = pe.getAnswer();
		firstAnswer = answers.get(0);
		this.printSol();
	}
	private boolean valid(ArrayList<Integer> m ,ArrayList<Integer> d) {
		for(int i =0; i < m.size();i++) {
			if(d.contains(m.get(i))) {
				return false;
			}
		}
		for(int i = 0; i < m.size(); i++) {
			if (m.get(i) >= 67108864 || m.get(i) < 0) {
				return false;
			}
		}
		for(int i = 0; i < d.size(); i++) {
			if (d.get(i) >= 67108864 || d.get(i) < 0) {
				return false;
			}
		}
		return true;
	}
	private boolean isNumber(char c) {
		if (c >= '0' && c <= '9') {
			return true;
		}
		return false;
	}
	public void readFile (String name) {
		ArrayList<Integer> m = new ArrayList<Integer>();
		ArrayList<Integer> d = new ArrayList<Integer>();
		String linetext = "";
		try {
			tempreadname = name;
			rf = true;
			File file = new File(name+".txt");
			Scanner sn = new Scanner(file);
			m = new ArrayList<Integer>();
			d = new ArrayList<Integer>();
			boolean min = true;
			while (sn.hasNext()) {
				linetext = sn.nextLine();
				for (int k = 0; k < linetext.length(); k++) {
					if (linetext.charAt(k) == 'm') {
						min = true;
					} else if (linetext.charAt(k) == 'd') {
						min = false;
					} else if (isNumber(linetext.charAt(k))){
						int fac = 10;
						int in = 0;
						while (k < linetext.length() && isNumber(linetext.charAt(k))) {
							in *= fac;
							in +=
							Integer.parseInt(
							String.valueOf(linetext.charAt(k)));
							k++;
						}
						while (k < linetext.length() && linetext.charAt(k) == ' ') {
							k++;
						}
						if (k < linetext.length()
							&& linetext.charAt(k) != ','
							&& linetext.charAt(k) != 'm'
							&& linetext.charAt(k) != 'd'
							&& linetext.charAt(k) != '\t') {
							throw new RuntimeException();
						}
						if (min) {
							m.add(in);
						} else {
							d.add(in);
						}
						if(k < linetext.length()
								&& (linetext.charAt(k) == 'm')) {
								min = true;
							} else if (k < linetext.length()
								&& (linetext.charAt(k) == 'd')) {
								min = false;
							}
					} else if(linetext.charAt(k) != ' '
						&& linetext.charAt(k) != ','
						&& linetext.charAt(k) != '\t') {
						throw new RuntimeException();
					}
				}
			}
			this.solTwoList(m, d);
		} catch (RuntimeException ex) {
			throw new RuntimeException(ex.getMessage());
		} catch (Exception e) {
			throw new StackOverflowError();
		}
	}
	private void printSol() {
		PrintWriter writer;
		try {
			String filename;
			if (!rf) {
				filename = "Solution"+ prosolv +".txt";
				prosolv ++;
			} else {
				filename = tempreadname + "Sol"+".txt";
				rf = false;
			}
			tempwritename = filename;
			writer = new PrintWriter(filename);
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			throw new RuntimeException();
		}
		writer.print("The min Terms are : ");
		for (int i = 0; i < mincars.size() ; i++) {
			if (i != this.mincars.size() - 1) {
				writer.print(this.mincars.get(i) + ", ");
			} else {
				writer.println(this.mincars.get(i));
			}
		}
		writer.println();
		writer.print("The Don't care Terms are : ");
		for (int i = 0; i < dontcars.size() ; i++) {
			if (i != dontcars.size() - 1) {
				writer.print(dontcars.get(i) + ", ");
			} else {
				writer.println(dontcars.get(i));
			}
		}
		writer.println();
		writer.println("----------------------------------------------------------");
		writer.println("Quine-McCluskey Tables :");
		writer.println("------------------------");
		for (int i = 0; i < qm.getTablesCount();i++) {
			writer.println("Table "+ (1+i));
			for (int j = 0; j <qm.getTableLength(i);j++) {
				writer.println(qm.getRow(i, j));
			}
			writer.println("----------------------------------------------------------");
		}
		writer.println("Prime Nodes :");
		writer.println("-------------");
		for (int j = 0; j <qm.getPrimeCount();j++) {
			writer.println(qm.getPrime(j));
		}
		writer.println("----------------------------------------------------------");
		writer.println("Minimal Solutions :");
		writer.println("-------------------");
		for(int i=0 ; i < answers.size() ; i++) {
			writer.println("Solution " + (i+1));
			writer.println(answers.get(i));
		}
		writer.println("----------------------------------------------------------");
		writer.println("Thanks for using our Solver.");
		writer.println("This is made by Amr Nasr & Michael Raafat.");
		writer.close();
	}
	
	public String getFirstAnswer() {
		return firstAnswer;
	}
	public String getWriteName() {
		return tempwritename;
	}
}
