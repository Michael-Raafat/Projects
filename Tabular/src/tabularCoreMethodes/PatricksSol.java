package tabularCoreMethodes;

import java.util.ArrayList;

public class PatricksSol {
	private ArrayList<PatricksNode> list = new ArrayList<PatricksNode>();
	private ArrayList<Integer> numberContained = new ArrayList<Integer>();
	private int size = 0;
	public int getSize() {
		return size;
	}
	public void addPNode(PatricksNode s) {
		for(int i = 0; i < s.getNumber().size(); i++) {
			if (!numberContained.contains(s.getNumber().get(i))) {
				numberContained.add(s.getNumber().get(i));
			}
		}
		list.add(s);
		size++;
	}
	public boolean isCompleteSol(ArrayList<Integer> minTerms) {
		boolean check = true;
		for (int i=0 ; i< minTerms.size() && check; i++) {
			check = false;
			if(numberContained.contains(minTerms.get(i))) {
				check = true;
			}
		}
		return check;
	}
	public PatricksNode getPNode(int index) {
		return list.get(index);
	}
	public void copySol(PatricksSol m) {
		for (int i = 0 ; i < list.size(); i++) {
			m.addPNode(this.getPNode(i));
		}
	}
	public ArrayList<PatricksNode> getPNodes() {
		return list;
	}
}
