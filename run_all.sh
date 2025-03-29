#!/bin/bash

set -e  # Faz o script parar se qualquer comando falhar

echo "==============================="
echo "🚿 Limpando arquivos anteriores..."
make clean || { echo "❌ Erro ao limpar com make clean"; exit 1; }

echo "==============================="
echo "🔨 Compilando o projeto..."
make || { echo "❌ Erro na compilação com make"; exit 1; }

echo "==============================="
echo "🔥 Executando o resolvedor de calor..."

mkdir -p logs  # Cria pasta de logs, se não existir

./heat_solver | tee logs/saida_heat_solver.log
# 'tee' mostra a saída no terminal E salva no arquivo de log

echo "==============================="
echo "📈 Gerando gráficos com os resultados..."

echo "📊 Plotando resultado FD..."
python3 plot_fd_result.py || { echo "❌ Erro ao executar plot_fd_result.py"; exit 1; }

echo "📊 Plotando resultado FEM..."
python3 plot_fem_result.py || { echo "❌ Erro ao executar plot_fem_result.py"; exit 1; }

echo "📊 Plotando resultado EFG..."
python3 plot_efg_result.py || { echo "❌ Erro ao executar plot_efg_result.py"; exit 1; }

echo "==============================="
echo "✅ Todos os processos foram concluídos com sucesso."
