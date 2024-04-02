package Banco.src;
import java.util.Scanner;
import java.io.IOException;
import java.util.ArrayList;

//Autor Breno Arouca
//Última atualiazação: 02/03/2024



public class Banco {
    private static Scanner inputText = new Scanner(System.in);
    private static Scanner inputValue = new Scanner(System.in);
    
    public static void main(String[] args) {
        ArrayList<Conta> listaClientes = new ArrayList<>();
        Conta newConta = null;

        String nome, cpf, conta, agencia = "092", senha;
        int op = 0, pos_cliente = 0;

        do {
            menu();
            op = inputValue.nextInt();
            switch (op) {
                case 1:
                    System.out.print("Nome: ");
                    nome = inputText.nextLine();

                    System.out.print("CPF: ");
                    cpf = inputText.nextLine();
                    
                    conta = "" + (listaClientes.size() + 1);
                    senha = definirSenha();

                    //Cria a conta do cliente e adiciona na lista geral de clientes, sempre inserido no ultimo elemento
                    newConta = new Conta(nome, conta, agencia, cpf, senha);
                    listaClientes.add(newConta); 
                    
                    clear();
                    listaClientes.get(listaClientes.size() - 1).getConta();
                    pause();
                    mensagem();
                    break;
            
                case 2:
                    if (!listaClientes.isEmpty()) {
                        System.out.print("Insira cpf: ");
                        cpf = inputText.nextLine();
                        System.out.print("Insira senha: ");
                        senha = inputText.nextLine();
                        pos_cliente = login(listaClientes, cpf, senha);
                        if (pos_cliente<0) {
                            System.out.println("\n\nSenha incorreta ou Conta não existe!!\n");
                            pause();
                        }else{
                            acesso_cliente(listaClientes.get(pos_cliente), listaClientes);
                        }
                    }else{
                        System.out.println("\n\nNao ha clientes registrados no banco de dados!!");
                    }
                    break;

                case 0:
                    System.out.println("\n\nVOLTE SEMPRE\n\n");
                    break;
            }
        } while (op != 0);
        inputValue.close();
        inputText.close();
    }

    //Menu para tela inicial
    public static void menu() {
        clear();
        System.out.println("\n\n\t\t\t\tMENU INICIAL\n\n");
        System.out.println("1 - Criar Conta;");
        System.out.println("2 - Realizar Login;");
        System.out.println("3 - Contato;");
        System.out.println("\n0 - Sair;\n");
    }

    //Menu para os clientes que tem conta no sistema, liberado apos logarem no sistema
    public static void menu_cliente() {
        clear();
        System.out.println("\n\n\t\t\t\t TELA CLIENTE\n\n");
        System.out.println("1 - Depositar;");
        System.out.println("2 - Sacar;");
        System.out.println("3 - Pix;");
        System.out.println("4 - Alterar Nome;");
        System.out.println("5 - Dados da Conta;");
        System.out.println("6 - Alterar Senha;");
        System.out.println("7 - Histórico pix;");        

        System.out.println("\n0 - Sair;\n");
    }

    //Procurar cliente através da agencia e numero da conta, retorna posicao ou -1 se nao encontrar
    public static int identificarCliente(ArrayList<Conta> lista, String n_conta, String agencia) {
        int i = 0;
        for (Conta cliente : lista){
            if (cliente.getAgencia().equals(agencia)) {
                if (cliente.getnConta().equals(n_conta)) {
                    return i;
                }
            }
            i++;
        }
        return -1;
    }
    
    //Realizar login, retorna posicao do cliente ou -1 se nao existir
    public static int login(ArrayList<Conta> lista, String cpf, String senha){
        int i = 0;
        for (Conta conta : lista) {
            if (conta.getCpf().equals(cpf)) {
                if (conta.valida_Logins(senha)) {
                    return i;
                }
                return -1;
            }
            i++;
        }
        return -1;
    }

    //Realizar deposito sem precisar logar no sistema, depositar em qualquer conta do banco
    public static void depositoLoterica(ArrayList<Conta> contas){
        String conta, agencia;
        float dinheiro;
        int posicao;
        
        System.out.print("Agência: ");
        agencia = inputText.nextLine();

        System.out.print("Número da Conta: ");
        conta = inputText.nextLine();

        posicao = identificarCliente(contas, conta, agencia);
        if (posicao > -1) {
            contas.get(posicao).getConta();

            System.out.print("Valor para Depósito: R$ ");
            dinheiro = inputValue.nextFloat();
            inputValue.nextLine();

            contas.get(posicao).deposito(dinheiro);
            mensagem();
        }else {
            System.out.println("\nCliente não registrado no banco de dados!!\n");
        }
    }

