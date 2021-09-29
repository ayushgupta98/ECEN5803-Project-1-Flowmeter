function frequency = frequency_detection3(samples, sampling_time, noise_factor)
    nsamples = length(samples);
    ntransitions = 0;
    nsamples_passed = 0;
    min_flag = 0;
    max_flag = 0;
    is_counting = 0;
    prev_sample_reading_taken = 0;
    for i = 2:nsamples
        if ((samples(i) - samples(i-1)) >= noise_factor)
            if (max_flag)
                max_flag = 0;
                if (is_counting)
                    ntransitions = ntransitions + 1;
                    nsamples_passed = nsamples_passed + i - prev_sample_reading_taken;
                    prev_sample_reading_taken = i;
                else
                    prev_sample_reading_taken = i;
                    is_counting = 1;
                end
            end
            min_flag = 1;
        elseif ((samples(i-1) - samples(i)) >= noise_factor)
            if (min_flag)
                min_flag = 0;
                if (is_counting)
                    ntransitions = ntransitions + 1;
                    nsamples_passed = nsamples_passed + i - prev_sample_reading_taken;
                    prev_sample_reading_taken = i;
                else
                    prev_sample_reading_taken = i;
                    is_counting = 1;
                end
            end
            max_flag = 1;
        end
    end
    if (ntransitions == 0) 
        frequency = 100;
    else
        frequency = (1000000/((nsamples_passed/ntransitions) * sampling_time * 2));

    end
    
end

