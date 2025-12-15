# Лабораторная работа: Криптоалгоритмы
# Бахал И.А., ИУ10-38, вариант 4

"""
Цель работы
Получение практических навыков защиты программного обеспечения от несанкционированного доступа 
путем шифрования с использованием криптоалгоритмов.

Задачи лабораторной работы:
1. Реализовать симметричный шифр (книжный шифр)
2. Реализовать асимметричный шифр (Гольдвассер — Микали)
3. Продемонстрировать шифрование и расшифровку текста
4. Проверить корректность работы алгоритмов
"""

import random

# =============================
# Симметричный шифр: Книжный шифр
# =============================

def generate_book_key(text: str, key: str) -> list[int]:
    """
    Формируем ключ для книжного шифра на основе строки key.
    Преобразуем ключ в список сдвигов для каждой буквы.
    """
    key_nums = [ord(c) for c in key] # преобразуем символы ключа в числовые коды
    key_extended = (key_nums * ((len(text) // len(key_nums)) + 1))[:len(text)] # повторяю ключ, чтобы его длина совпала с длиной текста
    return key_extended # djpdhfof. e;t ujnjdsq rk.x

def book_encrypt(plaintext: str, key: str) -> str:
    key_seq = generate_book_key(plaintext, key) # получаем последовательность числовых сдвигов
    ciphertext = ''.join(chr((ord(p) + k) % 65536) for p, k in zip(plaintext, key_seq)) # шифруем каждый символ с помощью сдвига по Unicode(сдвиг символа и защита от переполнения)
    return ciphertext # возвращаем зашифрованный текст

def book_decrypt(ciphertext: str, key: str) -> str:
    key_seq = generate_book_key(ciphertext, key) # сформирую тот ж ключ, что и при шифровании
    plaintext = ''.join(chr((ord(c) - k) % 65536) for c, k in zip(ciphertext, key_seq)) # выполняем обратный сдвиг символов
    return plaintext # возвращаем исходный текст

# =============================
# Асимметричный шифр: Гольдвассер — Микали
# =============================

def is_prime(n: int) -> bool:  # проверка числа на простоту
    if n <= 1:
        return False  # числа меньше 2 не простые
    if n <= 3:
        return True # 2 и 3 простые
    if n % 2 == 0 or n % 3 == 0:
        return False # отбрасываем чётные и кратные 3
    i = 5
    while i * i <= n:  # проверяем делители до корня
        if n % i == 0 or n % (i+2) == 0:
            return False # нашли делитель
        i += 6
    return True  # в таком случае число простое

def generate_gm_keys() -> tuple[int, int, int]:
    """
    Генерация простых чисел p, q и открытого/закрытого ключа для GM
    """
    primes = [i for i in range(3, 100) if is_prime(i)] # формируем список простых чисел
    p = random.choice(primes)
    q = random.choice([x for x in primes if x != p]) # случайно выбираем два разных простых числа
    n = p * q # вычисляем модуль n
    return n, p, q # n — открытый ключ, p и q — закрытые

def gm_encrypt_bit(m: int, n: int) -> int:
    """
    Шифрование одного бита (0 или 1) по схеме Гольдвассер — Микали
    """
    while True:
        x = random.randint(1, n-1) # генерируем рандомное число
        if pow(x, 2, n) != 1:
            break
    c = pow(x, 2, n) * (1 if m == 0 else -1) % n  # вычисляет (x² mod n) (важно, чтобы x² mod n ≠ 1 иначе шифрование некорректно)
    return c  # возвращаем зашифрованный бит

def text_to_bits(text: str) -> list[int]:
    """Преобразуем текст в последовательность битов"""
    bits = []
    for char in text:
        bin_str = format(ord(char), '016b') # добавляем каждый бит в список
        bits.extend(int(b) for b in bin_str)
    return bits # возвращаем список битов

# =============================
# Демонстрация работы
# =============================

if __name__ == '__main__':
    plaintext = "Привет, мир!" # наш текст
    key = "фф12К52"  # ключ для книжного шифра

    # --- Книжный шифр ---
    cipher_book = book_encrypt(plaintext, key)
    decipher_book = book_decrypt(cipher_book, key)

    print("=== Книжный шифр ===")
    print("Исходный текст:", plaintext)
    print("Зашифрованный текст:", cipher_book)
    print("Расшифрованный текст:", decipher_book)

    # --- Гольдвассер — Микали ---
    n, p, q = generate_gm_keys()
    print("\n=== Гольдвассер — Микали ===")
    print("Открытый модуль n:", n)
    print("Простые числа p, q:", p, q)

    bits = text_to_bits(plaintext)
    cipher_bits = [gm_encrypt_bit(b, n) for b in bits]
    print(f"Первые 16 битов исходного текста: {bits[:16]}")
    print(f"Первые 16 зашифрованных битов: {cipher_bits[:16]}")
