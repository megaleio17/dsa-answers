# Лабораторная работа  : Двоичные деревья поиска (BST)
# Бахал И.А., ИУ10-38, вариант 4

"""
Цель работы
Изучение структуры данных «Двоичное дерево поиска», реализация операций над ним
и самобалансирующегося дерева (AVL). Для варианта 4 реализовать метод,
возвращающий поддерево, вершиной которого является максимальный элемент дерева.
"""
## Задачи лабораторной работы
1. Изучить устройство и свойства двоичного дерева поиска (BST)
2. Реализовать класс BST с основными функциями (вставка, удаление, поиск, обходы)
3. Реализовать класс AVL-дерева и механику балансировки
4. Реализовать функцию для варианта 4 — получение поддерева, вершиной которого является максимальный элемент дерева
5. Продемонстрировать работу классов на примерах


## Словесная постановка задачи
1. Изучить операции вставки, удаления и поиска в BST
2. Реализовать обходы дерева: in-order, pre-order, post-order
3. Реализовать AVL-дерево с правильными поворотами и балансировкой
4. Разработать метод subtree_of_max() для варианта 4
5. Применить реализованные структуры данных для демонстрации в main

from typing import Optional, List, Tuple


class Node:
    def __init__(self, key: int):
        self.key: int = key
        self.left: Optional['Node'] = None
        self.right: Optional['Node'] = None
        self.height: int = 1  # для AVL

    def __repr__(self):
        return f"Node({self.key})"


class BST:
    def __init__(self):
        self.root: Optional[Node] = None

    # Вставка
    def insert(self, key: int) -> None:
        self.root = self._insert_rec(self.root, key)

    def _insert_rec(self, node: Optional[Node], key: int) -> Node:
        if node is None:
            return Node(key)
        if key == node.key:
            return node  # дубликаты не добавляем
        if key < node.key:
            node.left = self._insert_rec(node.left, key)
        else:
            node.right = self._insert_rec(node.right, key)
        return node

    # Поиск
    def find(self, key: int) -> Optional[Node]:
        return self._find_rec(self.root, key)

    def _find_rec(self, node: Optional[Node], key: int) -> Optional[Node]:
        if node is None:
            return None
        if key == node.key:
            return node
        return self._find_rec(node.left, key) if key < node.key else self._find_rec(node.right, key)

    # Минимум/Максимум
    def find_min(self, node: Optional[Node] = None) -> Optional[Node]:
        node = self.root if node is None else node
        if node is None:
            return None
        while node.left:
            node = node.left
        return node

    def find_max(self, node: Optional[Node] = None) -> Optional[Node]:
        node = self.root if node is None else node
        if node is None:
            return None
        while node.right:
            node = node.right
        return node

    # Удаление
    def remove(self, key: int) -> None:
        self.root = self._remove_rec(self.root, key)

    def _remove_rec(self, node: Optional[Node], key: int) -> Optional[Node]:
        if node is None:
            return None
        if key < node.key:
            node.left = self._remove_rec(node.left, key)
        elif key > node.key:
            node.right = self._remove_rec(node.right, key)
        else:
            # случай: лист
            if node.left is None and node.right is None:
                return None
            # случай: один потомок
            if node.left is None:
                return node.right
            if node.right is None:
                return node.left
            succ = self.find_min(node.right)
            assert succ is not None
            node.key = succ.key
            node.right = self._remove_rec(node.right, succ.key)
        return node

    # Обходы
    def inorder(self) -> List[int]:
        out: List[int] = []
        self._inorder_rec(self.root, out)
        return out

    def _inorder_rec(self, node: Optional[Node], out: List[int]) -> None:
        if not node:
            return
        self._inorder_rec(node.left, out)
        out.append(node.key)
        self._inorder_rec(node.right, out)

    def preorder(self) -> List[int]:
        out: List[int] = []
        self._preorder_rec(self.root, out)
        return out

    def _preorder_rec(self, node: Optional[Node], out: List[int]) -> None:
        if not node:
            return
        out.append(node.key)
        self._preorder_rec(node.left, out)
        self._preorder_rec(node.right, out)

    def postorder(self) -> List[int]:
        out: List[int] = []
        self._postorder_rec(self.root, out)
        return out

    def _postorder_rec(self, node: Optional[Node], out: List[int]) -> None:
        if not node:
            return
        self._postorder_rec(node.left, out)
        self._postorder_rec(node.right, out)
        out.append(node.key)

    # Печать (текстовая)
    def _print_rec(self, node: Optional[Node], prefix: str = "", is_left: bool = True) -> None:
        if node is None:
            return
        print(prefix + ("├── " if is_left else "└── ") + str(node.key))
        if node.left or node.right:
            if node.left:
                self._print_rec(node.left, prefix + ("│   " if is_left else "    "), True)
            else:
                print(prefix + ("│   " if is_left else "    ") + "├── None")
            if node.right:
                self._print_rec(node.right, prefix + ("│   " if is_left else "    "), False)
            else:
                print(prefix + ("│   " if is_left else "    ") + "└── None")

    def print(self) -> None:
        if self.root is None:
            print("<пустое дерево>")
            return
        print(self.root.key)
        self._print_rec(self.root.left, "", True)
        self._print_rec(self.root.right, "", False)

    def is_empty(self) -> bool:
        return self.root is None

    def height(self) -> int:
        return self._height_rec(self.root)

    def _height_rec(self, node: Optional[Node]) -> int:
        if node is None:
            return 0
        return 1 + max(self._height_rec(node.left), self._height_rec(node.right))

    # Вариант 4: вернуть поддерево, вершиной которого является максимальный элемент дерева
    def subtree_of_max(self) -> Optional['BST']:
        max_node = self.find_max()
        if max_node is None:
            return None
        subtree = BST()
        # копируем поддерево (чтобы не ломать исходное дерево при дальнейших операциях)
        subtree.root = self._copy_subtree(max_node)
        return subtree

    def _copy_subtree(self, node: Optional[Node]) -> Optional[Node]:
        if node is None:
            return None
        new = Node(node.key)
        new.left = self._copy_subtree(node.left)
        new.right = self._copy_subtree(node.right)
        new.height = node.height
        return new


