class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
        self.prev = None

class DoublyLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None

    # Вставка в конец списка
    def append(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = self.tail = new_node
        else:
            new_node.prev = self.tail
            self.tail.next = new_node
            self.tail = new_node

    # Вставка в начало списка
    def prepend(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = self.tail = new_node
        else:
            new_node.next = self.head
            self.head.prev = new_node
            self.head = new_node

    # Печать списка
    def print_list(self):
        current = self.head
        result = []
        while current:
            result.append(current.data)
            current = current.next
        print(result)

    # Реверс списка
    def reverse(self):
        current = self.head
        prev_node = None
        self.tail = self.head
        while current:
            next_node = current.next
            current.next = prev_node
            current.prev = next_node
            prev_node = current
            current = next_node
        self.head = prev_node

    def sort(self):
        if not self.head or not self.head.next:
            return
        swapped = True
        while swapped:
            swapped = False
            current = self.head
            while current.next:
                if current.data > current.next.data:
                    current.data, current.next.data = current.next.data, current.data
                    swapped = True
                current = current.next

    def sort_to_new_list(self):
        lst = []
        current = self.head
        while current:
            lst.append(current.data)
            current = current.next
        lst.sort()
        new_list = DoublyLinkedList()
        for val in lst:
            new_list.append(val)
        return new_list

# ---------------- Тестирование ----------------
dll = DoublyLinkedList()
for val in [5.2, 3.1, 4.8, 2.9, 5.0]:
    dll.append(val)

print("Исходный список:")
dll.print_list()

dll.reverse()
print("Разворот списка:")
dll.print_list()

dll.sort()
print("Сортировка на месте:")
dll.print_list()

dll2 = dll.sort_to_new_list()
print("Индивидуальное задание №4 - новый список по возрастанию:")
dll2.print_list()
class Node:
    def __init__(self, data):
        self.data = data
        self.next = None
        self.prev = None

class DoublyLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None

    # Вставка в конец списка
    def append(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = self.tail = new_node
        else:
            new_node.prev = self.tail
            self.tail.next = new_node
            self.tail = new_node

    # Вставка в начало списка
    def prepend(self, data):
        new_node = Node(data)
        if not self.head:
            self.head = self.tail = new_node
        else:
            new_node.next = self.head
            self.head.prev = new_node
            self.head = new_node

    # Печать списка
    def print_list(self):
        current = self.head
        result = []
        while current:
            result.append(current.data)
            current = current.next
        print(result)

    # Реверс списка
    def reverse(self):
        current = self.head
        prev_node = None
        self.tail = self.head
        while current:
            next_node = current.next
            current.next = prev_node
            current.prev = next_node
            prev_node = current
            current = next_node
        self.head = prev_node

    def sort(self):
        if not self.head or not self.head.next:
            return
        swapped = True
        while swapped:
            swapped = False
            current = self.head
            while current.next:
                if current.data > current.next.data:
                    current.data, current.next.data = current.next.data, current.data
                    swapped = True
                current = current.next

    def sort_to_new_list(self):
        lst = []
        current = self.head
        while current:
            lst.append(current.data)
            current = current.next
        lst.sort()
        new_list = DoublyLinkedList()
        for val in lst:
            new_list.append(val)
        return new_list

# ---------------- Тестирование ----------------
dll = DoublyLinkedList()
for val in [5.2, 3.1, 4.8, 2.9, 5.0]:
    dll.append(val)

print("Исходный список:")
dll.print_list()

dll.reverse()
print("Разворот списка:")
dll.print_list()

dll.sort()
print("Сортировка на месте:")
dll.print_list()

dll2 = dll.sort_to_new_list()
print("Индивидуальное задание №4 - новый список по возрастанию:")
dll2.print_list()
Исходный список:
[5.2, 3.1, 4.8, 2.9, 5.0]
Разворот списка:
[5.0, 2.9, 4.8, 3.1, 5.2]
Сортировка на месте:
[2.9, 3.1, 4.8, 5.0, 5.2]
Индивидуальное задание №4 - новый список по возрастанию:
[2.9, 3.1, 4.8, 5.0, 5.2]
