# Comparação Numérica de Métodos para a Equação de Laplace

Este projeto compara três métodos numéricos para resolver o problema da distribuição de temperatura em uma placa bidimensional com condições de contorno de Dirichlet, utilizando:

- 🔹 Diferenças Finitas (FD)
- 🔸 Elementos Finitos (FEM)
- ⚫ Element Free Galerkin (EFG)

---

## 📌 Objetivos

- Implementar e comparar diferentes técnicas numéricas para um mesmo problema físico
- Avaliar desempenho, qualidade da solução e facilidade de implementação
- Fornecer uma base sólida e documentada para fins didáticos e acadêmicos

---

## 📂 Documentação

A documentação está dividida em seções independentes, acessíveis a partir dos links abaixo:

1. 📖 [Equacionamento Físico do Problema](docs/01_equationamento_fisico.md)
2. 📐 [Discretização dos Métodos](docs/02_discretizacao_metodos.md)
3. 🧠 [Algoritmos e Implementação](docs/03_algoritmos_implementacao.md)
4. 📊 [Resultados Comparativos](docs/04_resultados_comparativos.md)
5. 📚 [Referências Bibliográficas](docs/05_referencias.md)

---

## ⚙️ Compilação e Execução

### Requisitos
- C++17
- [Eigen](https://eigen.tuxfamily.org/) (biblioteca de cabeçalhos usada no método EFG)
- GNU Make
- Python 3 com `matplotlib` e `numpy` (para visualização dos resultados)

### Instalação das Dependências

#### 🪟 Windows

1. **Compilador C++ (GCC via MinGW-w64):**
   - Baixe de: https://www.mingw-w64.org/downloads/
   - Durante a instalação, inclua `g++` no PATH do sistema.

2. **GNU Make:**
   - Instale o [GnuWin32 Make](http://gnuwin32.sourceforge.net/packages/make.htm) e adicione o executável `make.exe` ao PATH.

3. **Biblioteca Eigen:**
   - Baixe de: https://gitlab.com/libeigen/eigen/-/releases
   - Extraia e coloque o diretório `Eigen` em uma pasta (ex: `C:/libs/eigen`)
   - No `Makefile`, certifique-se de incluir:
     ```make
     -I C:/libs/eigen
     ```

4. **Python 3 e pacotes:**
   - Instale via: https://www.python.org/downloads/windows/
   - Marque a opção "Add Python to PATH"
   - No terminal (Prompt de Comando), execute:
     ```bash
     pip install matplotlib numpy
     ```

#### 🐧 Linux (Ubuntu/Debian)

1. **Compilador C++ e Make:**
   ```bash
   sudo apt update
   sudo apt install build-essential
   ```

2. **Biblioteca Eigen:**
   ```bash
   sudo apt install libeigen3-dev
   ```

3. **Python 3 e pacotes:**
   ```bash
   sudo apt install python3 python3-pip
   pip3 install matplotlib numpy
   ```

---

### 🔧 Compilar

No terminal, dentro da pasta do projeto:
```bash
make
```

> O executável gerado será `heat_solver`

### ▶️ Executar

```bash
./heat_solver
```

Os resultados serão salvos no diretório `data/`, como:
- `resultado_fd.txt`
- `resultado_fem.txt`
- `resultado_efg.txt`

Além disso, o tempo de execução de cada método será salvo em `tempos_execucao.csv`.

---

## 📈 Visualizações

Os scripts Python no diretório `scripts/` permitem gerar visualizações dos resultados numéricos em formato de imagem:

```bash
python3 scripts/plot_fd_result.py
python3 scripts/plot_fem_result.py
python3 scripts/plot_efg_result.py
```

Cada script gera um gráfico de calor no diretório `plots/`:
- `fd_plot.png`
- `fem_plot.png`
- `efg_plot.png`

<div align="center">
  <img src="plots/fd_plot.png" width="30%">
  <img src="plots/fem_plot.png" width="30%">
  <img src="plots/efg_plot.png" width="30%">
</div>

---

## 🧑‍💻 Autor

Este repositório está sendo desenvolvido por [**Lucas Kriesel Sperotto**](https://github.com/Lucas-Sperotto), com foco em rigor técnico, aplicabilidade prática e fins educacionais.

---

## 📝 Licença

[MIT](LICENSE)

