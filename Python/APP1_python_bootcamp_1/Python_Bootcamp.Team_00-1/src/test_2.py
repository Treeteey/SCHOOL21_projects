import unittest
from shortest_path import build_adjacency_list, bfs_shortest_path

class TestShortestPath(unittest.TestCase):

    @classmethod
    def setUpClass(cls):
        # Примерный граф
        cls.directed_graph = {
            "A": ["B", "C"],
            "B": ["C", "D"],
            "C": ["E"],
            "D": ["F"],
            "E": ["F", "G"],
            "F": [],
            "G": ["A"]
        }
        cls.undirected_graph = build_adjacency_list(cls.directed_graph, non_directed=True)

    def test_directed_short_path_exists(self):
        # Проверяем путь A -> F (через B, D)
        path = bfs_shortest_path(self.directed_graph, "A", "F")
        self.assertEqual(path, ["A", "B", "D", "F"])
        self.assertEqual(len(path) - 1, 3)  # Проверяем длину пути

    def test_directed_no_path(self):
        # Проверяем отсутствие пути F -> A в ориентированном графе
        path = bfs_shortest_path(self.directed_graph, "F", "A")
        self.assertEqual(path, [])

    def test_undirected_short_path(self):
        # Проверяем путь G -> F в неориентированном графе
        path = bfs_shortest_path(self.undirected_graph, "G", "F")
        possible_paths = [
            ["G", "E", "F"]
        ]
        self.assertIn(path, possible_paths)

    def test_no_start_node(self):
        # Проверяем случай, когда начальной вершины нет в графе
        path = bfs_shortest_path(self.directed_graph, "Z", "A")
        self.assertEqual(path, [])

    def test_no_end_node(self):
        # Проверяем случай, когда конечной вершины нет в графе
        path = bfs_shortest_path(self.directed_graph, "A", "Z")
        self.assertEqual(path, [])

    def test_empty_graph(self):
        # Проверяем работу алгоритма с пустым графом
        path = bfs_shortest_path({}, "A", "B")
        self.assertEqual(path, [])

    def test_large_path(self):
        # Проверяем путь, включающий большое количество узлов
        path = bfs_shortest_path(self.directed_graph, "A", "F")
        self.assertEqual(path, ["A", "B", "D", "F"])

    def test_no_path_in_disconnected_graph(self):
        # Проверяем граф, где вершины изолированы
        disconnected_graph = {"A": ["B"], "C": ["D"], "E": []}
        path = bfs_shortest_path(disconnected_graph, "A", "D")
        self.assertEqual(path, [])

    def test_directed_vs_undirected(self):
        # Сравниваем длину пути в ориентированном и неориентированном графе
        directed_path = bfs_shortest_path(self.directed_graph, "A", "G")
        undirected_path = bfs_shortest_path(self.undirected_graph, "A", "G")
        self.assertNotEqual(len(directed_path), len(undirected_path))

if __name__ == "__main__":
    unittest.main()
