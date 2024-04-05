package Banco.src;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;

public class Conta {
    private static int quantidade_contas; 
    private String nome;
    private String agencia;
    private String nConta;
    private double saldo;
    private String cpf;
    private String senha;
    private int qtdTransacao;
    private ArrayList<Transacao> transacoes = new ArrayList<>();

    public Conta(){

    }

    public Conta(String nome, String nConta, String agencia, String cpf, String senha) {
        this.nome = nome;
        this.nConta = nConta;
        this.agencia = agencia;
        this.cpf = cpf;
        this.senha = senha;
        quantidade_contas++;
    }

    public static int getQuantidade_contas(){
        return quantidade_contas;
    }

    public void setSenha(String senha){
        this.senha = senha;
    }

    public String getAgencia(){
        return agencia;
    }

    public String getCpf(){
        return cpf;
    }

    public boolean valida_Logins(String Senha){
        if (this.senha.equals(Senha)) {
            return true;
        }
        return false;
    }

    public void deposito(double deposito) {
        this.saldo += deposito;
    }

    public void sacar(double saque) {
        this.saldo -= saque;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getnConta() {
        return nConta;
    }

    public double getSaldo() {
        return saldo;
    }

    public boolean validaSaldo(double valor){
        if (this.saldo >= valor) {
            return true;
        }
        return false;
    }

    public void pix(double valor, String emissor, Conta destinatario){
        this.sacar(valor);
        destinatario.deposito(valor);
        transacao(valor, emissor, destinatario.getNome(),  destinatario.transacoes);
        destinatario.qtdTransacao++;
    }

    public void transacao(double valor, String emissor, String destinatario, ArrayList<Transacao> destino){
        DateTimeFormatter formato = DateTimeFormatter.ofPattern("dd/MM/yyyy HH:mm:ss");
        Transacao newTransacao = new Transacao(valor, destinatario, emissor, formato, destino);
        this.transacoes.add(newTransacao);
        this.qtdTransacao++;
    }

    public void getTransacoes(){
        for(int i = 0; i < qtdTransacao;i++){
            transacoes.get(i).getTransacao();
        }
    }

    public void getConta() {
        System.out.printf("\n\nAgencia: %s\n", this.agencia);
        System.out.printf("Conta: %s\n", this.nConta);
        System.out.printf("Nome: %s\n", this.nome);
        System.out.printf("Saldo: R$ %.2f\n", this.saldo);
        System.out.printf("CPF: %s\n\n", this.cpf);
        System.out.println("___________________________");
    }
}
