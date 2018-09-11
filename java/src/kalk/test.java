package kalk;
import kalk.numeri.*;
import kalk.wave.Audio;
import kalk.wave.Color;
import kalk.wave.Wave;

import javax.sound.midi.SysexMessage;

public class test {
    public static void main(String[] args) {
        testNumeri();
        testOnde();
    }

    public static void testOnde() {
        // Lavora qui
        System.out.println("----wave-----");
        Wave o1 = new Wave();
        Wave o2 = new Wave();
        o1.pushPoint(3.0);
        o1.pushPoint(2.0);
        o1.pushPoint(-7.0);
        o1.removePoint(1);
        System.out.println(o1.waveLenght());
        System.out.println(o1.getAmpVal(1));
        o2.pushPoint(2.5);
        o2.pushPoint(1.5);
        System.out.println(o1.somma(o2));

        System.out.println("----Audio-----");
        Audio a1 = new Audio();
        Audio a2 = new Audio();
        a1.pushPoint(2.3, 2.5);
        a1.pushPoint(3.0, 2.4);
        System.out.println(a1.waveLenght());
        System.out.println(a1.getAmpVal(1));
        a2.pushPoint(2.0, 1.1);
        a2.pushPoint(2.0, 1.1);
        a2.pushPoint(2.0, 1.1);
        System.out.println(a2.moltiplicazione(a1));

        System.out.println("----Colori-----");
        Color c1 = new Color();
        c1.setRdec(200);
        c1.setGdec(125);
        c1.setBdec(25);
        System.out.println(c1.convertRGBtoHex());
        Color c2 = new Color();
        c2.setRdec(20);
        c2.setGdec(15);
        c2.setBdec(25);
        Color c3 = new Color();
        System.out.println(c3.somma(c1, c2));
        System.out.println(c3.sottrazione(c1, c2));
        System.out.println(c3.moltiplicazione(c1, c2));
        System.out.println(c3.divisione(c1, c2));

    }

    public static void testNumeri() {
        // Complessi esempi di utilizzo
        System.out.println("--------- Test numeri complessi ---------");
        Complex c1 = new Complex(3.0, 6.0);
        Complex c2 = new Complex(5.0, 3.0);
        Complex c3 = new Complex();
        System.out.println("Complesso A: " + c1.getString());
        System.out.println("Complesso B: " + c2.getString());
        System.out.println("Cambio il complesso B");
        c2.string(("6.3,-2.3i"));
        System.out.println("Complesso B: " + c2.getString());
        c3 = c2.somma(c1);
        System.out.println("Somma: " + c3.getString());
        c3 = c2.sottrai(c1);
        System.out.println("Sottrazione: " + c3.getString());
        c3 = c2.moltiplica(c1);
        System.out.println("Moltiplicazione: " + c3.getString());
        c3 = c2.dividi(c1);
        System.out.println("Divisione: " + c3.getString());
        c3 = c2.conjugate();
        System.out.println("Coniugato: " + c3.getString());
        System.out.println("Norma: " + String.valueOf(c2.norm()));
        c3 = c2.inverse();
        System.out.println("Inverso: " + c3.getString());

        // Quaternioni esempi di utilizzo
        System.out.println("--------- Test numeri quaternioni ---------");
        Quaternion n1 = new Quaternion(3.0, 6.0, 5.0, 3.0);
        Quaternion n2 = new Quaternion(5.0, 3.0, 6.0, 6.7);
        Quaternion n3 = new Quaternion();
        System.out.println("Quaternione A: " + n1.getString());
        System.out.println("Quaternione B: " + n2.getString());
        System.out.println("Cambio il quaternione B");
        n2.string(("6.3,-2.3i,4.6j,-3k"));
        System.out.println("Complesso B: " + n2.getString());
        n3 = n2.somma(n1);
        System.out.println("Somma: " + n3.getString());
        n3 = n2.sottrai(n1);
        System.out.println("Sottrazione: " + n3.getString());
        n3 = n2.moltiplica(n1);
        System.out.println("Moltiplicazione: " + n3.getString());
        n3 = n2.dividi(n1);
        System.out.println("Divisione: " + n3.getString());
        n3 = n2.conjugate();
        System.out.println("Coniugato: " + n3.getString());
        System.out.println("Norma:" + String.valueOf(n2.norm()));
        n3 = n2.inverse();
        System.out.println("Inverso: " + n3.getString());
    }
}
