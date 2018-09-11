package kalk.wave;


import java.util.ArrayList;

import static java.lang.Integer.max;

public class Wave {
    protected ArrayList<Double> v = new ArrayList<Double>();

    protected void  setVAmp(Double x, Integer index, Boolean insert){
        if (index < 0) {
            v.add(x);
        } else if (index<waveLenght()){
            if (insert){
                v.add(index, x);
            } else {
                v.set(index, x);
            }
        }
    }
    protected Double getVAmp(Integer index) {
        if(index < v.size()){
            return v.get(index);
        } return 0.0;
    }
    protected void removeVAmp (Integer index) {
        if (index < v.size()) {
            v.remove(index.intValue());
        }
    }
    public Wave(){}

    public void pushPoint (Double x, Integer index, boolean insert){
        setVAmp(x, index, insert);
    }
    public void pushPoint (Double x, Integer index){ pushPoint(x, index, false);}
    public void pushPoint (Double x){ pushPoint(x, -1, false);}
    public void removePoint(Integer index) {
        removeVAmp(index);
    }
    public Integer waveLenght() {
        return v.size();
    }
    public Double getAmpVal(Integer x) {
        return getVAmp(x);
    }

    public Wave somma (Wave x) {
        Wave aux = new Wave();
        Integer maxLenght = max(waveLenght(), x.waveLenght());
        for(Integer i=0 ; i<maxLenght; ++i ){
            aux.pushPoint(getAmpVal(i) + x.getAmpVal(i));
        }
        return aux;
    }
    public Wave sottrazione (Wave x) {
        Wave aux = new Wave();
        Integer maxLenght = max(waveLenght(), x.waveLenght());
        for(Integer i=0 ; i<maxLenght; ++i ){
            aux.pushPoint(getAmpVal(i) - x.getAmpVal(i));
        }
        return aux;
    }
    public Wave moltiplicazione (Wave x) {
        Wave aux = new Wave();
        Integer maxLenght = max(waveLenght(), x.waveLenght());
        for(Integer i=0 ; i<maxLenght; ++i ){
            aux.pushPoint(getAmpVal(i) * x.getAmpVal(i));
        }
        return aux;
    }
    public Wave divisione (Wave x) throws RuntimeException{
        Wave aux = new Wave();
        Integer maxLenght = max(waveLenght(), x.waveLenght());
        for(Integer i=0 ; i<maxLenght; ++i ){
            if (x.getAmpVal(i) == 0) {
                throw new RuntimeException("Errore divisione per 0");
            }else {
                aux.pushPoint(getAmpVal(i) / x.getAmpVal(i));
            }
        }
        return aux;
    }
}
