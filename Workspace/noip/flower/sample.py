from cyaron import *

for T in range(4, 5):
    print T
    test_data = IO(file_prefix="flower_sample", data_id=T)

    n = 500
    m = 1e5

    tree = Graph.tree(n, 0.3, 0.3, weight_limit=1000)
    exG = Graph.graph(n, m-n+1, self_loop=False, repeated_edges=False, weight_limit=1000)
    graph = Graph(n)
    m = 0
    for t_e in tree.iterate_edges():
        exist = False
        for g_e in exG.edges[t_e.start]:
            if t_e.end == g_e.end:
                exist = True
                break
        if exist == False:
            graph.add_edge(t_e.start, t_e.end, weight=t_e.weight)
            m += 1
    for e in exG.iterate_edges():
        graph.add_edge(e.start, e.end, weight=e.weight)
        m += 1
    
    test_data.input_writeln(n, m)

    test_data.input_writeln(graph.to_str(shuffle=True))

