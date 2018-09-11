package kalk.wave;

import java.util.ArrayList;

import static java.lang.Integer.max;

public class ColoredWave extends Wave {

    private ArrayList<Color> colori = new ArrayList<Color>();

    public ColoredWave() {}

    public Color getColore(Integer index) {
        Color ret  = new Color();
        if (index < colori.size()) {
            ret = colori.get(index);
        } return ret;
    }

    public void setColor(Color color, Integer index, boolean insert){
        Color aux = color;
        if (index < 0) {
            colori.add(aux);
        }else if (index < waveLenght()) {
            if (insert) {
                colori.add(index, aux);
            } else {
                colori.set(index, aux);
            }
        }
    }

    public void pushPoint(Double x, Color color, Integer index, boolean insert){
        setVAmp(x, index, insert);
        setColor(color, index, insert);
    }

    public void pushPoint (Double x, Color color, Integer index){
        pushPoint(x, color, index, false);
    }

    public void pushPoint (Double x, Color color){
        pushPoint(x, color, -1, false);
    }

    public void removePoint(Integer  index) {
        if (index < colori.size()) {
            colori.remove(index.intValue());
            v.remove(index.intValue());
        }
    }

    public Integer waveLenght() {
        return colori.size();
    }

    public Double getAmpVal(Integer index) {
        return getVAmp(index);
    }

    public Color getAmpColor(Integer index) {
        return getColore(index);
    }

    public ColoredWave somma(ColoredWave x) {
        ColoredWave aux = new ColoredWave();
        Integer maxLenght = max(waveLenght(), x.waveLenght());
        Color res = new Color();
        for(int i=0; i<maxLenght; ++i) {
            res.somma(getColore(i), x.getColore(i));
            aux.pushPoint(getAmpVal(i) + x.getAmpVal(i), res);
        }
        return aux;
    }

    public ColoredWave sottrazione(ColoredWave x) {
        ColoredWave aux = new ColoredWave();
        Integer maxLenght = max(waveLenght(), x.waveLenght());
        Color res = new Color();
        for(int i=0; i<maxLenght; ++i) {
            res.sottrazione(getColore(i), x.getColore(i));
            aux.pushPoint(getAmpVal(i) - x.getAmpVal(i), res);
        }
        return aux;
    }

    public ColoredWave moltiplicazione(ColoredWave x) {
        ColoredWave aux = new ColoredWave();
        Integer maxLenght = max(waveLenght(), x.waveLenght());
        Color res = new Color();;
        for(int i=0; i<maxLenght; ++i) {
            res.moltiplicazione(getColore(i), x.getColore(i));
            aux.pushPoint(getAmpVal(i) * x.getAmpVal(i), res);
        }
        return aux;
    }

    public ColoredWave divisione(ColoredWave x) {
        ColoredWave aux = new ColoredWave();
        Integer maxLenght = max(waveLenght(), x.waveLenght());
        Color res = new Color();
        for(int i=0; i<maxLenght; ++i) {
            res.divisione(getColore(i), x.getColore(i));
            aux.pushPoint(getAmpVal(i) / x.getAmpVal(i), res);
        }
        return aux;
    }
}
