package question2;

import java.math.BigInteger;

/**
 * 
 * @author michael.
 *
 */
public class ExtendedEuclid {
	public BigInteger euclid(BigInteger a, BigInteger b, BigInteger c, BigInteger d) {
		if (b.equals(BigInteger.ZERO)) {
			return d;
		} else {
			return euclid(b , a.mod(b), d.subtract((a.divide(b)).multiply(c)), c);
		}
		
	}
	
	public BigInteger euclid2(BigInteger n, BigInteger b, BigInteger c, BigInteger d) {
        BigInteger x = n;
		while (!b.equals(BigInteger.ZERO)) {
        	BigInteger temp ;
        	temp = c;
			c = d.subtract((n.divide(b)).multiply(c));
			d = temp;
			temp = b;
        	b = n.mod(b);
        	n = temp;
		}
        return d.mod(x);
	}
	
	public boolean isOne(BigInteger n, BigInteger a) {
		if (a.equals(BigInteger.ZERO)) {
			return false;
		}else if (a.equals(BigInteger.ONE)) {
			return true;
		} else {
			return isOne(a , n.mod(a));
		}
		
	}
}
