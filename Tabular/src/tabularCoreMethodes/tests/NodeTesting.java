package tabularCoreMethodes.tests;


import java.util.ArrayList;

import org.junit.Assert;
import org.junit.Test;

import tabularCoreMethodes.NodeT;

public class NodeTesting {

	@Test
	public void test() {
		NodeT n = new NodeT(1,1);
		ArrayList<Integer> list = new ArrayList<Integer>();
		list.add(0);
		list.add(1);
		list.add(2);
		list.add(4);
		NodeT m = new NodeT(4,list);
		Assert.assertEquals(1, n.getGroup());
		Assert.assertEquals("1",n.getBinary());
		Assert.assertEquals(0,m.getGroup());
		Assert.assertEquals("0---", m.getBinary());
		Assert.assertTrue(m.getPrime());
		Assert.assertEquals(list, m.getNumber());
	}

}
