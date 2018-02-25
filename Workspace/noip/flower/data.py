from cyaron import *

_n = [0, 2, 4, 6, 8, 9, 10, 123, 234, 345, 456, 121, 232, 343, 454, 122, 233, 344, 433, 455, 500]
_m = ati([0, 1, 5, 8, 15, 20, 22, 122, 233, 344, 455, 121, 232, 343, 454, 4000, 1e4, 3e4, 5e4, 8e4, 1e5])
_t = [0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0]
for T in range(1, 21):
    print T
    test_data = IO(file_prefix="flower", data_id=T)

    n = _n[T]
    m = _m[T]
    t = _t[T]

    if t == 1:
        graph = Graph.chain(n, weight_limit=1000)
    elif t   == 2:
        graph = Graph.chain(n, weight_limit=1000)
        graph.add_edge(1, n, weight=randint(1,1000))
    else:
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
