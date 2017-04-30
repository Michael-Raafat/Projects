package tabularCoreMethodes;

import java.util.ArrayList;
import java.util.Arrays;
/**
 *
 * @author Michael.
 *
 */
public class PetricksEngine {
	/**
	 * create a object from Petrick
	 */
	public PetricksEngine(QuineMcCluskeyApplication v) {
		// TODO Auto-generated constructor stub
		minterms = v.getMinTerms();
		for (int i=0; i < v.getPrimeCount(); i++) {
			PatricksNode modNode = new PatricksNode(v.getPrimeList().get(i), minterms);
			if (modNode.getNumber().size() != 0) {
				primeNodes.add(modNode);
			}
		}
		simple = new ArrayList<PatricksSol>();
		this.ColRowD();
		PatricksSol tempsol = new PatricksSol();
		this.Petricks(tempsol);
		this.PetricksSolutionsMini();
		this.expression();
	}
	/**
	 * minterms arraylist.
	 */
	private ArrayList<Integer> minterms;
	/**
	 * the minimal exp.
	 */
	private ArrayList<String> simpleExp = new ArrayList<String>();
	/**
	 * simple table to be converted to expression.
	 */
	private ArrayList<PatricksSol> simple;
	/**
	 * arraylist of expression in a design of table.
	 * an example : 00-1 + 001- will be reperesented
	 * 00-1
	 * 001-
	 */
	private ArrayList<PatricksNode> primeNodes = new ArrayList<PatricksNode>();
	/**
	 * write expression with variables 
	 * @param table
	 * This function gets and sets the minimal expression.
	 */
	public void expression(){
		StringBuilder be = new StringBuilder();
		for (int k = 0; k < minimalSol.size(); k++) {
			PatricksSol table = minimalSol.get(k);
			for (int i = 0; i < table.getSize(); i++) {
				PatricksNode s = table.getPNode(i);
				String node = s.getBinary();
				for (int j = 0; j < node.length(); j++) {
					switch (node.charAt(j)) {
					case '0':
						int y = 65+j;
						be.append(Character.toString((char)y)+"'");
						break;
					case '1':
						int x = 65+j;
						be.append(Character.toString((char)x));
						break;	
					default:
						break;
					}
				}
				if (i != table.getSize() - 1) {
					be.append(" + ");
				}
			}
			if (be.length() == 0) {
				be.append(1);
			}
			simpleExp.add(be.toString());
			be = new StringBuilder();
		}
	}
	public boolean isRDominated(PatricksNode n1, PatricksNode n2) {
		boolean contained = true;
		if (n2.getNumber().size() == n1.getNumber().size()) {
			return false;
		}
		for (int i=0 ; i < n2.getNumber().size() && contained; i++) {
			contained = false;
			for (int j = 0; j < n1.getNumber().size() && !contained; j++) {
				if(n2.getNumber().get(i) == n1.getNumber().get(j)) {
					contained = true;
				}
			}
		}
		return contained;
	}
	public void RowDominance() {
		boolean exit = false;
		for (int i = 0; i < primeNodes.size() ; i++) {
			exit = false;
			for (int j = 0; j < primeNodes.size() && !exit ; j++) {
				if (i != j && isRDominated(primeNodes.get(i), primeNodes.get(j))) {
					primeNodes.remove(j);
					j--;
					i--;
					exit = true;
				}
			}
		}
	}
	public boolean isCDominated(int n1, int n2) {
		boolean contained = true;
		for (int i=0 ; i < primeNodes.size() && contained; i++) {
			if(primeNodes.get(i).getNumber().contains(n2)) {
				contained = false;
				if(primeNodes.get(i).getNumber().contains(n1)) {
					contained = true;
				}
			}
		}
		return contained;
	}
	public void ColDominance() {
		boolean exit = false;
		for (int i = 0; i < minterms.size() ; i++) {
			exit = false;
			for (int j = 0; j < minterms.size() && !exit; j++) {
				if (i != j && isCDominated(minterms.get(i), minterms.get(j))) {
					minterms.remove(i);
					i--;
					exit = true;
				}
			}
		}
		ArrayList <PatricksNode> temp = new ArrayList <PatricksNode>();
		for (int i=0; i < primeNodes.size(); i++) {
			PatricksNode modNode = new PatricksNode(primeNodes.get(i), minterms);
			if (modNode.getNumber().size() != 0) {
				temp.add(modNode);
			}
		}
		primeNodes = temp;
	}
	public void ColRowD () {
		int n = minterms.size();
		int m = primeNodes.size();
		boolean changed = true;
		while (changed) {
			changed = false;
			this.RowDominance();
			this.ColDominance();
			if (n != minterms.size()) {
				n = minterms.size();
				changed = true;
			}
			if (m != primeNodes.size()) {
				m = primeNodes.size();
				changed = true;
			}
		}
	}
	private ArrayList<Integer> visited = new ArrayList<Integer>();
	private int minSolLen = 4000;
	public void Petricks(PatricksSol s) {
		for (int m = 0 ; m < primeNodes.size(); m++) {
			if (!visited.contains(m) && visited.size() != primeNodes.size()) {
				visited.add(m);
				PatricksSol n = new PatricksSol();
				s.copySol(n);
				n.addPNode(primeNodes.get(m));
				if (n.isCompleteSol(minterms)) {
					if (n.getSize() < minSolLen) {
						minSolLen = n.getSize();
					}
					simple.add(n);
				} else {
					Petricks(n);
				}
				visited.remove(visited.size() - 1);
			}
		}
	}
	private ArrayList<PatricksSol> minimalSol = new ArrayList<PatricksSol>();
	public void PetricksSolutionsMini() {
		for (int i = 0 ; i <simple.size(); i++) {
			if(simple.get(i).getSize() == minSolLen
				&& !inMinimalAlready(simple.get(i))) {
				minimalSol.add(simple.get(i));
			}
		}
	}
	public boolean inMinimalAlready(PatricksSol s) {
		boolean found = false;
		for (int i=0; i < minimalSol.size() && !found ; i++) {
			if(twoEqualSol(s, minimalSol.get(i))) {
				found = true;
			}
		}
		return found;
	}
	public boolean twoEqualSol(PatricksSol s1, PatricksSol s2) {
		if(s1.getSize() != s2.getSize()) {
			return false;
		}
		boolean equal = true;
		for (int i = 0; i < s1.getPNodes().size() && equal ;i++) {
			equal = false;
			for (int j = 0; j < s2.getPNodes().size() && !equal ;j++) {
				if (s1.getPNode(i).getBinary() == s2.getPNode(j).getBinary()) {
					equal = true;
				}
			}
		}
		return equal;
	}
	public ArrayList<String> getAnswer() {
		return simpleExp;
	}
}
