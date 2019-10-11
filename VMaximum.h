
double VMaximum(double tMin, double tMax,
	unsigned nSamples, vector<double>& time, vector<double>& channel)
{
	Interpolator voltage;
	voltage.init(nSamples, time[0], time[nSamples-1], channel);
	
	double tStep = (time[nSamples-1] - time[0])/(double)(nSamples-1)/10.;
	
	double vMax = -1.e6;
	
	for(double t = tMin; t <= tMax; t += tStep){
		if(voltage.f(t) > vMax) vMax = voltage.f(t);
	}
	
	return vMax;
}
	