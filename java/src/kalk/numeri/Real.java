package kalk.numeri;

public class Real {
    private Double rVal = 0.0;

    public Real() {
        setR(0.0);
    }

    public Real(Double initVal) {
        setR(initVal);
    }

    public void setR(Double valToSet) {
        rVal = valToSet;
    }

    public Double getR() {
        return this.rVal;
    }

    public void string (String str) {
        str = str.replaceAll("\\s+","");
        setR(Double.valueOf(str));
    }

    public Real somma(Real b) {
        Real res = new Real();
        res.setR(getR() + b.getR());
        return res;
    }
    public Real sottrai (Real b) {
        Real res = new Real();
        res.setR(getR() - b.getR());
        return res;
    }
    public Real moltiplica (Real b) {
        Real res = new Real();
        res.setR(getR() * b.getR());
        return res;
    }
    public Real dividi(Real b) throws RuntimeException {
        Real res = new Real();
        if (b.getR() == 0)
            throw new RuntimeException("Errore divisione per 0");
        res.setR(getR() / b.getR());
        return res;
    }

    public String getString() {
        return String.format("%.2f", getR());
    }
}