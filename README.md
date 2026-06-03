# ClientPatch UIControl

DLL de patch para o cliente **With Your Destiny**, focada em controle de interface, hooks, regras de negócio e ajustes de comportamento do cliente.

O projeto gera `ClientPatch.dll` e foi reorganizado para facilitar manutenção de hooks, endereços fixos, regras de item, entrada, servidor, NPC, rede e UI.

## Recursos

- Controle de textos, labels, painéis, botões, listas e progress bars.
- Controle de eventos de mouse e teclado.
- Hooks para fluxo de cenas, inventário, itens, NPCs, pacotes e comandos.
- Regras de negócio separadas por domínio.
- Endereços e constantes do cliente centralizados em um header.
- Sistema de log com buffer, gravando no arquivo por intervalo ou no encerramento da DLL.
- Guardas contra ponteiros nulos em pontos sensíveis para reduzir crashes.

## Estrutura

```text
include/                  Headers compartilhados
src/App/                  Entrada da DLL e bootstrap
src/Core/                 Funções utilitárias, log e dados globais
src/Hooking/              Instalação de hooks e patches
src/Network/              Interceptação de pacotes enviados/recebidos
src/Scenes/               Fluxo de cenas e main loop
src/Business/Chat/        Comandos e chat
src/Business/Input/       Teclado, botões e message boxes
src/Business/Items/       Inventário, uso, tooltip e amount de itens
src/Business/Npc/         NPCs, mobs e score
src/Business/Server/      Lista e endereços de servidores
src/UI/                   Comportamento específico de componentes de UI
docs/                     Documentação auxiliar
PatchInfo/                Arquivos de referência do cliente
```

Veja também [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md).

## Arquivos importantes

- `include/ClientAddresses.h`: endereços de memória, funções, hooks e aliases usados em assembly.
- `include/BusinessRules.h`: constantes e helpers de regras de negócio.
- `include/LogManager.h` e `src/Core/LogManager.cpp`: log com buffer e flush periódico.
- `src/Hooking/HookPatch.cpp`: instalação dos hooks principais.
- `src/App/dllmain.cpp`: inicialização da DLL, permissões de memória e flush final do log.
- `UIControl.vcxproj`: projeto Visual Studio.

## Build

Requisitos:

- Windows.
- Visual Studio com toolset C++ `v142`.
- MSBuild.
- Plataforma `x86`/`Win32`.

Build recomendado:

```powershell
& 'C:\Program Files\Microsoft Visual Studio\18\Community\MSBuild\Current\Bin\MSBuild.exe' ClientPatch.sln /p:Configuration=Release /p:Platform=x86 /m /v:minimal
```

Saída esperada:

```text
Release\ClientPatch.dll
```

Observação: o projeto pode emitir o warning `MSB8004` sobre o diretório Output não terminar com barra. Esse warning não impede a geração da DLL.

## Atualização de endereços

Endereços de funções, hooks e memória devem ficar em `include/ClientAddresses.h`.

Use:

- `ClientAddresses::Memory::*` para ponteiros e regiões de memória do cliente.
- `ClientAddresses::Function::*` para chamadas diretas para funções do cliente.
- `ClientAddresses::Hook::*` para pontos de instalação de hooks e destinos.
- `CLIENT_ADDR_*`, `CLIENT_FN_*` ou `CLIENT_RAW_*` quando o valor precisar ser usado em inline assembly do MSVC.

Evite espalhar literais como `0x004...`, `0x005...`, `0x006...` e endereços similares pelos arquivos de regra ou UI. Isso deixa atualizações de versão muito mais difíceis.

## Logs

O log usa `LogManager` e grava em `./UIControl.log` por padrão.

Comportamento:

- As mensagens entram em buffer.
- O arquivo é gravado por intervalo configurado.
- O buffer também é descarregado quando a DLL recebe `DLL_PROCESS_DETACH`.
- O intervalo padrão é `5000 ms`.
- O buffer força flush ao atingir `128` linhas.

APIs úteis:

```cpp
LogManager::Write("mensagem");
LogManager::WriteFormat("valor: %d", value);
LogManager::Flush();
LogManager::SetFlushInterval(5000);
LogManager::SetFilePath("./UIControl.log");
```

## Padrões de manutenção

- Hooks devem capturar o contexto do cliente e encaminhar para funções de domínio.
- Regras de negócio devem ficar em `src/Business/*` ou em helpers de `include/BusinessRules.h`.
- Código de infraestrutura deve ficar em `src/Core`.
- Comportamento de UI deve ficar em `src/UI` ou nos headers de componentes.
- Antes de acessar ponteiros vindos do cliente, valide nulos quando houver chance de crash.
- Evite adicionar regra de negócio diretamente em assembly quando for possível delegar para C++.
- Ao adicionar novos arquivos, atualize `UIControl.vcxproj` e `UIControl.vcxproj.filters`.

## Checklist para alterações

1. Mover novos endereços para `include/ClientAddresses.h`.
2. Separar regra de negócio na pasta correta em `src/Business`.
3. Adicionar guardas para ponteiros vindos do cliente.
4. Manter logs via `LogManager`.
5. Compilar em `Release|x86`.
6. Conferir se `Release\ClientPatch.dll` foi gerado.

## Créditos

Copyright (C) `{2019.1}` `{Djunio - SeiTbNao - Wed}`

Este projeto segue os termos da GNU General Public License conforme indicado nos comentários dos arquivos-fonte.