# Простая реализация AVL (на базе Node)
class AVL(BST):
    def _height(self, node: Optional[Node]) -> int:
        return node.height if node else 0

    def _update_height(self, node: Node) -> None:
        node.height = 1 + max(self._height(node.left), self._height(node.right))

    def _balance_factor(self, node: Node) -> int:
        return self._height(node.right) - self._height(node.left)

    def _rotate_right(self, y: Node) -> Node:
        x = y.left
        assert x is not None
        T2 = x.right
        x.right = y
        y.left = T2
        self._update_height(y)
        self._update_height(x)
        return x

    def _rotate_left(self, x: Node) -> Node:
        y = x.right
        assert y is not None
        T2 = y.left
        y.left = x
        x.right = T2
        self._update_height(x)
        self._update_height(y)
        return y

    def _rebalance(self, node: Node) -> Node:
        self._update_height(node)
        bf = self._balance_factor(node)
        # right heavy
        if bf > 1:
            if self._balance_factor(node.right) < 0:
                node.right = self._rotate_right(node.right)
            return self._rotate_left(node)
        # left heavy
        if bf < -1:
            if self._balance_factor(node.left) > 0:
                node.left = self._rotate_left(node.left)
            return self._rotate_right(node)
        return node

    def _insert_rec(self, node: Optional[Node], key: int) -> Node:
        if node is None:
            return Node(key)
        if key == node.key:
            return node
        if key < node.key:
            node.left = self._insert_rec(node.left, key)
        else:
            node.right = self._insert_rec(node.right, key)
        return self._rebalance(node)

    # удаление в AVL — переопределим, чтобы поддерживать баланс
    def _remove_rec(self, node: Optional[Node], key: int) -> Optional[Node]:
        if node is None:
            return None
        if key < node.key:
            node.left = self._remove_rec(node.left, key)
        elif key > node.key:
            node.right = self._remove_rec(node.right, key)
        else:
            if node.left is None:
                return node.right
            if node.right is None:
                return node.left
            succ = self.find_min(node.right)
            assert succ is not None
            node.key = succ.key
            node.right = self._remove_rec(node.right, succ.key)
        return self._rebalance(node) if node else None


# Демонстрация (вариант 4)
if __name__ == '__main__':
    print('=== ДЕМОНСТРАЦИЯ: ВАРИАНТ 4 ===')

    # Пример: формируем BST
    keys = [50, 30, 70, 20, 40, 60, 80, 75, 85]
    bst = BST()
    for k in keys:
        bst.insert(k)

    print('\nBST inorder (должно быть отсортировано):')
    print(bst.inorder())

    print('\nBST (текстовая печать):')
    bst.print()

    print('\nВысота дерева:', bst.height())

    # Найти и вывести поддерево с корнем = максимальный элемент
    subtree = bst.subtree_of_max()
    print('\nМаксимальный элемент дерева:', bst.find_max().key)
    print('Поддерево, вершиной которого является максимальный элемент:')
    if subtree:
        subtree.print()

    # Краткая проверка AVL
    avl = AVL()
    for k in [10, 20, 30, 40, 50, 25]:
        avl.insert(k)
    print('\nAVL inorder (должно быть отсортировано):', avl.inorder())
    print('AVL (текстовая печать):')
    avl.print()
    print('Высота AVL:', avl.height())

    # Демонстрация удаления
    print('\nУдаляем 70 из BST...')
    bst.remove(70)
    print('BST inorder после удаления:', bst.inorder())

    print('\n=== КОНЕЦ ДЕМОНСТРАЦИИ ===')

