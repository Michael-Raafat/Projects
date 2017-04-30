package tabularCoreMethodes.tests;


import java.util.ArrayList;

import org.junit.Assert;
import org.junit.Test;

import tabularCoreMethodes.NodeT;
import tabularCoreMethodes.Table;

public class TableTesting {

	@Test
	public void test() {
		Table t = new Table(3);
		t.addNodeNumber(5);
		t.addNodeNumber(2);
		t.addNodeNumber(1);
		t.addNodeNumber(7);
		NodeT n = new NodeT(3,1);
		NodeT m = new NodeT(3,5);
		Assert.assertEquals(4, t.getSize());
		Assert.assertEquals(n.getBinary(), t.getNode(2).getBinary());
		t.removeNode(1);
		Assert.assertEquals(n.getBinary(), t.getNode(1).getBinary());
		t.sortTable();
		Assert.assertEquals(m.getBinary(), t.getNode(1).getBinary());
		m = new NodeT(3,7);
		Assert.assertEquals(m.getBinary(), t.getNode(2).getBinary());
		m = new NodeT(3,1);
		Assert.assertEquals(m.getBinary(), t.getNode(0).getBinary());
		Assert.assertEquals(3, t.getSize());
		Table tt = new Table();
		ArrayList<Integer> list = new ArrayList<Integer>();
		list.add(7);
		list.add(5);
		list.add(1);
		list.add(2);
		list.add(1);
		tt.setTable(list);
		Assert.assertEquals(4, tt.getSize());
		m = new NodeT(3,1);
		Assert.assertEquals(m.getBinary(), tt.getNode(0).getBinary());
		m = new NodeT(3,2);
		Assert.assertEquals(m.getBinary(), tt.getNode(1).getBinary());
		m = new NodeT(3,5);
		Assert.assertEquals(m.getBinary(), tt.getNode(2).getBinary());
		m = new NodeT(3,7);
		Assert.assertEquals(m.getBinary(), tt.getNode(3).getBinary());
		list.clear();
		list.add(0);
		list.add(1);
		Table testing = new Table(3);
		Table getting = new Table();
		testing.addNode(list);
		list.clear();
		list.add(0);
		list.add(2);
		testing.addNode(list);
		list.clear();
		list.add(1);
		list.add(3);
		testing.addNode(list);
		list.clear();
		list.add(1);
		list.add(5);
		testing.addNode(list);
		list.clear();
		list.add(2);
		list.add(3);
		testing.addNode(list);
		list.clear();
		list.add(0);
		list.add(1);
		list.add(2);
		list.add(3);
		list.add(5);
		getting.setTable(list);
		for(int i=0;i<testing.getSize();i++) {
			Assert.assertEquals(testing.getNode(i).getBinary(), getting.tabularMethodComparison().getNode(i).getBinary());
		}
		Table table2 = getting.tabularMethodComparison();
		Table table3 = table2.tabularMethodComparison();
		list.clear();
		list.add(0);
		list.add(1);
		list.add(2);
		list.add(3);
		NodeT end = new NodeT(3,list);
		Assert.assertEquals(end.getBinary(), table2.tabularMethodComparison().getNode(0).getBinary());
		Assert.assertEquals(1, table3.getSize());
		Assert.assertEquals(null, table3.tabularMethodComparison());
	}

}
