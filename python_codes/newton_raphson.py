import numpy as np
import matplotlib.pyplot as plt

def derivada_numerica(f, x, h=1e-5):
    return (f(x + h) - f(x - h)) / (2 * h)


def newton_raphson(f, x0, erro_min, max_iter=100):
    pontos = []
    erro = 100
    i = 0

    x = x0

    while erro > erro_min and i < max_iter:
        pontos.append(x)

        df = derivada_numerica(f, x)

        if abs(df) < 1e-12:
            raise ValueError("Derivada muito próxima de zero!")

        x_new = x - f(x) / df

        # erro relativo percentual
        erro = abs((x_new - x) / x_new) * 100

        print(f"Iteração {i+1}: x = {x_new:.6f}, erro = {erro:.6f}%")

        x = x_new
        i += 1

    print(f"\nFinalizou em {i} iterações")
    return x, pontos

if __name__ == "__main__":

    def f(x):
        return x**3 - x - 2

    x0 = 1.5

    raiz, pontos = newton_raphson(f, x0, erro_min=0.01)

    print(f"Raiz aproximada: {raiz}")