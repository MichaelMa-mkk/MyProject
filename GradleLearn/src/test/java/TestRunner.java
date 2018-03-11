import static org.junit.Assert.assertEquals;
import org.junit.Test;
import java.io.IOException;
import java.util.Vector;

public class TestRunner {
    @Test
    public void TestAccess() throws IOException {
        Graph t = new Graph();
        t.init("bed", "bar");
        boolean A = t.access("bed", "bar");
        assertEquals(true, A);
    }
    @Test
    public void TestLadder() throws IOException {
        Graph t = new Graph();
        t.init("bed", "bar");
        Vector<String> path = new Vector<>();
        int A = t.getLadder("bed", "bar", path);
        assertEquals(2, A);
    }
}
