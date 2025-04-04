/*
 * pmic.h
 *
 *  Created on: Mar 9, 2025
 *      Author: lsj95
 */

#ifndef PMIC_PMIC_H_
#define PMIC_PMIC_H_

#ifdef __cplusplus
extern "C" {
#endif


//#include <MAX20303.h>
////extern "C" {
//////class PMIC
//////{
//////public:
//////	PMIC(void);
//////	int init(void);
//////
//////	MAX20303 max20303;
//////};
//
//	int pmic_init(void);
//	MAX20303 max20303;
////}


int pmic_init(void);
//MAX20303 max20303;

int pmicSOCRead(unsigned char *batterylevel);
int isBATTCharging();

int runHaptic(int hapticFrequencyHz, int hapticDuration, int hapticContinue);

#ifdef __cplusplus
}
#endif

#endif /* PMIC_PMIC_H_ */
