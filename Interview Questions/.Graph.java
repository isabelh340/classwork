import java.util.*;

public class Graph<T> {
    public final int V;
    public int e;
    public ArrayList<LinkedList<T>> adjList;

    public Graph(int V) {
	this.V = V;
	this.e = 0;
	adjList = new ArrayList<LinkedList<T>>(V);
	for (int v = 0; v < V; v++) {
	    adjList.add(v, new LinkedList<T>());
	}
    }

    public void addUndirectedEdge(T v1, T v2) {
	e++;
	adjList.get(v1).add(v2);
	adjList.get(v1).add(v2);
    }

    public void addDirectedEdge(T from, T to) {
	e++;
	adjList.get(from).add(to);
    }

    public static void bfs(Graph g, T s) {
	HashSet<Integer> white = new HashSet<T>();
	HashSet<Integer> gray  = new HashSet<T>();
	HashSet<Integer> black = new HashSet<T>();
	// need to be rewritten for template
	for (int v = 0; v < g.V; v++) {
	    if (v == s) {
		continue;
	    }
	    white.add(v);
	}
	gray.add(s);
	Queue<T> q = new LinkedList<T>();
	q.add(s);
	while (q.size() != 0) {
	    T u = q.poll();
	    System.out.println(u);
	    for (T v : g.adjList.get(u)) {
		if (white.contains(v)) {
		    white.remove(v);
		    gray.add(v);
		    q.add(v);
		} // end if
	    } // end for
	    gray.remove(u);
	    black.add(u);
	} // end while
    } // end bfs
    
    public static void main(String args[]) {
	Graph<Integer> g = new Graph<Integer>(5);
	g.addDirectedEdge(0,1);
	g.addDirectedEdge(1,2);
	g.addDirectedEdge(2,3);
	g.addDirectedEdge(2,4);
	g.addDirectedEdge(3,3);
	g.addUndirectedEdge(0,3);
	bfs(g, 0);
    }
}