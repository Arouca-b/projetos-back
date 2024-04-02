package Banco.src;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;

public class Transacao {
    private double valor;
    private String emissor;
    private String destinatario;
    private LocalDateTime data;

    public Transacao(){
    }

    public Transacao(double valor, String emissor, String destinatario, LocalDateTime data){
        this.valor = valor;
        this.emissor = emissor;
        this.destinatario = destinatario;
        this.data = data;
    }

    public Transacao(double valor, String destinatario, String emissor, DateTimeFormatter formato, ArrayList<Transacao> destino){
        Transacao newDestino;
        this.valor = valor * (-1);
        this.destinatario = destinatario;
        this.emissor = emissor;
        this.data = LocalDateTime.now();
        String dataString = this.data.format(formato);
        this.data = LocalDateTime.parse(dataString, formato);
        newDestino = new Transacao(valor, emissor, destinatario, this.data);
        destino.add(newDestino);
    }

    public double getValor(){
        return this.valor;
    }

    public String getDestinatario(){
        return this.destinatario;
    }

    public String getEmissor(){
        return this.emissor;
    }

    public LocalDateTime getData(){
        return this.data;
    }

    public void getTransacao(){
        System.out.println("Data: "+getData());
        System.out.println("Emissor: "+getEmissor());
        System.out.println("Destinatário: "+getDestinatario());
        System.out.println("Valor: R$"+getValor());
    }
}
