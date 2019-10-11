class Correction {

	public:
	

	double a0 = 6.41e-09;
	double a1 = -2.73e-10;
	double a2 = 0.;
	double a3 = 0.;
	
	


	double corr(double tot) { 
	
		  return ((a3*tot + a2)*tot + a1)*tot +a0;
	  
	}
	
	void print() {
	
		cout << "a0: " << a0 << " " 
			 << "a1: " << a1 << " " 
			 << "a2: " << a2 << " " 
			 << "a3: " << a3 << " " 
			 << endl;
	}
	
};