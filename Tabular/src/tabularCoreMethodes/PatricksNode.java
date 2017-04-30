package tabularCoreMethodes;

import java.util.ArrayList;

public class PatricksNode {
	/**
	 * Binary representation of a few Integers.
	 */
	private String binary;
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
	public PatricksNode(final NodeT node, final ArrayList<Integer> list) {
		variablesNumber = node.getNumberOfBits();
		binary = node.getBinary();
		numbers = new ArrayList<Integer>();
		for (int i = 0; i < node.getNumber().size(); i++) {
			if(list.contains(node.getNumber().get(i))) {
				numbers.add(node.getNumber().get(i));
			}
		}
	}
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
	public PatricksNode(final PatricksNode node, final ArrayList<Integer> list) {
		variablesNumber = node.getNumberOfBits();
		binary = node.getBinary();
		numbers = new ArrayList<Integer>();
		for (int i = 0; i < node.getNumber().size(); i++) {
			if(list.contains(node.getNumber().get(i))) {
				numbers.add(node.getNumber().get(i));
			}
		}
	}
	/**
	 * Number of bits in each expression.
	 */
	private int variablesNumber;
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
