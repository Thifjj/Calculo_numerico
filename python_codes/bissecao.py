import numpy as np
import matplotlib.pyplot as plt

def bissecao(f, a, b, erro_min, max_iter=100):
    if f(a) * f(b) >= 0:
        raise ValueError("A função deve ter sinais opostos em a e b!")

    pontos = []
    i = 0
    erro = 1
    while erro > erro_min:
        
        c = (a + b) / 2
        pontos.append(c)
        if i > 1:
        # erro relativo percentual
            erro = abs((c - c_old) / c) * 100
            if erro < erro_min:
                print(f"Convergiu em {i+1} iterações")
                print(f"Erro: {erro:.6f}%")
                return c, pontos

        # atualiza intervalo
        if f(a) * f(c) < 0:
            b = c
        else:
            a = c

        c_old = c
        i +=1

    print("Número máximo de iterações atingido")
    return c, pontos


def plotar_funcao(f, a, b, raiz, pontos):
    x = np.linspace(a - 1, b + 1, 400)
    y = f(x)

    plt.figure()

    plt.plot(x, y, label="f(x)")
    plt.axhline(0)

    plt.scatter(raiz, f(raiz), label="Raiz", zorder=3)

    y_pontos = [f(p) for p in pontos]
    plt.scatter(pontos, y_pontos, marker='x', label="Iterações")

    plt.title("Método da Bisseção")
    plt.xlabel("x")
    plt.ylabel("f(x)")
    plt.legend()
    plt.grid()

    plt.show()


# ==========================
# Exemplo
# ==========================
if __name__ == "__main__":

    def f(x):
        return x**3 - x - 2

    a, b = 1, 2

    raiz, pontos = bissecao(f, a, b, erro_min=0.01)

    print(f"Raiz aproximada: {raiz}")

    plotar_funcao(f, a, b, raiz, pontos)