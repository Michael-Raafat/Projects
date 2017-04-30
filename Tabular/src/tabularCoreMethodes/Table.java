package tabularCoreMethodes;

import java.util.ArrayList;

/**
 *
 * @author Amr
 * Table Containing all the related NodeT and responsible of organizing them.
 */
public class Table {
	/**
	 * head of the table. Contains elements !.
	 */
	private NodeT head;
	/**
	 * size of the table.
	 */
	private int size;
	/**
	 * the variableNumber of the table.
	 */
	private int maxVar;
	/**
	 * Sets a new table.
	 * @param varnum
	 * the maxVar number to build nodes with it.
	 */
	public Table(final int varnum) {
		maxVar = varnum;
		size = 0;
	}
	/**
	 * Constructor for a new table.Will need to calculate maxVar manually.
	 */
	public Table() {
		size = 0;
		maxVar = -1;
	}
	/**
	 * Compares the binary representation of the two nodes.
	 * @param node1
	 * first node to be compared.
	 * @param node2
	 * second node to be compared.
	 * @return
	 * The number of differences between 2 different nodes.
	 * If the - are not in the same place will return 1000.
	 */
	public final int compareNodes(final NodeT node1, final NodeT node2) {
		String first = node1.getBinary();
		String second = node2.getBinary();
		int s = 0, j = 0;
		for (int i = 0; i < first.length(); i++) {
			if (first.charAt(i) == second.charAt(i)) {
				s++;
			} else {
				j++;
			}
			if (j == 2) {
				break;
			}
		}
		if (first.length() == s) {
			return 0;
		} else if (s + 1 == first.length()) {
			return 1;
		} else {
			return 2;
		}
	}
	/**
	 * Compares the current table according to the tabular method
	 * by groupes.
	 * can Use compareNodes.
	 * Change prime status of nodes that will be advanced to false.
	 * creats a new table with the same MaxVar of this table
	 * and adds elements to it.
	 * @return
	 * The new Table constructed of tabular method solution.
	 * returns null if no items were added to the new table.
	 */
	public final Table tabularMethodComparison() {
		Table table = new Table(maxVar);
		int y = 0, s = 0, l = 0;
		for (int i = 0; i < size - 1; i++) {
			ArrayList<Integer> numbers = new ArrayList<Integer>();
			ArrayList<Integer> numbers1 = new ArrayList<Integer>();
			ArrayList<Integer> numbers2 = new ArrayList<Integer>();
			for (int j = i + 1; j < size
				&& this.getNode(i).getGroup() + 2
				> this.getNode(j).getGroup(); j++) {
				numbers.clear();
				if (compareNodes(getNode(i), getNode(j))
						== 1) {
					y = 0;
					s = 0;
					l = 0;
					getNode(i).setPrime(false);
					getNode(j).setPrime(false);
					numbers1 = getNode(i).getNumber();
					numbers2 = getNode(j).getNumber();
					while (y < numbers1.size()
						&& y < numbers2.size()) {
						if (numbers1.get(s)
							< numbers2.get(l)) {
							numbers.add(
							numbers1.get(s));
							s++;
						} else if (numbers1.get(s)
							> numbers2.get(l)) {
							numbers.add(
							numbers2.get(l));
							l++;
						} else {
							numbers.add(
							numbers2.get(l));
							l++;
							s++;
						}
						y++;
					}
					if (y == numbers1.size()) {
						for (int p = l; p
						< numbers2.size(); p++) {
							numbers.add(
							numbers2.get(p));
						}
					} else {
						for (int p = s; p
						< numbers1.size(); p++) {
							numbers.add(
							numbers1.get(p));
						}
					}
					table.addNode(numbers);
				}
			}
		}
		if (table.isEmpty()) {
			return null;
		} else {
			table.removeDuplicates();
			table.sortTable();
			return table;
		}
	}
	/**
	 * Sets the maxVar number to number of bits of the biggest
	 * number of the list of numbers.
	 * @param list
	 * list to get the biggest number from.
	 */
	public final void setMaxVar(final ArrayList<Integer> list) {
		int k, max = 0, s = 0;
		for (int i = 0; i < list.size(); i++) {
			k = list.get(i);
			if (k > max) {
				max = k;
			}
		}
		while (max > 0) {
			max /= 2;
			s++;
		}
		maxVar = s;
	}
	/**
	 * Sets the table for the elements in the list
	 * for each element adds a node.
	 * can use method set maxVar get biggest maxVar if
	 * maxVar is equal to -1.
	 * @param list
	 * list of numbers.
	 */
	public final void setTable(final ArrayList<Integer> list) {
		if (maxVar == -1) {
			setMaxVar(list);
		}
		for (int i = 0; i < list.size(); i++) {
			addNodeNumber(list.get(i));
		}
		this.sortTable();
		this.removeDuplicates();
	}
	/**
	 * Returns node saved in this index.
	 * @param index
	 * index to get the node from.
	 * @return
	 * the chosen node.
	 */
	public final NodeT getNode(final int index) {
		NodeT temp = head;
		int i = 0;
		while (i < index) {
			temp = temp.getNext();
			i++;
		}
		return temp;
	}
	/**
	 * removes the node at the specified index from the table.
	 * @param index
	 * the index of the node to be removed.
	 */
	public final void removeNode(final int index) {
		NodeT temp;
		if (index == 0) {
			temp = head;
			head = head.getNext();
			size--;
		} else if (index == size - 1) {
			int i = 0;
			temp = head;
			while (i < index - 1) {
				temp = temp.getNext();
				i++;
			}
			temp.setNext(null);
			size--;
		} else {
			int i = 0;
			temp = head;
			while (i < index - 1) {
				temp = temp.getNext();
				i++;
			}
			NodeT p;
			p = temp;
			temp = temp.getNext();
			p.setNext(temp.getNext());
			temp.setNext(null);
			size--;
		}
	}
	/**
	 * addes a new node to the table containing certain numbers.
	 * @param list
	 * numbers to be contained in the new node.
	 */
	public final void addNode(final ArrayList<Integer> list) {
		NodeT temp = new NodeT(maxVar, list);
		if (head == null) {
			head = temp;
			size++;
			return;
		}
		NodeT p = head;
		while (p.getNext() != null) {
			p = p.getNext();
		}
		p.setNext(temp);
		temp.setNext(null);
		size++;
	}
	/**
	 * addes a new node to the table containing certain number.
	 * can use addNode method to add the new number.
	 * @param val
	 * number to be contained in the new node.
	 */
	public final void addNodeNumber(final int val) {
		ArrayList<Integer> j = new ArrayList<Integer>();
		j.add(val);
		addNode(j);
	}
	/**
	 * remove any duplicates.
	 * duplicates are nodes having the same binary String value.
	 * Keeps one at least of each binary representation.
	 * can use method CompareNodes, and method removeNode.
	 */
	public final void removeDuplicates() {
		for (int i = 0; i < size - 1; i++) {
			for (int j = i + 1; j < size; j++) {
			if (compareNodes(getNode(i), getNode(j))
					== 0) {
				removeNode(j);
				j--;
			}
			}
		}
	}
	/**
	 * Sorts the table nodes according to their groups.
	 */
	public final void sortTable() {
		for (int i = 0; i < size - 1; i++) {
			for (int j = i + 1; j < size; j++) {
				if (this.getNode(i).getGroup()
					> this.getNode(j).getGroup()) {
					ArrayList<Integer> list
					= this.getNode(i).getNumber();
					this.getNode(i).
					setNumbers(this.getNode(j).getNumber());
					this.getNode(j).setNumbers(list);
				} else if (this.getNode(i).getGroup()
						== this.getNode(j).getGroup()) {
					if (this.getNode(i).getNumber().get(0)
						> this.getNode(j).getNumber().get(0)) {
						ArrayList<Integer> list
						= this.getNode(i).getNumber();
						this.getNode(i).
						setNumbers(this.getNode(j).getNumber());
						this.getNode(j).setNumbers(list);
					}
				}
		    }
		}

	}
	/**
	 * @return
	 * the size of table.
	 */
	public final int getSize() {
		return size;
	}
	/**
	 * @return
	 * true if the table is empty.
	 */
	public final boolean isEmpty() {
		return (size == 0);
	}
}
