from cyaron import *

_n = [0, 5, 14, 250, 444, 888, 19772, 47960, 77952, 97876, 7892, 19782, 47000, 78999, 98765, 8765, 19876, 48000, 78999, 98789, 9879, 19949, 49494, 79797, 99123, 99345]
_m = ati([0, 10, 20, 249, 443, 887, 19771, 47959, 77951, 97875, 7891, 19781, 46999, 78998, 98764, 2e4, 4e4, 6e4, 1e5, 1e5, 2e4, 4e4, 6e4, 1e5, 1e5, 1e5])
_q = ati([0, 20, 20, 1e3, 1e3, 1e3, 1e5, 1e5, 1e5, 1e5, 1e5, 1e5, 1e5, 1e5, 1e5, 1e5, 1e5, 1e5, 1e5, 1e5, 1e5, 1e5, 1e5, 1e5, 1e5, 1e5])
_t = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1]

for T in range(1, 26):
    print T
    test_data = IO(file_prefix="harmonics", data_id=T)

    n = _n[T]
    m = _m[T]
    q = _q[T]

    if m == n-1:
        tree = Graph.tree(n, 0.4, 0.4)
    else:
        tree = Graph.tree(n, 0.3, 0.3)

    exG = Graph.graph(n, m-n+1, self_loop=False, repeated_edges=False)
    graph = Graph(n)
    m = 0
    for t_e in tree.iterate_edges():
        exist = False
        for g_e in exG.edges[t_e.start]:
            if t_e.end == g_e.end:
                exist = True
                break
        if exist == False:
            graph.add_edge(t_e.start, t_e.end)
            m += 1
    for e in exG.iterate_edges():
        graph.add_edge(e.start, e.end)
        m += 1
    test_data.input_writeln(n, m, q)

    for i in range(1, n+1):
        test_data.input_write(randint(1, 1e9))
    test_data.input_writeln()

    test_data.input_writeln(graph.to_str(output=Edge.unweighted_edge, shuffle=True))

    for i in range(1, q):
        t = randint(0, _t[T])
        if t == 1:
            x = randint(1, n)
            y = randint(1, 1e9)
            test_data.input_writeln('C', x, y)
        else:
            x = randint(1, n)
            y = randint(1, n)
            while y == x:
                y = randint(1, n)
            test_data.input_writeln('Q', x, y)
