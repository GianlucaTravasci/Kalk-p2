package kalk.numeri;

import java.util.regex.Pattern;

public class Quaternion extends Complex {
    final Pattern regExp = Pattern.compile("^(\\+|-)?([0-9]+(\\.[0-9])?[0-9]*),(\\+|-)?([0-9]+(\\.[0-9])?[0-9]*)i,(\\+|-)?([0-9]+(\\.[0-9])?[0-9]*)j,(\\+|-)?([0-9]+(\\.[0-9])?[0-9]*)k$");
	private Double jVal =  0.0;
	private Double kVal =  0.0;

	public Quaternion() {
		setR(0.0);
	}

	public Quaternion(Double rVal, Double iVal, Double jVal, Double kVal) {
		setR(rVal);
		setI(iVal);
		setJ(jVal);
		setK(kVal);
	}

	public void setJ(Double valToSet) {
		jVal = valToSet;
	}

	public void setK(Double valToSet) {
		kVal = valToSet;
	}

	public double getJ() {
		return jVal;
	}

	public double getK() {
		return kVal;
	}

	public void inverseJ() {
		setJ(getJ() * -1);
	}

	public void inverseK() {
		setJ(getK() * -1);
	}

	public Quaternion conjugate() {
		Quaternion res;
		res = this;
		res.inverseI();
		res.inverseJ();
		res.inverseK();
		return res;
	}

	public double norm() throws RuntimeException {
		double ret;
		if ((Math.pow(getR(), 2.0) + Math.pow(getI(), 2.0) +
				Math.pow(getJ(), 2.0) + Math.pow(getK(), 2.0)) == 0) {
			throw new RuntimeException("Divisione per 0" );
		}else{
			ret = Math.pow((Math.pow(getR(), 2.0) + Math.pow(getI(), 2.0) +
					Math.pow(getJ(), 2.0) + Math.pow(getK(), 2.0)), 1/2);
			return ret;
		}
	}

	public Quaternion inverse() {
		Quaternion norma = new Quaternion();
		norma.setR(Math.pow(norm(), 2.0));
		Quaternion ret = this;
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
            splitted[2] = splitted[2].replace("j", "");
            setJ(Double.valueOf(splitted[2]));
            splitted[3] = splitted[3].replace("k", "");
            setK(Double.valueOf(splitted[3]));
            return;
        }
        throw new RuntimeException("Errore nella lettura del quaternione " + str);
	}

	public Quaternion somma(Quaternion b) {
		Quaternion res = new Quaternion();
		res.setR(getR() + b.getR());
		res.setI(getI() + b.getI());
		res.setJ(getJ() + b.getJ());
		res.setK(getK() + b.getK());
		return res;
	}
	public Quaternion sottrai (Quaternion b) {
		Quaternion res = new Quaternion();
		res.setR(getR() - b.getR());
		res.setI(getI() - b.getI());
		res.setJ(getJ() - b.getJ());
		res.setK(getK() - b.getK());
		return res;
	}
	public Quaternion moltiplica (Quaternion b) {
		Quaternion res = new Quaternion();
		// prodotti normali
		res.setR((getR() * b.getR()) -
				(getI() * b.getI()) -
				(getJ() * b.getJ()) -
				(getK() * b.getK()));
		// prodotti tra R<>I e J<>K
		res.setI((getR() * b.getI()) +
				(getI() * b.getR()) +
				(getJ() * b.getK()) -
				(getK() * b.getJ()));
		// prodotti tra R<>J e I<>K
		res.setJ((getR() * b.getJ()) -
				(getI() * b.getK()) +
				(getJ() * b.getR()) +
				(getK() * b.getI()));
		// prodotti tra R<>K e I<>J
		res.setK((getR() * b.getK()) +
				(getI() * b.getJ()) -
				(getJ() * b.getI()) +
				(getK() * b.getR()));
		return res;
	}
	public Quaternion dividi(Quaternion b) throws RuntimeException {
		Double a1 = getR();
		Double b1 = getI();
		Double c1 = getJ();
		Double d1 = getK();
		Double a2 = b.getR();
		Double b2 = b.getI();
		Double c2 = b.getJ();
		Double d2 = b.getK();

		Double denominatore = a2*a2 + b2*b2 + c2*c2 + d2*d2;
		if (denominatore == 0)
			throw new RuntimeException("Errore divisione per 0");

		Quaternion res = new Quaternion();
		// Parte reale -- prodotti normali
		res.setR( ((a1*a2)+(b1*b2)+(c1*c2)+(d1*d2)) / denominatore);
		// Parte immaginaria I -- prodotti tra R<>I e J<>K
		res.setI( ((a1*-b2)+(b1*a2)+(c1*d2)+(d1*-c2)) / denominatore);
		// Parte immaginaria J -- prodotti tra R<>J e I<>K
		res.setJ( ((a1*-c2)+(b1*-d2)+(c1*a2)+(d1*b2)) / denominatore);
		// Parte immaginaria K -- prodotti tra R<>K e I<>J
		res.setK( ((a1*-d2)+(b1*c2)+(c1*-b2)+(d1*a2)) / denominatore);
		return res;
	}

	public String getString() {
		return String.format("%.2f", getR()) + " " + String.format("%+.2f", getI()) + "i" + " " +
				String.format("%+.2f", getJ()) + "j " + String.format("%+.2f", getK()) + "k";
	}
}