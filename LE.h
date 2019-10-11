
int LE(double tThresh, double tMin, double tMax,
	unsigned nSamples, vector<double>& time, vector<double>& channel, double &time1)

{
	Interpolator voltage;
	voltage.init(nSamples, time[0], time[nSamples-1], channel);
	
	double tStep = (time[nSamples-1] - time[0])/(double)(nSamples-1)/10.;
	double tStepInit = tStep;
	double t = tMin;
	unsigned nIterations = 0;
	for(;;){
		//cout << "tStep: " << tStep << endl;
		for(; (voltage.f(t) - tThresh)*tStep < 0.; t += tStep){	
			//cout << "t: " << t << endl;
			if(t<tMin) return -1;
			if(t>tMax) return -2;	
		}
		if(abs(tStep) < 0.1e-12) break;
		tStep = - tStep/2.;
		++nIterations;
		if(nIterations > 1000) return -3;
	}
	
	time1 = t;
	
	return 0;
	
}