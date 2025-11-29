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
    key_nums = [ord(c) for c in key]
    key_extended = (key_nums * ((len(text) // len(key_nums)) + 1))[:len(text)]
    return key_extended

def book_encrypt(plaintext: str, key: str) -> str:
    key_seq = generate_book_key(plaintext, key)
    ciphertext = ''.join(chr((ord(p) + k) % 65536) for p, k in zip(plaintext, key_seq))
    return ciphertext

def book_decrypt(ciphertext: str, key: str) -> str:
    key_seq = generate_book_key(ciphertext, key)
    plaintext = ''.join(chr((ord(c) - k) % 65536) for c, k in zip(ciphertext, key_seq))
    return plaintext

# =============================
# Асимметричный шифр: Гольдвассер — Микали (демо)
# =============================

def is_prime(n: int) -> bool:
    if n <= 1:
        return False
    if n <= 3:
        return True
    if n % 2 == 0 or n % 3 == 0:
        return False
    i = 5
    while i * i <= n:
        if n % i == 0 or n % (i+2) == 0:
            return False
        i += 6
    return True

def generate_gm_keys() -> tuple[int, int, int]:
    """
    Генерация простых чисел p, q и открытого/закрытого ключа для GM
    """
    primes = [i for i in range(3, 100) if is_prime(i)]
    p = random.choice(primes)
    q = random.choice([x for x in primes if x != p])
    n = p * q
    return n, p, q

def gm_encrypt_bit(m: int, n: int) -> int:
    """
    Шифрование одного бита (0 или 1) по схеме Гольдвассер — Микали
    """
    while True:
        x = random.randint(1, n-1)
        if pow(x, 2, n) != 1:
            break
    c = pow(x, 2, n) * (1 if m == 0 else -1) % n
    return c

def text_to_bits(text: str) -> list[int]:
    """Преобразуем текст в последовательность битов"""
    bits = []
    for char in text:
        bin_str = format(ord(char), '016b')
        bits.extend(int(b) for b in bin_str)
    return bits

# =============================
# Демонстрация работы
# =============================

if __name__ == '__main__':
    plaintext = "Привет, мир!"
    key = "фф12К52"

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
