void kruskal(int n, vector<Edge>& edges) {
	makeSet(n);
	sort(edges.begin(), edges.end()); //weight에 대해 sort

	for (Edge e : edges) { //작은 간선부터 순서대로
		if (find(e.u) != find(e.v)) { //같은 그룹이 아니면
			unionSets(e.u, e.v); //간선 선택
		}
	}
}
