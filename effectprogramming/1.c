#include <stdio.h>
#include <time.h>
long long TimeValue=0;

unsigned long long time_RDTSC(){ 
	union ticks{ 
		unsigned long long tx;
		struct dblword { 
			long tl,th; 
		}dw; // little endian
  }t;

  asm("rdtsc\n": "=a"(t.dw.tl),"=d"(t.dw.th));
  return t.tx;

} // for x86 only!

void time_start() { 
	TimeValue=time_RDTSC(); 
}

long long time_stop() { 
	return time_RDTSC()-TimeValue; 
}

int main(){
	double sum = 1.11;
	double sum2 = 1.11;
	double sum3 = 1.11;
	double sum4 = 1.11;
	double sum5 = 1.11;
	double sum6 = 1.11;
	double sum7 = 1.11;
	double sum8 = 1.11;
	double sum9 = 1.11;
	double sum10 = 1.11;
	register int i =0;
	time_start();
	for( i = 0; i < 100000; i++){
		
		sum += sum2;
		sum2 += sum;
		
		// sum += 1.23;
		// sum2 += 1.23;
		// sum3 += 1.23;		
		// sum4 += 1.23;
		// sum5 += 1.23;
		// sum6 += 1.23;
		// sum7 += 1.23;
		// sum8 += 1.23;
		// sum9 += 1.23;
		// sum10 += 1.23;

	}
	printf("%lf %lf \n", sum,sum2);
	// printf("%lf %lf %lf %lf %lf %lf %lf %lf %lf \n", sum,sum2,sum3,sum4,sum5,sum6,sum7,sum8,sum9 );
	unsigned long long time2 = time_stop();
	printf("Cycle time =  %lld", time2);
	// printf("Time 2 = %lf\n", (double)time2 / 100000 / 10);
	printf("Time 2 = %lf\n", (double)time2 / 100000 / 2);
	
}
