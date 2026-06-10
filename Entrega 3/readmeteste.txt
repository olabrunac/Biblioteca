Tentando criar a pasta de novo
funcionou?
Fiz outro main para testar e compilou :)


vou aproveitar esse arquivo pra botar anotações (com '//' significa que ta feito):
    //reservar 2 livros iguais / 2x o mesmo -- Adicionei essa logica no criarReserva do Gerenciador
    /empréstimo para ontem -- Estou pensando em como a classe Gerenciador vai interagir com as datas

    //data do empréstimo com enum -- A classe data tem um construtor da pra colocar ela com int 20260608 nas funções do Gerenciador
    //construtores que faltaram
    //checar se retirar a reserva funciona e checar se apaga na memória
    //arrumar a herança
    //ponteiros nos vetores de objetos
    //Destrutores
    /Reserva -- Ta indo
    //polimorfismo da reserva e emprestimo com usuario

    data de empréstimo e data de devolucao ainda tao +-
    emprestimo apartir de reserva cria um objeto emprestimo novo em vez de fazer uma lista pro usuario (pra arrumar isso é mto código nao sei se ficaria legal)
    ao criar um empréstimo ta pra alocar a data atual, mas e se quisermos usar outra data?

    //data de empréstimo e data de devolucao
    //GerenciadorDeReservas
    
    //Menu
    //Verificar Possiveis regras esquecidas

    para lidar com o menu tive q criar os gerenciadores senao o sistemabiblioteca ficaria ENORME
    mainmenu.cpp funcional, outras mains tbm mas a mainTeste1 é boa pra usar de teste dos métodos msm, reserva fica na lista de espera, coisas inuteis foram tiradas
    sobrecargas que ocorrem sao a de construtor tipo livro q tem 2 iguais, tem a de método com 2 iguais tbm (criar emprestimo 1 ou vários), e na data em a sobrecarga de operador+ e ==
    pode criar varios livros, usuarios e etc com o mesmo nome pois cada um tem um código
    quando for imprimir data usa o proprio imprimirdata para ficar DD/MM/AAAA e nao o getdatainteira que fica AAAAMMDD
    imprimir é só tela e getdata é para lógica interna
    regra nao pode deletar usuario com pendencia