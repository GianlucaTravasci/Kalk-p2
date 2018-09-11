package kalk.wave;

public class Color {
    private Integer r = new Integer(0);
    private Integer g = new Integer(0);
    private Integer b = new Integer(0);

    public Color() {
        setRdec(255);
        setGdec(255);
        setBdec(255);
    }
    public Color(Integer red, Integer green, Integer blue) {
        setRdec(red);
        setGdec(green);
        setBdec(blue);
    }
     public void setRdec (int red){
        if (red < 0) {
            r = 0;
        }else if (red > 255) {
            r = 255;
        }else {
            r=red;
        }
     }
    public void setGdec (int green){
        if (green < 0) {
            g = 0;
        }else if (green > 255) {
            g = 255;
        }else {
            g=green;
        }
    }
    public void setBdec (int blue){
        if (blue < 0) {
            b = 0;
        }else if (blue > 255) {
            b = 255;
        }else {
            b=blue;
        }
    }
    public Integer getRdec() {
        return r;
    }

    public Integer getGdec() {
        return g;
    }

    public Integer getBdec() {
        return b;
    }

    public static String decimal2hex(Integer d) {
        String digits = "0123456789ABCDEF";
        if (d <= 0) return "00";
        int base = 16;
        StringBuilder ret = new StringBuilder();
        while (d > 0) {
            int digit = d % base;
            ret.insert(0, digits.charAt(digit));
            d = d / base;
        }
        while (ret.toString().length() < 2) {
            ret.insert(0, "0");
        }
        return ret.toString();
    }

    public String convertRGBtoHex(){
        String ret = "#";
        ret = ret.concat(decimal2hex(getRdec()))
                .concat(decimal2hex(getGdec()))
                .concat(decimal2hex(getBdec()));
        return ret;
    }

    public Color somma (Color x, Color y) {
        return new Color(x.getRdec()+y.getRdec(),
                x.getGdec()+y.getGdec(),
                x.getBdec()+y.getBdec());
    }

    public Color sottrazione (Color x, Color y) {
        return new Color(x.getRdec()-y.getRdec(),
                x.getGdec()-y.getGdec(),
                x.getBdec()-y.getBdec());
    }

    public Color moltiplicazione (Color x, Color y) {
        return new Color(x.getRdec()*y.getRdec(),
                x.getGdec()*y.getGdec(),
                x.getBdec()*y.getBdec());
    }

    public Color divisione (Color x, Color y) throws RuntimeException{
        if(x.getRdec()==0 || x.getGdec()==0 || x.getBdec()==0 || y.getRdec()==0 || y.getGdec()==0 || y.getBdec()==0){
            throw new RuntimeException("Errore divisione per 0");
        } else {
            return new Color(x.getRdec() + y.getRdec(),
                    x.getGdec() + y.getGdec(),
                    x.getBdec() + y.getBdec());
        }
    }
}