    //Sistema do usuario, liberado apos login
    public static void acesso_cliente(Conta cliente, ArrayList<Conta> listaClientes){
        int op2 = 0;
        String nome = null;
        do{
            clear();
            menu_cliente();
            op2 = inputValue.nextInt();
            switch (op2) {
                case 1:
                    realizarDeposito(cliente);
                    break;

                case 2:
                    realizarSaque(cliente);
                    break;

                case 3:
                    realizarPix(listaClientes, cliente);
                    break;

                case 4:
                    System.out.printf("Nome: %s\n", cliente.getNome());
                    System.out.print("Nome: ");
                    nome = inputText.nextLine();
                    cliente.setNome(nome);
                    mensagem();
                    break;

                case 5:
                    cliente.getConta();
                    System.out.println("\t\t\tPressione ENTER para continuar\n");
                    inputText.nextLine();
                    break;

                case 6:

                    //Alterar senha
                    break;

                case 7:
                    clear();
                    cliente.getTransacoes();
                    System.out.println("\t\t\tPressione ENTER para continuar\n");
                    inputText.nextLine();
                    break;
            }
        }while(op2!=0);
    }

    //Depositar com login, deposita na conta logada
    public static void realizarDeposito(Conta cliente){
        float dinheiro;
        cliente.getConta();

        System.out.print("Valor para Depósito: R$ ");
        dinheiro = inputValue.nextFloat();
        inputValue.nextLine();
        cliente.deposito(dinheiro);
        mensagem();
    }

    //mensagem apos executar uma acao do sistema
    public static void mensagem(){
        clear();
        System.out.println("\n\n\t\t\tOperacao realizada com sucesso!\n");
        pause();
    }

    public static void alterarSenha(Conta cliente){
        String senha = null;
        boolean denovo = true;
        while(denovo){
            System.out.print("Senha atual: ");
            senha = inputText.nextLine();
            if (cliente.valida_Logins(senha)){
                denovo = false;
                System.out.print("Nova senha: ");
                senha = inputText.nextLine();
                System.out.print("Confirmar Senha: ");
                if (!senha.equals(inputText.nextLine())) {
                    denovo=true;
                }
            }
            if(denovo){
                System.out.println("\n\n\t\tSENHA INCORRETA");
                System.out.println("\n\t\tTente novamente");
                pause();
            }
        }
    }

    //Criacao de senha, retorna a propria senha se for digitada corretamente
    public static String definirSenha(){
        String senha = null;
        boolean corrigir_senha = true;
        while (corrigir_senha) {
            System.out.print("Defina uma senha: ");
            senha=inputText.nextLine();
            System.out.print("Confirme a senha: ");
            if (senha.equals(inputText.nextLine())) {
                corrigir_senha = false;
            }else{
                System.out.println("\n\n\t\tSenha incorreta, tente novamente!\n\n");
            }
        }
        return senha;
    }

    //Sacar dinheiro
    public static void realizarSaque(Conta cliente) {
        float dinheiro;
        cliente.getConta();

        System.out.print("Valor para saque: R$ ");
        dinheiro = inputValue.nextFloat();
        inputValue.nextLine();

        if (!cliente.validaSaldo(dinheiro)) {
            clear();
            System.out.println("\t\tVc não tem Saldo para realizar saque desse valor!\n\nPor favor, Tente novamente!!\n");
            pause();
        }else if (dinheiro < 0) {  
            System.out.println("\n\n\t\tValor inválido!\n\n");
            pause();
        }else{
            cliente.sacar(dinheiro);
            System.out.println(("\n\t\tSaque realizado com sucesso!!"));
            pause();
        }
    }

    //Transferencia PIX, so aceita cpf como chave pix
    public static void realizarPix(ArrayList<Conta> listaClientes, Conta cliente){
        String chavePix;
        double valor = 0;
        boolean feito = false;
        System.out.print("Insira chave pix(cpf): ");
        chavePix = inputText.nextLine();

        for(int i = 0; i < listaClientes.size() && (!feito);i++){
            if (listaClientes.get(i).getCpf().equals(chavePix) && chavePix!=cliente.getCpf()) {
                System.out.print("Valor: R$ ");
                valor = inputValue.nextDouble();
                if (cliente.validaSaldo(valor)) {
                    cliente.pix(valor, cliente.getNome(), listaClientes.get(i));
                    mensagem();
                    
                }else{
                    System.out.println("\n\nSALDO INDISPONÍVEL!\n\n");
                }
            }
        }
    }

    public static void clearSystem() throws IOException, InterruptedException {
        if (System.getProperty("os.name").contains("Windows")) {
            new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
        } else {
            new ProcessBuilder("clear").inheritIO().start().waitFor();
        }
    }

    public static void clear(){
        try {
            clearSystem();
        } catch (IOException | InterruptedException e) {
            System.out.println("Erro ao limpar a tela: " + e.getMessage());
        }
    }

    public static void pause(){
        try {
            // Pausa a execução por 3 segundos (3000 milissegundos)
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            // Trata a exceção, se ocorrer
            e.printStackTrace();
        }
    }
}
