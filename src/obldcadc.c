/*
 * obldcadc.c
 *
 *  Created on: 31.05.2014
 *      Author: joerg
 */


#include "ch.h"
#include "hal.h"

#include "obldcadc.h"

#define ADC_GRP1_NUM_CHANNELS   8
#define ADC_GRP1_BUF_DEPTH      4

static adcsample_t samples1[ADC_GRP1_NUM_CHANNELS * ADC_GRP1_BUF_DEPTH];

/*
 * ADC streaming callback.
 */
static void adccallback(ADCDriver *adcp, adcsample_t *buffer, size_t n) {

  (void)adcp;

  adcsample_t avg_ch1 = (samples1[0] + samples1[1] + samples1[2] + samples1[3] + samples1[4] + samples1[5] + samples1[6] + samples1[7]) / 8;
  float voltage = avg_ch1/4095.0*3;

}

static void adcerrorcallback(ADCDriver *adcp, adcerror_t err) {

  (void)adcp;
  (void)err;
}

/*
 * ADC conversion group.
 * Mode:        Continuous, 8 samples of 1 channel, SW triggered.
 * Channels:    IN0.
 */
static const ADCConversionGroup adcgrpcfg1 = {
  TRUE,
  ADC_GRP1_NUM_CHANNELS,
  adccallback,
  adcerrorcallback,
  0, ADC_CR2_TSVREFE,           /* ADC_CR1, ADC_CR2; ADC_CR2_TSVREFE = Temperature sensor and V REFINT enable */
  ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_239P5) | ADC_SMPR1_SMP_VREF(ADC_SAMPLE_239P5), // ADC sample time register 1 (ADC_SMPR1)
  ADC_SMPR2_SMP_AN0(ADC_SAMPLE_41P5) | ADC_SMPR2_SMP_AN1(ADC_SAMPLE_41P5) |
  ADC_SMPR2_SMP_AN2(ADC_SAMPLE_41P5) | ADC_SMPR2_SMP_AN3(ADC_SAMPLE_41P5) |
  ADC_SMPR2_SMP_AN4(ADC_SAMPLE_41P5) | ADC_SMPR2_SMP_AN5(ADC_SAMPLE_41P5),                            /* SMPR2 */
  ADC_SQR1_NUM_CH(ADC_GRP1_NUM_CHANNELS),  // ADC regular sequence register (ADC_SQRx)
  ADC_SQR2_SQ8_N(ADC_CHANNEL_SENSOR) | ADC_SQR2_SQ7_N(ADC_CHANNEL_VREFINT),
  ADC_SQR3_SQ6_N(ADC_CHANNEL_IN5) | ADC_SQR3_SQ5_N(ADC_CHANNEL_IN4) |
  ADC_SQR3_SQ4_N(ADC_CHANNEL_IN3) | ADC_SQR3_SQ3_N(ADC_CHANNEL_IN2) |
  ADC_SQR3_SQ2_N(ADC_CHANNEL_IN1) | ADC_SQR3_SQ1_N(ADC_CHANNEL_IN0)
};


void startmyadc(void) {
	adcStart(&ADCD1, NULL);
	adcStartConversion(&ADCD1, &adcgrpcfg1, samples1, ADC_GRP1_BUF_DEPTH);
}



