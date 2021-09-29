function frequency = frequency_detection1(samples, sampling_time, noise_factor)
    nSamples = length(samples);
    ncycles = 0;
    is_counting = 0;
    reference_value = samples(1);
    min_flag = 0;
    max_flag = 0;
    prev_sample_reading_taken = 0;
    nsamples_passed = 0;
    for i = 1:nSamples
        if (samples(i) - reference_value >= noise_factor)
            if (max_flag == 1)
                if is_counting== 1
                    ncycles = ncycles + 0.5;
                    nsamples_passed = nsamples_passed + i - prev_sample_reading_taken;
                    prev_sample_reading_taken = i;
                else
                    is_counting = 1;
                    prev_sample_reading_taken = i;
                    reference_value = samples(i);
                end
                max_flag = 0;                
            end
            min_flag = 1;
        elseif (reference_value - samples(i) > noise_factor)
            if (min_flag == 1)
                if is_counting== 1
                    ncycles = ncycles + 0.5;
                    nsamples_passed = nsamples_passed + i - prev_sample_reading_taken;
                    prev_sample_reading_taken = i;
                else
                    is_counting = 1;
                    prev_sample_reading_taken = i;
                    reference_value = samples(i);
                end
                min_flag = 0;
            end
            max_flag = 1;
        end
    end
    if ncycles
        frequency = (1000000/((nsamples_passed/ncycles) * sampling_time));
    else
        frequency = 100;
    end
end
