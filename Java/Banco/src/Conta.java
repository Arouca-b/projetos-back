package LP3.aula02.src;

public class Conta {
    private String nome;
    private String agencia;
    private String nConta;
    private double saldo;
    private String cpf;
    private String senha;

    public Conta(String nome, String nConta, String agencia, String cpf, String senha) {
        this.nome = nome;
        this.nConta = nConta;
        this.agencia = agencia;
        this.cpf = cpf;
        this.senha = senha;
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

    public void pix(double valor, Conta recebedor){
        this.sacar(saldo);
        recebedor.deposito(valor);
    }

    public void getConta() {
        System.out.printf("\n\nAgencia: %s\n", this.agencia);
        System.out.printf("Conta: %s\n", this.nConta);
        System.out.printf("Nome: %s\n", this.nome);
        System.out.printf("Saldo: %.2f\n", this.saldo);
        System.out.printf("CPF: %s\n\n", this.cpf);
        System.out.println("___________________________");
    }
}
