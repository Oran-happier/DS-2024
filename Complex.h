class Complex
{
private:
	double real;
	double imag;

public:
	Complex(double r = 0, double i = 0) :real(r), imag(i) {};
	double modulus() const;
	bool operator==(const Complex& other) const;
	bool operator!=(const Complex& other) const;
	bool operator<(const Complex& other) const;
	bool operator>(const Complex& other) const;
	void show() const;
};
