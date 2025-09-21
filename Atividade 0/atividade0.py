def encontrar_primos(n):
    
    primos = [True for i in range(n + 1)]
    primos[0] = primos[1] = False # 0 e 1 não são primos

    for p in range(2, int(n**0.5) + 1):
        # Se primos[p] não foi alterado, então é um primo
        if primos[p]:
            # Atualiza todos os múltiplos de p
            for i in range(p * p, n + 1, p):
                primos[i] = False

    # Coleta os números primos
    numeros_primos_encontrados = []
    for p in range(2, n + 1):
        if primos[p]:
            numeros_primos_encontrados.append(p)

    return numeros_primos_encontrados

def main():
   
    while True:
        try:
            n_str = input("Digite um número inteiro N > 0: ")
            n = int(n_str)
            if n > 0:
                break
            else:
                print("O número deve ser maior que 0. Tente novamente.")
        except ValueError:
            print(f"Entrada inválida. '{n_str}' não é um número inteiro. Tente novamente.")

    # Encontra os primos
    primos_encontrados = encontrar_primos(n)
    quantidade_primos = len(primos_encontrados)

    # Exibe os resultados
    print("-" * 30)
    print(f"Valor de N: {n}")
    print(f"Números primos encontrados: {primos_encontrados}")
    print(f"Quantidade de números primos encontrados: {quantidade_primos}")
    print("-" * 30)

if __name__ == "__main__":
    main()