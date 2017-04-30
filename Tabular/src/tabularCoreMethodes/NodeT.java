package tabularCoreMethodes;

import java.util.ArrayList;
/**
 * Node used to contain a table row data.
 * @author Michael.
 *
 */
public class NodeT {
	/**
	 * Binary representation of a few Integers.
	 */
	private String binary;
	/**
	 * Constructor for the basic elements with only one
	 * integer entered to be stored in this row.
	 * @param bitsNumber
	 * the number of bits to be in the String representation.
	 * @param value
	 * the number to be saved and represented
	 * Should automatically set all the other variables of the node.
	 * sets variableNumber to bitsNumber.
	 */
	public NodeT(final int bitsNumber, final int value) {
		variablesNumber = bitsNumber;
		numbers = new ArrayList<Integer>();
		numbers.add(value);
		binary = binaryExpand(value);
		prime = true;
		this.bitCounter();
	}
	/**
	 * Numbers Represented by The binary Representation.
	 */
	private ArrayList<Integer> numbers;
	/**
	 * Constructor for a list of elements with only one
	 * integer entered to be stored in this row.
	 * @param bitsNumber
	 * the number of bits to be in the String representation.
	 * @param list
	 * the numbers to be saved and represented
	 * Should automatically set all the other variables of the node.
	 * sets variableNumber to bitsNumber.
	 */
	public NodeT(final int bitsNumber, final ArrayList<Integer> list) {
		variablesNumber = bitsNumber;
		numbers = new ArrayList<Integer>();
		for (int i = 0; i < list.size(); i++) {
			numbers.add(list.get(i));
		}
		binaryExpress();
		bitCounter();
		prime = true;
	}
	/**
	 * Is this expression Prime Implicant.
	 */
	private Boolean prime;
	/**
	 * How many 1's does the expression have.
	 */
	private int group;
	/**
	 * Number of bits in each expression.
	 */
	private int variablesNumber;
	/**
	 * The next row in the table.
	 */
	private NodeT next;
	/**
	 * Uses the String Binary and calculates how many 1's are
	 * in the expression.
	 * Save that number in the Group variable.
	 */
	private void bitCounter() {
		int counter = 0;
		for (int i = 0; i < binary.length(); i++) {
			if (binary.charAt(i) == '1') {
				counter++;
			}
		}
		group = counter;
	}
	/**
	 * Uses List numbers and get a binary expression of them by comparing
	 * their binary Strings after getting them to the same VariableNumber
	 * (using BinaryExpand method)
	 * putting 0 if all numbers have 0 in that place
	 * putting 1 if all numbers have 1 in that place
	 * putting - for any other case.
	 * sets String Binary.
	 */
	private void binaryExpress() {
	  	ArrayList<String> v = new ArrayList<String>();
		for (int i = 0; i < numbers.size(); i++) {
	  		String now = binaryExpand(numbers.get(i));
	  		v.add(now);
	  	}
		boolean check = false;
		StringBuilder collect = new StringBuilder();
		String l = v.get(0);
		for (int j = 0; j < v.get(0).length(); j++) {
			check = false;
			for (int k = 1; k < v.size(); k++) {
				String p = v.get(k);
				if (l.charAt(j) == p.charAt(j)) {
					check = false;
				} else {
					check = true;
					k = v.size();
				}
			}
			if (check) {
				collect.append("-");
			} else {
				collect.append(l.charAt(j));
			}
		}
		binary = collect.toString();
	}
	/**
	 *
	 * @return
	 * the binary expression of the element.
	 */
	public final String getBinary() {
		return binary;
	}
	/**
	 *
	 * @return
	 * return true if it is prime.
	 */
	public final boolean getPrime() {
		return prime;
	}
	/**
	 * Sets a new value for prime .
	 * @param status
	 * the new value for prime.
	 */
	public final void setPrime(final boolean status) {
		prime = status;
	}
	/**
	 * gets an int element and return its binary according to the
	 * variableNumber
	 * ex: variableNumber = 3 and element =1 ; should return "011".
	 * @param m
	 * number to be transformed to binary
	 * @return
	 * the String representation with a suitable number of elements.
	 */
	private String binaryExpand(final int m) {
		int k = m;
		ArrayList<Integer> c = new ArrayList<Integer>();
		ArrayList<Integer> f = new ArrayList<Integer>();
		while (k > 0) {
			c.add(k % 2);
			k /= 2;
		}
		for (int i = 0; i < c.size(); i++) {
			f.add(i, c.get(c.size() - i - 1));
		}
		if (f.size() < variablesNumber) {
			for (int j = f.size(); j < variablesNumber; j++) {
				f.add(0, 0);
			}
		}
		StringBuilder here = new StringBuilder();
		for (int i = 0; i < f.size(); i++) {
			here.append(f.get(i));
		}
		return here.toString();
	}
	/**
	 * @return
	 * returns the next node.
	 */
	public final NodeT getNext() {
		return next;
	}
	/**
	 *
	 * @param nodeNode
	 * new node to be next.
	 */
	public final void setNext(final NodeT nodeNode) {
		next = nodeNode;
	}
	/**
	 *
	 * @return
	 * returns the group of the binary expression.
	 */
	public final int getGroup() {
		return group;
	}
	/**
	 *
	 * @return
	 * return the numbers represented by this node.
	 */
	public final ArrayList<Integer> getNumber() {
		return numbers;
	}
	/**
	 * Sets all the parameters for a new List of numbers.
	 * @param list
	 * list of new numbers.
	 */
	public final void setNumbers(final ArrayList<Integer> list) {
		numbers = new ArrayList<Integer>();
		for (int i = 0; i < list.size(); i++) {
			numbers.add(list.get(i));
		}
		binaryExpress();
		bitCounter();
	}
	public final int getNumberOfVariables() {
		String s = binary;
		int num = 0;
		for (int i = 0; i < s.length(); i++) {
			if (binary.charAt(i) == '1' ||
					binary.charAt(i) == '0') {
				num++;
			}
		}
		return num;
	}
	public final int getNumberOfBits() {
		return variablesNumber;
	}
}
