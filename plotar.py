import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# 1. Carregar os dados gerados pelo C
df = pd.read_csv('dados_bissecao.csv')

# 2. Definir a função para o gráfico de fundo
# IMPORTANTE: Mude esta linha para a mesma função que você usou no C
# Lembre-se: em Python, potência é ** (ex: x**2 em vez de x^2)
def f(x):
    return x**2 - 2 

# 3. Criar o intervalo do gráfico baseado no 'a' e 'b' iniciais do C
x_plot = np.linspace(df['a'].min() - 1, df['b'].max() + 1, 400)
y_plot = f(x_plot)

plt.figure(figsize=(10, 6))

# Desenha a curva da função
plt.plot(x_plot, y_plot, label='f(x)', color='blue', linewidth=2)
plt.axhline(0, color='black', linestyle='--', linewidth=1) # Linha do zero

# Desenha o caminho que a Bisseção fez (pontos c)
plt.scatter(df['c'], df['fc'], color='red', label='Iterações (c)', zorder=5)
plt.plot(df['c'], df['fc'], color='red', alpha=0.3, linestyle='--')

# Destaca a última raiz encontrada
ultima_raiz = df['c'].iloc[-1]
plt.plot(ultima_raiz, f(ultima_raiz), 'go', markersize=10, label=f'Raiz: {ultima_raiz:.5f}')

plt.title('Convergência do Método da Bisseção (C -> Python)')
plt.xlabel('x')
plt.ylabel('f(x)')
plt.legend()
plt.grid(True)
plt.show()