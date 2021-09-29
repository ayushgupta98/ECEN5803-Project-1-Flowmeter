function velocity = flow_rate_calculation(frequency, temperature, pid, d)
    %velocity is in m/sec
    %frequency in Hz
    %temperature in celsius
    %
    pid = pid * 0.0254; % convert to meters
    d = d * 0.0254; %converts to meters
    T = temperature + 273.15; % converts the temperature to Kelvin
    density = 1000*(1 - ((temperature + 288.9414)/(508929.2* (temperature + 68.1293))) * ((temperature-3.9862)^2));
    viscosity = (2.4 * 10^(-5)) * (10 ^((247.8/(T - 140))));
    
    a = 0.0671;
    b = -1*((0.05368*frequency*d) + (viscosity / (density*pid)));
    c = (frequency*d)^2;
    
    p = [a b c];
    r = roots(p);
    absolute_values = abs(r);
    v = absolute_values(1);
    velocity = v;
end