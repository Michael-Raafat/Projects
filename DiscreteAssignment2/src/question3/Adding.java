package question3;

import java.math.BigInteger;
import java.util.ArrayList;

public class Adding {
	
	public ArrayList<BigInteger> solveAddition(ArrayList<BigInteger> a,
			ArrayList<BigInteger> b, ArrayList<BigInteger> m) {
		ArrayList<BigInteger> temp = new ArrayList<BigInteger>();
		for (int i = 0; i < a.size(); i++) {
			temp.add((a.get(i).add(b.get(i))).mod(m.get(i)));
		}
		return temp;
	}

}
