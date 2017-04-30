package question3;
import java.math.BigInteger;
import java.util.ArrayList;

import question2.ExtendedEuclid;
public class ReverseMapping {
	// Addition in ZM domain.
	public BigInteger additionZMDomain(ArrayList<BigInteger> a, ArrayList<BigInteger> b,
			ArrayList<BigInteger> m) {
		// CRT of A.
		BigInteger temp = mapToA(a, m); 
		// CRT of B.
		BigInteger temp1 = mapToA(b, m); 
		// M.
		BigInteger mCapital = BigInteger.ONE; 
		for (int i = 0; i < m.size(); i++) {
			mCapital = mCapital.multiply(m.get(i));
		}
		return (temp.add(temp1)).mod(mCapital);
	}
	// Addition in Zmi domain.
	public BigInteger additionZmiDomain(ArrayList<BigInteger> a, ArrayList<BigInteger> b,
			ArrayList<BigInteger> m) {
		// temp is a list X = A + B for each A and B
		ArrayList<BigInteger> temp = new ArrayList<BigInteger>();
		for (int i = 0; i < m.size(); i++) {
			// temp[i] = ( a[i] + b[i] ) mod m[i].
			temp.add((a.get(i).add(b.get(i))).mod(m.get(i)));
		}	
		return mapToA(temp, m); // CRT of A + B
	}
	
	// multiplication in ZM domain.
		public BigInteger multiplicationZMDomain(ArrayList<BigInteger> a, ArrayList<BigInteger> b,
				ArrayList<BigInteger> m) {
			// CRT of A.
			BigInteger temp = mapToA(a, m); 
			// CRT of B.
			BigInteger temp1 = mapToA(b, m); 
			// M.
			BigInteger mCapital = this.calculateM(m); 
			return (temp.multiply(temp1)).mod(mCapital);
		}
		// multiplication in Zmi domain.
		public BigInteger multiplicationZmiDomain(ArrayList<BigInteger> a, ArrayList<BigInteger> b,
				ArrayList<BigInteger> m) {
			// temp is a list X = A + B for each A and B
			ArrayList<BigInteger> temp = new ArrayList<BigInteger>();
			for (int i = 0; i < m.size(); i++) {
				// temp[i] = ( a[i] * b[i] ) mod m[i].
				temp.add((a.get(i).multiply(b.get(i))).mod(m.get(i)));
			}	
			return mapToA(temp, m); // CRT of A * B
		}
	
	
	public BigInteger mapToA(ArrayList<BigInteger> a, ArrayList<BigInteger> m) {
		if (a.size() != m.size()) {
			throw new RuntimeException();
		}
		// list of Mi 
		//  getMCapitalList(m) method return list of Mi by obtaining M and 
		//  dividing it with all m's except its mi
		ArrayList<BigInteger> mCapital = this.getMCapitalList(m);   
		// list of (Mi ^ -1)
		// getMCapitalInverseList(m, mCapital) method gets the multiplicative inverse list of each Mi
		ArrayList<BigInteger> mCapitalInverse = this.getMCapitalInverseList(m, mCapital);
		// Result.
		BigInteger res = BigInteger.ZERO;
		// M
		BigInteger capitalM = this.calculateM(m);
		for (int i = 0; i < m.size(); i++) {
			res = res.add((mCapital.get(i).multiply(
					mCapitalInverse.get(i)).multiply(a.get(i))).mod(capitalM));
		}
		return res.mod(capitalM);
	}
	
	private ArrayList<BigInteger> getMCapitalList(ArrayList<BigInteger> m) {
		ArrayList<BigInteger> temp = new ArrayList<BigInteger>();
		BigInteger mCapital = this.calculateM(m);
		for (int i = 0; i < m.size(); i++) {
			temp.add(mCapital.divide(m.get(i)));
		}
		return temp;
	}
	
	private ArrayList<BigInteger> getMCapitalInverseList(ArrayList<BigInteger> m,
			ArrayList<BigInteger> mCapital) {
		ArrayList<BigInteger> temp = new ArrayList<BigInteger>();
		ExtendedEuclid e = new ExtendedEuclid();
		for (int i = 0; i < m.size(); i++) {
			temp.add(e.euclid(m.get(i), mCapital.get(i),
					BigInteger.ONE, BigInteger.ZERO).mod(m.get(i)));
		}
		return temp;
	}
	
	private BigInteger calculateM(ArrayList<BigInteger> m) {
		BigInteger res = BigInteger.ONE;
		for (int i = 0; i < m.size(); i++) {
			res = res.multiply(m.get(i));
		}
		return res;
	}

}
