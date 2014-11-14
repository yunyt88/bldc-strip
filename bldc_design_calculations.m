Ts_ADC1 = 1e-6; % Sample time of ADC1 [s] (All channels ADC_SAMPLE_1P5)
ADC_COMMUTATE_NUM_CHANNELS = 5;
ADC_COMMUTATE_BUF_DEPTH = 8;
f_single = 1 / (Ts_ADC1 * ADC_COMMUTATE_NUM_CHANNELS) % Sample frequency of each channel
T_cb_ADC1 = Ts_ADC1 * ADC_COMMUTATE_NUM_CHANNELS * ADC_COMMUTATE_BUF_DEPTH / 2 % Period of ADC1 streaming callback
f_cb_ADC1 = 1 / T_cb_ADC1

f_PWM = 20e3;
duty_cycle = 0.2;
t_on = duty_cycle * 1/f_PWM


