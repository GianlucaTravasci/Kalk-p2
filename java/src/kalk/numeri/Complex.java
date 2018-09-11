package kalk.numeri;
import java.util.regex.Pattern;

public class Complex extends Real {
    final Pattern regExp = Pattern.compile("^(\\+|-)?([0-9]+(\\.[0-9])?[0-9]*),(\\+|-)?([0-9]+(\\.[0-9])?[0-9]*)i$");
	private Double iVal = 0.0;

	public Complex() {
		setR(0.0);
	}

	public Complex(Double rVal, Double iVal) {
		setR(rVal);
		setI(iVal);
	}

	public void setI(Double valToSet) {
		iVal = valToSet;
	}

	public double getI() {
		return iVal;
	}

	public void inverseI() {
		setI(getI() * -1);
	}

	public Complex conjugate() {
		Complex res;
		res = this;
		res.inverseI();
		return res;
	}

	public double norm() throws RuntimeException {
		double ret;
		if ((Math.pow(getR(), 2.0) + Math.pow(getI(), 2.0)) == 0) {
			throw new RuntimeException("Divisione per 0" );
		}else{
			ret = Math.pow(Math.pow(getR(),2.0) + Math.pow(getI(), 2.0),1/2);
			return ret;
		}
	}

	public Complex inverse() {
		Complex norma = new Complex();
		norma.setR(Math.pow(norm(), 2.0));
		Complex ret = this;
		ret = ret.dividi(norma);
		return ret;
	}

	public void string (String str) {
        str = str.replaceAll("\\s+", "");

        if (regExp.matcher(str).matches()) {
            String[] splitted = str.split(",");
            setR(Double.valueOf(splitted[0]));
            splitted[1] = splitted[1].replace("i", "");
            setI(Double.valueOf(splitted[1]));
            return;
        }
        throw new RuntimeException("Errore nella lettura del complesso " + str);
    }

	public Complex somma(Complex b) {
		Complex res = new Complex();
		res.setR(getR() + b.getR());
		res.setI(getI() + b.getI());
		return res;
	}
	public Complex sottrai (Complex b) {
		Complex res = new Complex();
		res.setR(getR() - b.getR());
		res.setI(getI() - b.getI());
		return res;
	}
	public Complex moltiplica (Complex b) {
		Complex res = new Complex();
		res.setR((getR() * b.getR()) -
				(getI() * b.getI()));
		res.setI((getR() * b.getI()) -
				(getI() * b.getR()));
		return res;
	}
	public Complex dividi(Complex b) throws RuntimeException {
		Complex denominatoreComplex;
		Complex inverse;
		inverse = b;
		inverse.inverseI();
		denominatoreComplex = inverse.moltiplica(b);
		double denominatore = denominatoreComplex.getR();
		double rPart, iPart;
		if (denominatore == 0)
			throw new RuntimeException("Errore divisione per 0");
		inverse = moltiplica(inverse);
		rPart = inverse.getR() / denominatore;
		iPart = inverse.getI() / denominatore;
		Complex res = new Complex(rPart, iPart);
		return res;
	}

	public String getString() {
		return String.format("%.2f", getR()) + " " + String.format("%+.2f", getI()) + "i";
	}
}