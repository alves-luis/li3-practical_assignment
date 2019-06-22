# LI3 - Practical Assignment
This repo contains code made for the practical assignment of the Computer Labs III course in the University of Minho.

Team members:
* [Luís Alves](https://github.com/alves-luis)
* [Miguel Carvalho](https://github.com/MAACarvalho)
* [José Costa](https://github.com/DeusTaNoComando)
* [João Queirós](https://github.com/JoaoQueiros)

Final grade: 18

## proj-c

Repositório com ficheiros comuns a todos os projetos.

Estrutura do repositório:

- pasta `include`: contém todos os ficheiros `.h`
- pasta `src`: contém o código realizado pelo grupo (ficheiros `.c`)
- pasta `src/lib`: contém as definições dos tipos que constam na definição da interface do programa
- pastas `src/obj` e `src/obj/lib`: conterão os ficheiros `.o` quando o programa for compilado

Nota da Fase 1: 16

## proj-java

### Estruturação do Repositório
Este projeto está dividido em 3 packages: `common`, `engine` e `li3`.
- `common`: classes utilitárias e comparadores;
- `engine`: classes que implementam as queries e onde os dados são armazenados;
- `li3`: definição das interfaces implementadas por cada query e o Main;


### Compilação do Projeto
Em primeiro lugar, deve-se instalar a ferramenta **Maven**, responsável pela gestão do projeto. 
Esta ferramenta é normalmente disponibilizada nos gestores de pacotes com o nome `mvn`.
Para compilar o projeto e corrê-lo com a *class* **Main** fornecida, deve-se executar o comando

```bash
./run.sh [DUMP_PATH]
```

Nota da Fase 2: 20

