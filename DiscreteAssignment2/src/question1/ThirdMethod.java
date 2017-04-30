package question1;

import java.math.BigInteger;
import java.util.ArrayList;

public class ThirdMethod implements Methods {
	public BigInteger solve(BigInteger a, BigInteger b, BigInteger n) {
		String temp;
		// b converted to binary.
		temp = fromDecimalToBinary(b);
		BigInteger res = BigInteger.ONE;
		ArrayList<BigInteger> binaryResults = aListBinary(a, temp, n);
		for (int i = temp.length() - 1; i >= 0; i--) {
			if (temp.charAt(i) == '1') {
				res = (res.multiply(binaryResults.get(
						temp.length() - 1 - i)));
			}
		}
		return res.mod(n);
	}
	private String fromDecimalToBinary(BigInteger x) {
		String temp = x.toString(2);
		return temp;
	}
	private ArrayList<BigInteger> aListBinary(BigInteger a, String temp, BigInteger n) {
		ArrayList<BigInteger> collect = new ArrayList<BigInteger>();
		BigInteger binaryAdaptor = BigInteger.ONE.add(BigInteger.ONE);
		for (int i = 0; i < temp.length(); i++) {
			binaryAdaptor = (BigInteger.ONE.add(BigInteger.ONE)).pow(i); 
			collect.add(a.modPow(binaryAdaptor, n));
		}
		return collect;
	}

}
