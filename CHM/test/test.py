import math

# Функція для обчислення значення інтегралу методом лівих прямокутників
def left_rectangle_method(f, a, b, n):
    h = (b - a) / n
    integral = sum(f(a + i * h) for i in range(n))
    integral *= h
    return integral

# Функція для обчислення значення інтегралу методом правих прямокутників
def right_rectangle_method(f, a, b, n):
    h = (b - a) / n
    integral = sum(f(a + (i + 1) * h) for i in range(n))
    integral *= h
    return integral

# Функція для обчислення значення інтегралу методом центральних прямокутників
def central_rectangle_method(f, a, b, n):
    h = (b - a) / n
    integral = sum(f(a + (i + 0.5) * h) for i in range(n))
    integral *= h
    return integral

# Функція для обчислення значення інтегралу методом трапецій
def trapezoid_method(f, a, b, n):
    h = (b - a) / n
    integral = (f(a) + f(b)) / 2
    integral += sum(f(a + i * h) for i in range(1, n))
    integral *= h
    return integral

# Функція для обчислення значення інтегралу методом Сімпсона
def simpsons_method(f, a, b, n):
    h = (b - a) / n
    x = [a + i * h for i in range(n + 1)]
    integral = f(a) + f(b)
    integral += 4 * sum(f(x[i]) for i in range(1, n, 2))
    integral += 2 * sum(f(x[i]) for i in range(2, n - 1, 2))
    integral *= h / 3
    return integral

# Функція, для яку обчислюємо інтеграл: f(x) = e^x * cos(x)
def f(x):
    return math.exp(x) * math.cos(x)

a = 0  # Початкова точка інтегрування
b = 1  # Кінцева точка інтегрування
n = 1  # Початна кількість підінтервалів

target_error = 0.0001  # Порядок похибки

integral_exact = 1.51568  # Точне значення інтегралу для порівняння

# Обчислюємо значення інтегралу з точністю до заданого порядку похибки
while True:
    integral_left = left_rectangle_method(f, a, b, n)
    integral_right = right_rectangle_method(f, a, b, n)
    integral_central = central_rectangle_method(f, a, b, n)
    integral_trapezoid = trapezoid_method(f, a, b, n)
    integral_simpsons = simpsons_method(f, a, b, n)
    
    # Обчислюємо максимальну похибку серед методів
    max_error = max(
        abs(integral_exact - integral_left),
        abs(integral_exact - integral_right),
        abs(integral_exact - integral_central),
        abs(integral_exact - integral_trapezoid),
        abs(integral_exact - integral_simpsons)
    )
    
    # Перевіряємо, чи досягли заданого порядку похибки
    if max_error < target_error:
        break
    
    n *= 2  # Збільшуємо кількість підінтервалів для підвищення точності

print(f"Точне значення інтегралу: {integral_exact}")
print(f"За методом лівих прямокутників: {integral_left}")
print(f"За методом правих прямокутників: {integral_right}")
print(f"За методом центральних прямокутників: {integral_central}")
print(f"За методом трапецій: {integral_trapezoid}")
print(f"За методом Сімпсона: {integral_simpsons}")
print(f"Кількість підінтервалів для досягнення порядку похибки {target_error}: {n}")