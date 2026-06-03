# Arquitetura do Projeto

Este projeto e uma DLL de patch para o cliente WYD. A organizacao fisica separa pontos de entrada, hooks, infraestrutura e regras de negocio para reduzir acoplamento e facilitar manutencao.

## Pastas

- `include/`: headers compartilhados pelo projeto.
- `src/App/`: entrada da DLL e arquivos de bootstrap.
- `src/Core/`: funcoes utilitarias, dados globais e acesso a estruturas do cliente.
- `src/Hooking/`: instalacao de hooks e trampolines para enderecos do cliente.
- `src/Network/`: interceptacao e roteamento de pacotes enviados/recebidos.
- `src/Scenes/`: ciclo de carregamento, inicializacao e loop de cenas.
- `src/Business/Chat/`: regras de comandos e chatbox.
- `src/Business/Input/`: regras de teclado, botoes e message boxes.
- `src/Business/Items/`: regras de inventario, movimentacao, uso, amount e tooltip de itens.
- `src/Business/Npc/`: regras de NPC, mobs e score.
- `src/Business/Server/`: regras de lista e endereco de servidores.
- `src/UI/`: callbacks e comportamento especifico de componentes de interface.

## Regras

- Hooks devem apenas capturar o contexto do cliente e chamar uma funcao de dominio.
- Regras de negocio devem ficar em `src/Business/*` ou em helpers de `include/BusinessRules.h`.
- Enderecos fixos do cliente devem permanecer concentrados em wrappers, hooks ou classes de acesso ao cliente.
- Novos headers devem entrar em `include/` e o projeto deve continuar compilando em `Release|x86`.
