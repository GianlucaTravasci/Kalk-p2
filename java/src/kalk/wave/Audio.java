package kalk.wave;

import java.util.ArrayList;
import static java.lang.Integer.max;


public class Audio extends Wave{
    private ArrayList<Double> w = new ArrayList<Double>();

    protected Double getWAmp(Integer index) {
        if(index < w.size()) {
            return w.get(index);
        } return 0.0;
    }

    protected void  setWAmp(Double x, Integer index, Boolean insert){
        if (index < 0) {
            w.add(x);
        } else if (index<waveLenght()){
            if (insert){
                w.add(index, x);
            } else {
                w.set(index, x);
            }
        }
    }

    protected void removeWAmp (Integer index) {
        if (index < w.size()) {
            w.remove(index.intValue());
        }
    }

    public enum ondeDisponibili {
        ondaSx,
        ondaDx
    }

    public Audio(){}

    public void pushPoint (Double x, Double y, Integer index, boolean insert){
        setVAmp(x, index, insert);
        setWAmp(y, index, insert);
    }

    public void pushPoint (Double x, Double y, Integer index){
        pushPoint(x, y, index, false);
    }

    public void pushPoint (Double x, Double y){
        pushPoint(x, y, -1, false);
    }

    public void removePoint(Integer index) {
        removeVAmp(index);
        removeWAmp(index);
    }

    public Integer waveLenght() {
        return w.size();
    }

    public Double getAmpVal(Integer x, ondeDisponibili ondaRichiesta) {
        if (ondaRichiesta == ondeDisponibili.ondaSx)
            return getVAmp(x);
        else
            return getWAmp(x);
    }

    public Audio somma (Audio x) {
        Audio aux = new Audio();
        Integer maxLenght = max(waveLenght(), x.waveLenght());
        for(Integer i=0 ; i<maxLenght; ++i ){
            aux.pushPoint(getAmpVal(i) + x.getAmpVal(i),
                            getAmpVal(i, ondeDisponibili.ondaDx)+getAmpVal(i, ondeDisponibili.ondaDx));
        }
        return aux;
    }
    public Audio sottrazione (Audio x) {
        Audio aux = new Audio();
        Integer maxLenght = max(waveLenght(), x.waveLenght());
        for(Integer i=0 ; i<maxLenght; ++i ){
            aux.pushPoint(getAmpVal(i) - x.getAmpVal(i),
                    getAmpVal(i, ondeDisponibili.ondaDx)- getAmpVal(i, ondeDisponibili.ondaDx));
        }
        return aux;
    }
    public Audio moltiplicazione (Audio x) {
        Audio aux = new Audio();
        Integer maxLenght = max(waveLenght(), x.waveLenght());
        for(Integer i=0 ; i<maxLenght; ++i ){
            aux.pushPoint(getAmpVal(i) * x.getAmpVal(i),
                    getAmpVal(i, ondeDisponibili.ondaDx)* getAmpVal(i, ondeDisponibili.ondaDx));
        }
        return aux;
    }
    public Audio divisione (Audio x) throws RuntimeException{
        Audio aux = new Audio();
        Integer maxLenght = max(waveLenght(), x.waveLenght());
        for(Integer i=0 ; i<maxLenght; ++i ){
            if (x.getAmpVal(i) == 0) {
                throw new RuntimeException("Errore divisione per 0");
            }else {
                aux.pushPoint(getAmpVal(i) - x.getAmpVal(i),
                        getAmpVal(i, ondeDisponibili.ondaDx)- getAmpVal(i, ondeDisponibili.ondaDx));            }
        }
        return aux;
    }
}


