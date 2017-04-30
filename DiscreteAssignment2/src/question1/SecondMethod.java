package question1;

import java.math.BigInteger;

public class SecondMethod implements Methods {
	public BigInteger solve(BigInteger a, BigInteger b, BigInteger n) {
		BigInteger temp = BigInteger.ONE;
		while (b.compareTo(BigInteger.ZERO) == 1) {
			temp = temp.multiply(a);
			temp = temp.mod(n);
			b = b.subtract(BigInteger.ONE);
		}
		return temp;
	}
}
