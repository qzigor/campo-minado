# Campo Minado em C

Este é um projeto do jogo **Campo Minado**, desenvolvido em linguagem C, como parte do projeto final da disciplina de **Programação de Computadores 1** na **UFRJ**. O objetivo principal foi aprimorar a lógica de programação estruturada e aprofundar o conhecimento na linguagem C.

---

## 🎮 Como jogar

O jogo **Campo Minado** foi projetado para ser executado diretamente no terminal. Ao iniciar, você verá um campo de células ocultas. Seu objetivo é revelar as células, evitando as que contêm minas.

### Regras básicas:
1. Insira as coordenadas da célula que deseja revelar (linha e coluna).
2. Se a célula não contiver uma mina, o jogo mostrará quantas minas estão ao redor dela.
3. Se você revelar uma célula com uma mina, o jogo terminará.

---

## ⚙️ Como compilar e executar

Para compilar o jogo, siga as etapas abaixo:

1. Certifique-se de ter o **gcc** instalado no seu sistema.
2. No terminal, execute o seguinte comando para compilar o código:
   ```bash
   gcc -o campo campo-minado.c

## 📝 Observações

Este projeto foi produzido e testado em um ambiente Linux. Portanto, para atualizar as telas durando o jogo utilizamos o comando system("clear").
Se você estiver em um ambiente Windows, substitua este comando por system("cls") no código-fonte para compatibilidade.
