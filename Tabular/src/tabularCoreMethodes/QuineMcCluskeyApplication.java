package tabularCoreMethodes;

import java.util.ArrayList;
/**
 *
 * @author Michael.
 * The application that solves the problem.
 */
public class QuineMcCluskeyApplication {
	/**
	 * List of tables done to solve the problem.
	 */
	private ArrayList<Table> tables;
	/**
	 * lists saving the minterms numbers in minterms list
	 * and minterms+don't care in all numbers.
	 */
	private ArrayList<Integer> allnumbers, minterms;
	/**
	 * Saving the primeNodes found in tables list.
	 */
	private ArrayList<NodeT> primeNodes;
	/**
	 * Constructor initializing all lists.
	 */
	public QuineMcCluskeyApplication() {
		// TODO Auto-generated constructor stub
		tables = new ArrayList<Table>();
		allnumbers = new ArrayList<Integer>();
		minterms = new ArrayList<Integer>();
		primeNodes = new ArrayList<NodeT>();
	}
	/**
	 * Sets the lists minterms and all numbers from two lists.
	 * @param m
	 * list of minterm expressions
	 * @param d
	 * list of don't care expressions
	 */
	public void setLists(final ArrayList<Integer> m,
			final ArrayList<Integer> d) {
		for (int i = 0; i < m.size(); i++) {
			minterms.add(m.get(i));
			allnumbers.add(m.get(i));
		}
		if (d == null) {
			return;
		}
		for (int i = 0; i < d.size(); i++) {
			allnumbers.add(d.get(i));
		}
	}
	/**
	 * Sets the first table with the all numbers list.
	 * adds the table to the list tables.
	 */
	public void settingTable() {
		Table table = new Table();
		table.setTable(allnumbers);
		tables.add(table);
	}
	/**
	 * Uses the already set Table in the tables list
	 * to generate the other tables using tabularmethodComparison
	 * method and stops when the method returns null
	 * adding each new table to the tables list.
	 */
	public void gettingTables() {
		int i = 0;
		while (tables.get(i)!= null) {
			tables.add(tables.get(i).tabularMethodComparison());
			i++;
		}
		tables.remove(i);
	}
	/**
	 * Goes through the tables list and takes each table
	 * and search for the nodes that has prime -> true
	 * and adds them to the list Primenodes.
	 */
	public void gettingPrimes() {
		for (int i = 0; i < tables.size(); i++) {
			Table table = tables.get(i);
			for (int j = 0; j < table.getSize(); j++) {
				if (table.getNode(j).getPrime()) {
					primeNodes.add(table.getNode(j));
				}
			}
		}
	}
	/**
	 * Returns a String format of the node containing all
	 * the important information of the node from a certain table.
	 * @param i
	 * The index of the table in the list tables.
	 * @param j
	 * the index of the node in the chosen table.
	 * @return
	 * A String representation of the node.
	 */
	public final String getRow(final int i, final int j) {
		StringBuilder row = new StringBuilder();
		row.append("| " + tables.get(i).getNode(j).getNumber().toString() + " (");
		row.append(tables.get(i).getNode(j).getBinary() + ") ");
		row.append(tables.get(i).getNode(j).getPrime()+"|");
		return row.toString();
	}
	/**
	 * Returns a proper String format for a prime node.
	 * @param i
	 * index of the node in the primeNodes list.
	 * @return
	 * A String Representation of a prime Node.
	 */
	public final String getPrime(final int i) {
		StringBuilder row = new StringBuilder();
		row.append("| " + primeNodes.get(i).getNumber().toString() + " (");
		row.append(primeNodes.get(i).getBinary() + ") ");
		row.append(primeNodes.get(i).getPrime()+"|");
		return row.toString();
	}
	/**
	 * returns the length of the primeNodes list.
	 * @return
	 * the length of the primeNodes list.
	 */
	public final int getPrimeCount() {
		return primeNodes.size();
	}
	/**
	 * @return
	 * the length of the tables list.
	 */
	public final int getTablesCount() {
		return tables.size();
	}
	/**
	 * @return
	 * the list of primeNodes.
	 */
	public final ArrayList<NodeT> getPrimeList() {
		return primeNodes;
	}
	/**
	 * @param i
	 * the index of the table in the list tables.
	 * @return
	 * the length of that table at the index i in the list tables.
	 */
	public final int getTableLength(final int i) {
		return tables.get(i).getSize();
	}
	/**
	 * @return
	 * the list of min terms to be handled in the PetricksEngine.
	 */
	public final ArrayList<Integer> getMinTerms() {
		return minterms;
	}
}
