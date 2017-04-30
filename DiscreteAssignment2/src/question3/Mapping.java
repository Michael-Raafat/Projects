package question3;

import java.math.BigInteger;
import java.util.ArrayList;

public class Mapping {
	public ArrayList<BigInteger> mapMultiA (BigInteger a, ArrayList<BigInteger> m) {
		ArrayList<BigInteger> temp = new ArrayList<BigInteger>();
		for (int i =0; i < m.size(); i++) {
			temp.add(a.mod(m.get(i)));
		}
		return temp;
	}
	
	
	
}
