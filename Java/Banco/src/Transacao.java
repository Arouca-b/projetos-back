package Banco.src;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

public class Transacao {
    private double valor;
    private String Recebedor;
    private LocalDateTime data;

    public Transacao(){
    }

    public Transacao(double valor, String recebedor, DateTimeFormatter formato){
        this.valor = valor;
        this.Recebedor = recebedor;
        this.data = LocalDateTime.now();
        String dataString = this.data.format(formato);
        this.data = LocalDateTime.parse(dataString, formato);
    }

    public double getValor(){
        return this.valor;
    }

    public String getRecebedor(){
        return this.Recebedor;
    }

    public LocalDateTime getData(){
        return this.data;
    }

    public void getTransacao(){
        System.out.println("Data: "+getData());
        System.out.println("Recebedor: "+getRecebedor());
        System.out.println("Valor: R$"+getValor());
    }
}
